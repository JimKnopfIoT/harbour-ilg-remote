#include "portscan.h"

#include <QCoreApplication>
#include <QTcpSocket>
#include <QTimer>
#include <QVector>

namespace {

struct Known { int port; const char *service; };

/* Am Geraet gemessen offen: 3000, 3001, 9922, 7000, 36866.
   Die uebrigen stehen mit drin, damit eine Aenderung auffaellt. */
const QVector<Known> kPorts = {
    { 3000,  QT_TRANSLATE_NOOP("PortScan", "SSAP unencrypted (refused by the firmware)") },
    { 3001,  QT_TRANSLATE_NOOP("PortScan", "SSAP over TLS - the connection this app uses") },
    { 7000,  QT_TRANSLATE_NOOP("PortScan", "AirPlay") },
    { 9922,  QT_TRANSLATE_NOOP("PortScan", "Developer mode SSH") },
    { 36866, QT_TRANSLATE_NOOP("PortScan", "webOS internal") },
    { 22,    QT_TRANSLATE_NOOP("PortScan", "SSH") },
    { 80,    QT_TRANSLATE_NOOP("PortScan", "HTTP") },
    { 443,   QT_TRANSLATE_NOOP("PortScan", "HTTPS") },
    { 1900,  QT_TRANSLATE_NOOP("PortScan", "UPnP") },
    { 8080,  QT_TRANSLATE_NOOP("PortScan", "HTTP alternative") },
};

} // namespace

PortScan::PortScan(QObject *parent) : QObject(parent) {}

/* Nur der eine Port, nur eine Sekunde: die Liste soll zuegig ein Bild geben.
   Ein Fernseher im Bereitschaftsbetrieb nimmt hier nichts an - genau das ist
   die Aussage "offline". */
void PortScan::probe(const QString &host)
{
    if (host.isEmpty())
        return;

    QTcpSocket *sock = new QTcpSocket(this);
    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(1200);

    auto report = [this, sock, timer, host](bool up) {
        if (sock->property("done").toBool())
            return;
        sock->setProperty("done", true);
        timer->stop();
        emit reachable(host, up);
        sock->abort();
        sock->deleteLater();
        timer->deleteLater();
    };

    connect(sock, &QTcpSocket::connected, this, [report]() { report(true); });
    connect(sock, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
            this, [report](QAbstractSocket::SocketError) { report(false); });
    connect(timer, &QTimer::timeout, this, [report]() { report(false); });

    timer->start();
    sock->connectToHost(host, quint16(3001));
}

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
        const QString service = QCoreApplication::translate("PortScan", k.service);

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
