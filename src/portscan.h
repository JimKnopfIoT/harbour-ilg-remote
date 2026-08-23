#ifndef PORTSCAN_H
#define PORTSCAN_H

#include <QObject>
#include <QString>

/*
 * Prueft, welche der bekannten Dienste-Ports des Fernsehers antworten.
 * Bewusst nur eine feste, kurze Liste - es geht um eine Zustandsanzeige,
 * nicht um eine Erkundung fremder Geraete.
 */
class PortScan : public QObject
{
    Q_OBJECT

public:
    explicit PortScan(QObject *parent = nullptr);

    Q_INVOKABLE void scan(const QString &host);

    /* Kurzer Test auf Port 3001: antwortet der Fernseher ueberhaupt?
       Fuer die Anzeige an-/abwesend in der Geraeteliste. */
    Q_INVOKABLE void probe(const QString &host);

signals:
    /** open=true, wenn der Port eine Verbindung annimmt. */
    void result(int port, const QString &service, bool open);
    void finished();
    /** Antwort auf probe(): erreichbar oder nicht. */
    void reachable(const QString &host, bool up);

private:
    int m_outstanding = 0;
};

#endif // PORTSCAN_H
