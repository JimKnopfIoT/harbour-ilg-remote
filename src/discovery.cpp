#include "discovery.h"

#include <QHostAddress>
#include <QNetworkAccessManager>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QTcpSocket>
#include <QTimer>
#include <QUdpSocket>
#include <QUrl>

namespace {

const char *kMulticast = "239.255.255.250";
const quint16 kSsdpPort = 1900;
const quint16 kSsapPort = 3001;
const int kRounds = 3;

// Manche Modelle antworten nur auf eine der beiden Kennungen
const QStringList kTargets = {
    QStringLiteral("urn:lge-com:service:webos-second-screen:1"),
    QStringLiteral("urn:schemas-upnp-org:device:MediaRenderer:1")
};

QByteArray searchRequest(const QString &target)
{
    return QStringLiteral(
        "M-SEARCH * HTTP/1.1\r\n"
        "HOST: 239.255.255.250:1900\r\n"
        "MAN: \"ssdp:discover\"\r\n"
        "MX: 2\r\n"
        "ST: %1\r\n\r\n").arg(target).toUtf8();
}

bool usable(const QNetworkInterface &i)
{
    const auto f = i.flags();
    return f.testFlag(QNetworkInterface::IsUp) && f.testFlag(QNetworkInterface::IsRunning)
           && f.testFlag(QNetworkInterface::CanMulticast)
           && !f.testFlag(QNetworkInterface::IsLoopBack);
}

// Eigene Adresse im lokalen Netz - Ausgangspunkt fuer das Abklopfen
QHostAddress localAddress()
{
    for (const QNetworkInterface &i : QNetworkInterface::allInterfaces()) {
        if (!usable(i))
            continue;
        for (const QNetworkAddressEntry &e : i.addressEntries()) {
            const QHostAddress a = e.ip();
            if (a.protocol() == QAbstractSocket::IPv4Protocol && !a.isLoopback())
                return a;
        }
    }
    return QHostAddress();
}

} // namespace

Discovery::Discovery(QObject *parent) : QObject(parent)
{
    m_repeat = new QTimer(this);
    m_repeat->setInterval(1200);
    connect(m_repeat, &QTimer::timeout, this, [this]() {
        if (++m_rounds >= kRounds)
            m_repeat->stop();
        sendSearch();
    });

    m_deadline = new QTimer(this);
    m_deadline->setSingleShot(true);
    m_deadline->setInterval(6000);
    connect(m_deadline, &QTimer::timeout, this, [this]() {
        m_repeat->stop();
        closeSocket();
        if (m_seen.isEmpty())
            sweep();
        else
            setRunning(false);
    });
}

void Discovery::start()
{
    stop();
    m_seen.clear();
    m_rounds = 0;

    m_socket = new QUdpSocket(this);
    if (!m_socket->bind(QHostAddress(QHostAddress::AnyIPv4), 0,
                        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        closeSocket();
        return;
    }
    connect(m_socket, &QUdpSocket::readyRead, this, &Discovery::readResponses);

    setRunning(true);
    sendSearch();
    m_repeat->start();
    m_deadline->start();
}

/* Je Runde ueber jede taugliche Schnittstelle: bindet man nur an die
   Vorgaberoute, geht die Suche bei aktivem Mobilfunk ins Mobilnetz. Und
   UDP-Multicast geht im WLAN verloren, deshalb mehrere Runden. */
void Discovery::sendSearch()
{
    if (!m_socket)
        return;
    const QHostAddress group{QLatin1String(kMulticast)};
    bool sent = false;

    for (const QNetworkInterface &i : QNetworkInterface::allInterfaces()) {
        if (!usable(i))
            continue;
        m_socket->setMulticastInterface(i);
        for (const QString &t : kTargets)
            sent = m_socket->writeDatagram(searchRequest(t), group, kSsdpPort) > 0 || sent;
    }
    if (!sent)
        for (const QString &t : kTargets)
            m_socket->writeDatagram(searchRequest(t), group, kSsdpPort);
}

void Discovery::closeSocket()
{
    if (!m_socket)
        return;
    m_socket->close();
    m_socket->deleteLater();
    m_socket = nullptr;
}

void Discovery::stop()
{
    m_repeat->stop();
    m_deadline->stop();
    closeSocket();
    for (QTcpSocket *s : findChildren<QTcpSocket *>()) {
        s->abort();
        s->deleteLater();
    }
    m_probes = 0;
    setRunning(false);
}

/* Rueckfall, wenn kein SSDP durchkommt: das eigene /24 auf dem SSAP-Port
   abklopfen. Nur dieser eine Port, nur das eigene Netz. */
void Discovery::sweep()
{
    const QHostAddress own = localAddress();
    if (own.isNull()) {
        setRunning(false);
        return;
    }

    const quint32 net = own.toIPv4Address() & 0xFFFFFF00u;
    for (quint32 h = 1; h < 255; ++h) {
        const QHostAddress addr{net | h};
        if (addr == own)
            continue;
        const QString host = addr.toString();

        QTcpSocket *s = new QTcpSocket(this);
        ++m_probes;
        connect(s, &QTcpSocket::connected, this, [this, s, host]() { probeDone(s, host, true); });
        connect(s, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                this, [this, s, host](QAbstractSocket::SocketError) { probeDone(s, host, false); });
        QTimer::singleShot(2500, s, [this, s, host]() { probeDone(s, host, false); });
        s->connectToHost(host, kSsapPort);
    }
    if (m_probes == 0)
        setRunning(false);
}

void Discovery::probeDone(QTcpSocket *s, const QString &host, bool open)
{
    if (s->property("done").toBool())
        return;
    s->setProperty("done", true);
    s->abort();
    s->deleteLater();

    if (open && !m_seen.contains(host)) {
        m_seen.insert(host);
        emit found(host, host);
    }
    if (--m_probes <= 0)
        setRunning(false);
}

void Discovery::setRunning(bool r)
{
    if (r == m_running)
        return;
    m_running = r;
    emit runningChanged();
}

void Discovery::readResponses()
{
    while (m_socket && m_socket->hasPendingDatagrams()) {
        QByteArray data;
        data.resize(int(m_socket->pendingDatagramSize()));
        QHostAddress sender;
        m_socket->readDatagram(data.data(), data.size(), &sender);

        const QString host = sender.toString();
        if (host.isEmpty() || m_seen.contains(host))
            continue;
        m_seen.insert(host);

        // LOCATION-Zeile fuehrt zum Anzeigenamen
        QString location;
        const QStringList lines = QString::fromUtf8(data).split(QStringLiteral("\r\n"));
        for (const QString &l : lines) {
            if (l.startsWith(QStringLiteral("LOCATION:"), Qt::CaseInsensitive)) {
                location = l.mid(9).trimmed();
                break;
            }
        }

        if (location.isEmpty())
            emit found(host, host);
        else
            fetchName(host, location);
    }
}

void Discovery::fetchName(const QString &host, const QString &location)
{
    if (!m_net)
        m_net = new QNetworkAccessManager(this);

    QNetworkReply *reply = m_net->get(QNetworkRequest(QUrl(location)));
    connect(reply, &QNetworkReply::finished, this, [this, reply, host]() {
        QString name = host;
        if (reply->error() == QNetworkReply::NoError) {
            const QString xml = QString::fromUtf8(reply->readAll());
            QRegularExpression re(QStringLiteral("<friendlyName>(.*?)</friendlyName>"),
                                  QRegularExpression::DotMatchesEverythingOption);
            const QRegularExpressionMatch m = re.match(xml);
            if (m.hasMatch())
                name = m.captured(1).trimmed();
        }
        reply->deleteLater();
        emit found(host, name);
    });
}
