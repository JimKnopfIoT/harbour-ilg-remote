#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <QAbstractListModel>
#include <QDateTime>
#include <QHash>
#include <QString>
#include <QVector>

/*
 * Fehlerprotokoll der App.
 *
 * Gedacht als Antwort auf "es geht nicht, aber warum". Jede Stelle, die etwas
 * verspricht - aufwecken, Symbol holen, Text schicken, Kachel belegen -, traegt
 * hier ein, wenn das Versprechen nicht eingeloest wurde. Laeuft alles glatt,
 * bleibt die Liste leer; das ist der Normalfall und zugleich die Aussage.
 *
 * Aus C++:  ErrorLog::note(tr("Wake-on-LAN"), tr("keine MAC hinterlegt"), host);
 * Aus QML:  errorLog.add("Kacheln", "Symbol nicht geladen", url)
 */
class ErrorLog : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    enum Roles {
        WhenRole = Qt::UserRole + 1,
        AreaRole,
        TextRole,
        DetailRole,
        RepeatRole
    };

    static ErrorLog *instance();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    /* Bequemer Aufruf aus dem uebrigen Quelltext - legt bei Bedarf an. */
    static void note(const QString &area, const QString &text,
                     const QString &detail = QString());

    Q_INVOKABLE void add(const QString &area, const QString &text,
                         const QString &detail = QString());
    Q_INVOKABLE void clear();
    /* Fuer die Zwischenablage: das ganze Protokoll als Text. */
    Q_INVOKABLE QString asText() const;

signals:
    void countChanged();

private:
    explicit ErrorLog(QObject *parent = nullptr);

    struct Entry {
        QDateTime when;
        QString area;
        QString text;
        QString detail;
        int repeat = 1;
    };

    QVector<Entry> m_rows;
};

#endif // ERRORLOG_H
