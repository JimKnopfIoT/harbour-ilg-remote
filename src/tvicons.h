#ifndef TVICONS_H
#define TVICONS_H

#include <QObject>
#include <QQuickAsyncImageProvider>
#include <QString>

class QNetworkAccessManager;
class QNetworkReply;

/*
 * App- und Eingangssymbole liegen auf dem Fernseher und sind nur ueber https
 * mit seinem selbstsignierten Zertifikat zu haben - QMLs Image nimmt das nicht
 * an. Hier geholt, gegen den gemerkten Fingerabdruck geprueft und auf Platte
 * zwischengespeichert. Aufruf aus QML: image://tvicon/<encodeURIComponent(url)>
 */
class TvIcons : public QObject, public QQuickAsyncImageProvider
{
    Q_OBJECT

    Q_PROPERTY(QString fingerprint READ fingerprint WRITE setFingerprint NOTIFY fingerprintChanged)

public:
    explicit TvIcons(QObject *parent = nullptr);

    QString fingerprint() const { return m_fingerprint; }
    void setFingerprint(const QString &f);

    QQuickImageResponse *requestImageResponse(const QString &id, const QSize &size) override;

    /* Bildschirmfoto des Fernsehers ablegen. Dieselbe Verbindung wie die
       Symbole, deshalb steht es hier und nicht in LgTv. */
    Q_INVOKABLE void saveToGallery(const QString &url, const QString &name);

signals:
    void fingerprintChanged();
    void saved(const QString &path);
    void saveFailed(const QString &message);

private:
    void pin(QNetworkReply *reply) const;
    void fetchCapture(const QString &url, const QString &path, int tries);

    QString m_fingerprint;
    QNetworkAccessManager *m_net = nullptr;
    QString m_dir;
};

#endif // TVICONS_H
