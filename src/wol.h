#ifndef WOL_H
#define WOL_H

#include <QObject>
#include <QString>

/*
 * Wake-on-LAN: sendet ein Magic Packet als UDP-Broadcast.
 * Muss in C++ liegen – QML hat keinen Zugriff auf UDP-Sockets.
 */
class Wol : public QObject
{
    Q_OBJECT

public:
    explicit Wol(QObject *parent = nullptr);

    /* MAC in der Form "AA:BB:CC:DD:EE:FF". host ist optional und dient nur
       dazu, das Paket zusaetzlich gezielt ins richtige Subnetz zu schicken.
       Gibt false zurueck, wenn die Adresse unlesbar war oder nichts rausging. */
    Q_INVOKABLE bool wake(const QString &mac, const QString &host = QString());
};

#endif // WOL_H
