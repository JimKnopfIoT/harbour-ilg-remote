#ifndef DISCOVERY_H
#define DISCOVERY_H

#include <QObject>
#include <QSet>
#include <QString>

class QTcpSocket;
class QTimer;
class QUdpSocket;
class QNetworkAccessManager;

/*
 * Sucht LG-Fernseher im Netz: erst SSDP, dann - falls nichts antwortet -
 * das eigene /24 auf Port 3001.
 */
class Discovery : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running NOTIFY runningChanged)

public:
    explicit Discovery(QObject *parent = nullptr);

    bool running() const { return m_running; }

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

signals:
    void found(const QString &host, const QString &name);
    void runningChanged();

private slots:
    void readResponses();

private:
    void sendSearch();
    void closeSocket();
    void sweep();
    void probeDone(QTcpSocket *s, const QString &host, bool open);
    void fetchName(const QString &host, const QString &location);
    void setRunning(bool r);

    QUdpSocket *m_socket = nullptr;
    QNetworkAccessManager *m_net = nullptr;
    QTimer *m_repeat = nullptr;
    QTimer *m_deadline = nullptr;
    QSet<QString> m_seen;
    int m_rounds = 0;
    int m_probes = 0;
    bool m_running = false;
};

#endif // DISCOVERY_H
