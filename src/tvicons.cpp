#include "tvicons.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QQuickTextureFactory>
#include <QSslCertificate>
#include <QSslError>
#include <QStandardPaths>
#include <QTimer>
#include <QUrl>

namespace {

QString cacheName(const QString &url)
{
    return QString::fromLatin1(
        QCryptographicHash::hash(url.toUtf8(), QCryptographicHash::Sha1).toHex()) + QStringLiteral(".png");
}

class IconResponse : public QQuickImageResponse
{
public:
    IconResponse(const QString &url, const QString &file, QNetworkAccessManager *net,
                 const QString &fingerprint)
        : m_url(url), m_file(file), m_net(net), m_fingerprint(fingerprint)
    {
        if (m_image.load(m_file)) {
            QTimer::singleShot(0, this, [this]() { emit finished(); });
            return;
        }
        get();
    }

    void get()
    {
        QNetworkReply *reply = m_net->get(QNetworkRequest(QUrl(m_url)));
        const QString fingerprint = m_fingerprint;
        connect(reply, &QNetworkReply::sslErrors, this,
                [reply, fingerprint](const QList<QSslError> &errors) {
                    for (const QSslError &e : errors) {
                        if (e.certificate().isNull())
                            continue;
                        if (fingerprint == QString::fromLatin1(
                                e.certificate().digest(QCryptographicHash::Sha256).toHex()))
                            reply->ignoreSslErrors();
                        return;
                    }
                });
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            const bool ok = reply->error() == QNetworkReply::NoError
                            && m_image.loadFromData(reply->readAll());
            reply->deleteLater();
            if (ok) {
                m_image.save(m_file, "PNG");
            } else if (m_retry) {
                // Zeitweise abgewiesene Handshakes: einmal nachfassen
                m_retry = false;
                QTimer::singleShot(600, this, [this]() { get(); });
                return;
            }
            emit finished();
        });
    }

    QQuickTextureFactory *textureFactory() const override
    {
        return QQuickTextureFactory::textureFactoryForImage(m_image);
    }

private:
    QImage m_image;
    QString m_url;
    QString m_file;
    QNetworkAccessManager *m_net;
    QString m_fingerprint;
    bool m_retry = true;
};

} // namespace

TvIcons::TvIcons(QObject *parent) : QObject(parent)
{
    m_net = new QNetworkAccessManager(this);
    m_dir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation)
            + QStringLiteral("/icons");
    QDir().mkpath(m_dir);
}

void TvIcons::setFingerprint(const QString &f)
{
    if (f == m_fingerprint)
        return;
    m_fingerprint = f;
    emit fingerprintChanged();
}

/* Gleiche Pruefung wie beim Hauptkanal: nur das gemerkte Zertifikat zaehlt. */
void TvIcons::pin(QNetworkReply *reply) const
{
    const QString fp = m_fingerprint;
    connect(reply, &QNetworkReply::sslErrors, reply, [reply, fp](const QList<QSslError> &errors) {
        for (const QSslError &e : errors) {
            if (e.certificate().isNull())
                continue;
            const QString seen = QString::fromLatin1(
                e.certificate().digest(QCryptographicHash::Sha256).toHex());
            if (seen == fp) {
                reply->ignoreSslErrors();
            } else {
                qWarning() << "TvIcons: Zertifikat passt nicht, erwartet" << fp << "gesehen" << seen;
            }
            return;
        }
        qWarning() << "TvIcons: kein Zertifikat in den Fehlern";
    });
}

void TvIcons::saveToGallery(const QString &url, const QString &name)
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)
                        + QStringLiteral("/LG Remote");
    QDir().mkpath(dir);
    fetchCapture(url, dir + QLatin1Char('/') + name, 3);
}

/* Der Fernseher weist zeitweise Handshakes ab (am Geraet gemessen: jeder
   fuenfte) - deshalb nachfassen statt aufgeben. */
void TvIcons::fetchCapture(const QString &url, const QString &path, int tries)
{
    QNetworkReply *reply = m_net->get(QNetworkRequest(QUrl(url)));
    pin(reply);
    connect(reply, &QNetworkReply::finished, this, [this, reply, url, path, tries]() {
        const QByteArray data = reply->readAll();
        const QNetworkReply::NetworkError err = reply->error();
        const QString text = reply->errorString();
        reply->deleteLater();
        if (err != QNetworkReply::NoError) {
            qWarning() << "TvIcons: Abruf gescheitert:" << err << text << "Versuche uebrig:" << tries - 1;
            if (tries > 1) {
                const QString u = url, p = path;
                QTimer::singleShot(800, this, [this, u, p, tries]() { fetchCapture(u, p, tries - 1); });
                return;
            }
            emit saveFailed(tr("Screenshot not fetched"));
            return;
        }
        QFile f(path);
        if (!f.open(QIODevice::WriteOnly) || f.write(data) != data.size()) {
            qWarning() << "TvIcons: Schreiben gescheitert:" << path << f.errorString();
            emit saveFailed(tr("Screenshot not saved"));
            return;
        }
        f.close();
        qWarning() << "TvIcons: Bildschirmfoto abgelegt:" << path << data.size() << "Bytes";
        emit saved(path);
    });
}

QQuickImageResponse *TvIcons::requestImageResponse(const QString &id, const QSize &)
{
    const QString url = QUrl::fromPercentEncoding(id.toUtf8());
    return new IconResponse(url, m_dir + QLatin1Char('/') + cacheName(url), m_net, m_fingerprint);
}
