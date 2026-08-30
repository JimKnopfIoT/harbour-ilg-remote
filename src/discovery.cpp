#include "discovery.h"

#include "errorlog.h"

#include <QHostAddress>
#include <QNetworkAccessManager>
#include <QNetworkInterface>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QStringList>
#include <QVector>
#include <QTcpSocket>
#include <QTimer>
#include <QUdpSocket>
#include <QUrl>

namespace {

const char *kMulticast = "239.255.255.250";
const quint16 kSsdpPort = 1900;
const quint16 kSsapPort = 3001;
const int kRounds = 3;

/* Wie viele Verbindungen gleichzeitig offen sein duerfen. Ein /24 passt in
   einen Schwung, es bleibt also so schnell wie bisher; erst ein weiteres Netz
   wird in Schueben abgeklopft. Der Grund: Ein /22 waeren ueber tausend
   Verbindungen auf einmal, und mehr als 1024 offene Dateien gibt der Prozess
   von Haus aus nicht her - die Suche waere an sich selbst gescheitert und
   nicht am Netz. */
const int kParallel = 256;

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

struct Netz {
    quint32 addr;
    quint32 mask;
    QString name;
};

/* Alle eigenen Netze, nicht nur das erste. Die Reihenfolge der Schnittstellen
   ist beliebig: bei aktivem Mobilfunk stand die Funkstrecke womoeglich vorn,
   und dann wurde das falsche Netz abgeklopft - das Wohnzimmer liegt nicht
   hinter dem Mobilfunk. Ohne Hardwareadresse ist es keine Netzwerkkarte,
   sondern genau so eine Strecke. */
QVector<Netz> localNets()
{
    QVector<Netz> out;
    for (const QNetworkInterface &i : QNetworkInterface::allInterfaces()) {
        if (!usable(i) || i.hardwareAddress().isEmpty())
            continue;
        for (const QNetworkAddressEntry &e : i.addressEntries()) {
            const QHostAddress a = e.ip();
            if (a.protocol() != QAbstractSocket::IPv4Protocol || a.isLoopback())
                continue;
            // Ohne Maske die uebliche Annahme /24
            const quint32 mask = e.netmask().isNull() ? 0xFFFFFF00u
                                                      : e.netmask().toIPv4Address();
            Netz z;
            z.addr = a.toIPv4Address();
            z.mask = mask;
            z.name = i.humanReadableName();
            out.append(z);
        }
    }
    return out;
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
        /* Immer abklopfen, nicht nur wenn gar nichts kam. Auf die
           Multicast-Anfrage antworten auch fremde Geraete - ein NAS, ein
           Medienserver -, und ein Fernseher, der die Anfrage verschluckt,
           fiel dann unter den Tisch: die Suche galt als erfolgreich, nur
           eben ohne ihn. */
        sweep();
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
        ErrorLog::note(tr("Search"), tr("no UDP socket for the search - is the phone on a network?"),
                       m_socket->errorString());
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
    if (!sent) {
        /* Keine Schnittstelle wollte das Multicast nehmen - der Versuch ueber
           die Vorgaberoute ist dann alles, was bleibt. */
        ErrorLog::note(tr("Search"),
                       tr("no interface accepted the multicast - trying the default route"),
                       QString());
        for (const QString &t : kTargets)
            m_socket->writeDatagram(searchRequest(t), group, kSsdpPort);
    }
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
    m_warteschlange.clear();
    setRunning(false);
}

/* Rueckfall, wenn kein SSDP durchkommt: das eigene /24 auf dem SSAP-Port
   abklopfen. Nur dieser eine Port, nur das eigene Netz. */
void Discovery::sweep()
{
    const QVector<Netz> netze = localNets();
    if (netze.isEmpty()) {
        ErrorLog::note(tr("Search"),
                       tr("no address of our own in the local network - search not possible"),
                       QString());
        setRunning(false);
        return;
    }

    QStringList beklopft;
    for (const Netz &z : netze) {
        const quint32 anzahl = ~z.mask;             // hoechste Hausnummer
        /* Ein sehr weites Netz waere hunderte Verbindungen - dafuer ist das
           hier nicht gedacht, und der Nutzer kann die Adresse eintragen. */
        if (anzahl < 3 || anzahl > 1022) {
            ErrorLog::note(tr("Search"),
                           tr("network too large to scan - add the TV by hand"),
                           z.name);
            continue;
        }
        beklopft << z.name + QStringLiteral(" ")
                    + QHostAddress(z.addr & z.mask).toString();

        for (quint32 h = 1; h < anzahl; ++h) {
            const quint32 ziel = (z.addr & z.mask) | h;
            if (ziel == z.addr)
                continue;
            const QString host = QHostAddress(ziel).toString();
            if (m_seen.contains(host))
                continue;               // hat schon per SSDP geantwortet
            m_warteschlange.append(host);
        }
    }
    m_beklopft = beklopft.join(QStringLiteral(", "));

    naechste();
}

/* Nachruecken lassen, bis die Warteschlange leer ist - und erst wenn auch
   nichts mehr laeuft, ist die Suche vorbei. */
void Discovery::naechste()
{
    while (m_probes < kParallel && !m_warteschlange.isEmpty()) {
        const QString host = m_warteschlange.takeFirst();
        if (m_seen.contains(host))
            continue;               // hat inzwischen per SSDP geantwortet

        QTcpSocket *s = new QTcpSocket(this);
        ++m_probes;
        connect(s, &QTcpSocket::connected, this, [this, s, host]() { probeDone(s, host, true); });
        connect(s, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                this, [this, s, host](QAbstractSocket::SocketError) { probeDone(s, host, false); });
        QTimer::singleShot(2500, s, [this, s, host]() { probeDone(s, host, false); });
        s->connectToHost(host, kSsapPort);
    }

    if (m_probes > 0 || !m_warteschlange.isEmpty())
        return;

    if (m_seen.isEmpty())
        ErrorLog::note(tr("Search"),
                       tr("nothing found - neither by SSDP nor on port 3001"),
                       m_beklopft);
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
    --m_probes;
    naechste();
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
        if (reply->error() != QNetworkReply::NoError)
            ErrorLog::note(tr("Search"), tr("device found, but it does not give up its name"),
                           host + QStringLiteral(" - ") + reply->errorString());
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
