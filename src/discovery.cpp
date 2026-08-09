#include "discovery.h"

#include <QHostAddress>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QTimer>
#include <QUdpSocket>
#include <QUrl>

namespace {

const char *kMulticast = "239.255.255.250";
const quint16 kPort = 1900;

/* Zwei Suchanfragen: die LG-eigene Kennung und die allgemeine nach
   Medienwiedergabegeraeten - manche Modelle antworten nur auf eine davon. */
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

} // namespace

Discovery::Discovery(QObject *parent) : QObject(parent) {}

void Discovery::start()
{
    stop();
    m_seen.clear();

    m_socket = new QUdpSocket(this);
    if (!m_socket->bind(QHostAddress(QHostAddress::AnyIPv4), 0,
                        QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) {
        delete m_socket;
        m_socket = nullptr;
        return;
    }
    connect(m_socket, &QUdpSocket::readyRead, this, &Discovery::readResponses);

    setRunning(true);

    for (const QString &t : kTargets)
        m_socket->writeDatagram(searchRequest(t), QHostAddress(QLatin1String(kMulticast)), kPort);

    // Antworten trudeln ueber ein paar Sekunden ein
    QTimer::singleShot(5000, this, &Discovery::stop);
}

void Discovery::stop()
{
    if (m_socket) {
        m_socket->close();
        m_socket->deleteLater();
        m_socket = nullptr;
    }
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

        // LOCATION-Zeile herausziehen, um an den Anzeigenamen zu kommen
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
