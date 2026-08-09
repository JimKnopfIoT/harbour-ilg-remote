#include "portscan.h"

#include <QTcpSocket>
#include <QTimer>
#include <QVector>

namespace {

struct Known { int port; const char *service; };

/* Am Geraet gemessen offen: 3000, 3001, 9922, 7000, 36866.
   Die uebrigen stehen mit drin, damit eine Aenderung auffaellt. */
const QVector<Known> kPorts = {
    { 3000,  "SSAP unverschlüsselt (von der Firmware abgewiesen)" },
    { 3001,  "SSAP über TLS – die Verbindung dieser App" },
    { 7000,  "AirPlay" },
    { 9922,  "Developer Mode SSH" },
    { 36866, "webOS intern" },
    { 22,    "SSH" },
    { 80,    "HTTP" },
    { 443,   "HTTPS" },
    { 1900,  "UPnP" },
    { 8080,  "HTTP alternativ" },
};

} // namespace

PortScan::PortScan(QObject *parent) : QObject(parent) {}

void PortScan::scan(const QString &host)
{
    if (host.isEmpty())
        return;

    m_outstanding = kPorts.size();

    for (const Known &k : kPorts) {
        QTcpSocket *sock = new QTcpSocket(this);
        QTimer *timer = new QTimer(this);
        timer->setSingleShot(true);
        timer->setInterval(1500);

        const int port = k.port;
        const QString service = QString::fromUtf8(k.service);

        // Genau einmal melden, egal ob Erfolg, Fehler oder Zeitablauf
        auto report = [this, sock, timer, port, service](bool open) {
            if (!sock->property("done").toBool()) {
                sock->setProperty("done", true);
                timer->stop();
                emit result(port, service, open);
                sock->abort();
                sock->deleteLater();
                timer->deleteLater();
                if (--m_outstanding <= 0)
                    emit finished();
            }
        };

        connect(sock, &QTcpSocket::connected, this, [report]() { report(true); });
        connect(sock, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                this, [report](QAbstractSocket::SocketError) { report(false); });
        connect(timer, &QTimer::timeout, this, [report]() { report(false); });

        timer->start();
        sock->connectToHost(host, static_cast<quint16>(port));
    }
}
