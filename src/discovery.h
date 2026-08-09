#ifndef DISCOVERY_H
#define DISCOVERY_H

#include <QObject>
#include <QSet>
#include <QString>

class QUdpSocket;
class QNetworkAccessManager;

/*
 * Sucht LG-Fernseher im Netz per SSDP.
 *
 * Der Fernseher meldet sich auf eine Suchanfrage nach
 * "urn:lge-com:service:webos-second-screen:1" und nennt dabei die Adresse
 * einer Beschreibungsdatei. Aus der holen wir den Anzeigenamen - sonst
 * stuende in der Liste nur eine nackte IP.
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
    void fetchName(const QString &host, const QString &location);
    void setRunning(bool r);

    QUdpSocket *m_socket = nullptr;
    QNetworkAccessManager *m_net = nullptr;
    QSet<QString> m_seen;
    bool m_running = false;
};

#endif // DISCOVERY_H
