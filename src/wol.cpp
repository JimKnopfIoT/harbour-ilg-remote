#include "wol.h"

#include <QByteArray>
#include <QHostAddress>
#include <QStringList>
#include <QUdpSocket>

Wol::Wol(QObject *parent) : QObject(parent) {}

bool Wol::wake(const QString &mac, const QString &host)
{
    // Trennzeichen beliebig: ":" oder "-" oder gar keins
    QString clean = mac;
    clean.remove(QLatin1Char(':')).remove(QLatin1Char('-')).remove(QLatin1Char(' '));
    if (clean.length() != 12)
        return false;

    QByteArray addr;
    for (int i = 0; i < 12; i += 2) {
        bool ok = false;
        const int byte = clean.mid(i, 2).toInt(&ok, 16);
        if (!ok)
            return false;
        addr.append(static_cast<char>(byte));
    }

    // Magic Packet: 6x 0xFF, danach 16x die MAC
    QByteArray packet(6, static_cast<char>(0xFF));
    for (int i = 0; i < 16; ++i)
        packet.append(addr);

    /*
     * Breit streuen. Am Geraet gemessen genuegt die allgemeine
     * Rundsendeadresse allein nicht zuverlaessig: Fernseher und Telefon
     * haengen an unterschiedlichen Zugangspunkten, und nicht jeder leitet
     * 255.255.255.255 weiter. Deshalb zusaetzlich die Rundsendeadresse des
     * eigenen Subnetzes und das Geraet direkt. Port 9 ist ueblich, 7 kommt
     * ebenfalls vor - beide kosten nichts.
     */
    QList<QHostAddress> targets;
    targets << QHostAddress::Broadcast;

    if (!host.isEmpty()) {
        QHostAddress tv(host);
        if (!tv.isNull() && tv.protocol() == QAbstractSocket::IPv4Protocol) {
            targets << tv;
            // Rundsendeadresse des Subnetzes, angenommen /24
            const quint32 v = tv.toIPv4Address();
            targets << QHostAddress((v & 0xFFFFFF00u) | 0xFFu);
        }
    }

    QUdpSocket sock;
    bool any = false;
    for (const QHostAddress &t : targets) {
        for (quint16 port : { quint16(9), quint16(7) }) {
            if (sock.writeDatagram(packet, t, port) > 0)
                any = true;
        }
    }
    return any;
}
