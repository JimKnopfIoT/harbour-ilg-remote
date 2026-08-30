#include "tvicons.h"

#include "errorlog.h"

#include <QCoreApplication>
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

/* Ein Symbol ist so gross wie ein Symbol, ein Bildschirmfoto so gross wie ein
   Bild. Wer mehr schickt, will nicht liefern, sondern den Arbeitsspeicher
   fuellen - readAll() nimmt sonst alles. */
const qint64 kMaxSymbol  =  4 * 1024 * 1024;
const qint64 kMaxAufnahme = 32 * 1024 * 1024;

/* Adressen aus der App-Liste bestimmt die App auf dem Fernseher selbst. Nur
   https auf den Fernseher wird abgerufen: bei http gibt es keinen Handschlag
   und damit auch kein gemerktes Zertifikat, das noch etwas pruefen koennte,
   und ein fremder Host waere ohnehin nicht der Fernseher. */
bool vomFernseher(const QString &url, const QString &host)
{
    if (host.isEmpty())
        return false;
    const QUrl u(url);
    return u.isValid()
           && u.scheme().compare(QLatin1String("https"), Qt::CaseInsensitive) == 0
           && u.host().compare(host, Qt::CaseInsensitive) == 0;
}

/* Zertifikat und Groesse an einen laufenden Abruf haengen.

   Geprueft wird das Zertifikat der Gegenstelle - peerCertificate() -, nicht
   das erstbeste aus der Fehlerliste. Deren Reihenfolge liegt nicht in unserer
   Hand: Steht die Zwischenstelle vorn, verglich die alte Fassung den
   gemerkten Fingerabdruck mit dem falschen Zertifikat und wies den Abruf ab,
   obwohl alles stimmte. Nur das Blatt beweist im Handschlag den Besitz seines
   Schluessels; jedes weitere Zertifikat der Kette ist oeffentliches Beiwerk
   und taugt nicht als Ausweis. */
void anhaengen(QNetworkReply *reply, const QString &fingerprint, qint64 max)
{
    QObject::connect(reply, &QNetworkReply::sslErrors, reply,
                     [reply, fingerprint](const QList<QSslError> &errors) {
        QSslCertificate blatt = reply->sslConfiguration().peerCertificate();
        if (blatt.isNull()) {
            // Aeltere Qt-Fassungen fuellen das erst spaeter
            for (const QSslError &e : errors) {
                if (!e.certificate().isNull()) {
                    blatt = e.certificate();
                    break;
                }
            }
        }
        if (blatt.isNull()) {
            ErrorLog::note(TvIcons::tr("Icon"),
                           TvIcons::tr("TLS error without a certificate to check"), QString());
            return;
        }
        const QString gesehen = QString::fromLatin1(
            blatt.digest(QCryptographicHash::Sha256).toHex());
        if (gesehen == fingerprint)
            reply->ignoreSslErrors();
        else
            ErrorLog::note(TvIcons::tr("Icon"),
                           TvIcons::tr("the TV shows a different certificate than the one remembered"),
                           gesehen);
    });

    QObject::connect(reply, &QNetworkReply::downloadProgress, reply,
                     [reply, max](qint64 da, qint64 gesamt) {
        if (da > max || gesamt > max)
            reply->abort();
    });
}

class IconResponse : public QQuickImageResponse
{
    // Eigener Uebersetzungskontext - die Klasse hat keinen von sich aus
    Q_DECLARE_TR_FUNCTIONS(TvIcons)

public:
    IconResponse(const QString &url, const QString &file, QNetworkAccessManager *net,
                 const QString &fingerprint, const QString &host)
        : m_url(url), m_file(file), m_net(net), m_fingerprint(fingerprint), m_host(host)
    {
        if (m_image.load(m_file)) {
            QTimer::singleShot(0, this, [this]() { emit finished(); });
            return;
        }
        if (!vomFernseher(m_url, m_host)) {
            ErrorLog::note(tr("Icon"),
                           tr("this address does not lead to the TV - not fetched"), m_url);
            QTimer::singleShot(0, this, [this]() { emit finished(); });
            return;
        }
        if (m_fingerprint.isEmpty()) {
            /* Ohne gemerktes Zertifikat wird jeder Abruf abgewiesen. Das
               passiert genau dann, wenn eine Kachel belegt wird, bevor je
               eine Verbindung stand. */
            ErrorLog::note(tr("Icon"),
                           tr("no certificate remembered yet - connect to the TV once, then the icons will load"),
                           m_url);
            QTimer::singleShot(0, this, [this]() { emit finished(); });
            return;
        }
        get();
    }

    void get()
    {
        QNetworkReply *reply = m_net->get(QNetworkRequest(QUrl(m_url)));
        anhaengen(reply, m_fingerprint, kMaxSymbol);
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            const bool ok = reply->error() == QNetworkReply::NoError
                            && m_image.loadFromData(reply->readAll());
            reply->deleteLater();
            if (ok) {
                m_image.save(m_file, "PNG");
            } else if (--m_tries > 0) {
                /* Der Fernseher weist zeitweise Handshakes ab, und beim
                   Oeffnen der Liste kommen zwanzig Abrufe auf einmal.
                   Deshalb mehrfach nachfassen, mit wachsendem Abstand. */
                QTimer::singleShot(m_tries == 2 ? 700 : 1600, this, [this]() { get(); });
                return;
            } else {
                ErrorLog::note(tr("Icon"), tr("not fetched from the TV after three tries"),
                               m_url);
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
    QString m_host;
    int m_tries = 3;
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

void TvIcons::setHost(const QString &h)
{
    if (h == m_host)
        return;
    m_host = h;
    emit hostChanged();
}

void TvIcons::saveToGallery(const QString &url, const QString &name)
{
    /* Zweiter Riegel. Die Adresse ist in LgTv bereits geprueft; hier steht
       sie noch einmal, weil dieser Weg von QML aus offen ist und ein Riegel
       nur dort haelt, wo der Griff sitzt. */
    if (!vomFernseher(url, m_host)) {
        ErrorLog::note(tr("Screenshot"),
                       tr("this address does not lead to the TV - not fetched"), url);
        emit saveFailed(tr("Screenshot not fetched"));
        return;
    }
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
    anhaengen(reply, m_fingerprint, kMaxAufnahme);
    connect(reply, &QNetworkReply::finished, this, [this, reply, url, path, tries]() {
        const QByteArray data = reply->readAll();
        const QNetworkReply::NetworkError err = reply->error();
        const QString text = reply->errorString();
        reply->deleteLater();
        if (err != QNetworkReply::NoError) {
            if (tries <= 1)
                ErrorLog::note(tr("Screenshot"), tr("not fetched from the TV"), text);
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
            ErrorLog::note(tr("Screenshot"), tr("could not be written to the gallery"),
                           path + QStringLiteral(" - ") + f.errorString());
            emit saveFailed(tr("Screenshot not saved"));
            return;
        }
        f.close();
        qWarning() << "TvIcons: Bildschirmfoto abgelegt:" << path << data.size() << "Bytes";
        emit saved(path);
    });
}

/* Wird beim Belegen einer Kachel gerufen: das Symbol soll auf der Platte
   liegen, bevor die Kachel es zeigen will. Klappt das nicht, steht der Grund
   im Protokoll - und nicht nur ein leeres Feld auf dem Bildschirm. */
void TvIcons::prefetch(const QString &url)
{
    if (url.isEmpty())
        return;
    const QString file = m_dir + QLatin1Char('/') + cacheName(url);
    if (QFile::exists(file)) {
        emit iconReady(url);
        return;
    }
    if (!vomFernseher(url, m_host)) {
        ErrorLog::note(tr("Tile"),
                       tr("icon not fetched: this address does not lead to the TV"), url);
        return;
    }
    if (m_fingerprint.isEmpty()) {
        ErrorLog::note(tr("Tile"),
                       tr("icon not fetched: no certificate of the TV remembered yet"), url);
        return;
    }

    QNetworkReply *reply = m_net->get(QNetworkRequest(QUrl(url)));
    anhaengen(reply, m_fingerprint, kMaxSymbol);
    connect(reply, &QNetworkReply::finished, this, [this, reply, url, file]() {
        const QByteArray data = reply->readAll();
        const bool ok = reply->error() == QNetworkReply::NoError && !data.isEmpty();
        const QString text = reply->errorString();
        reply->deleteLater();
        QImage bild;
        if (!ok || !bild.loadFromData(data)) {
            ErrorLog::note(tr("Tile"), tr("icon not fetched from the TV"),
                           url + QStringLiteral(" - ") + text);
            return;
        }
        if (!bild.save(file, "PNG")) {
            ErrorLog::note(tr("Tile"), tr("icon could not be cached"), file);
            return;
        }
        emit iconReady(url);
    });
}

QQuickImageResponse *TvIcons::requestImageResponse(const QString &id, const QSize &)
{
    const QString url = QUrl::fromPercentEncoding(id.toUtf8());
    return new IconResponse(url, m_dir + QLatin1Char('/') + cacheName(url), m_net,
                            m_fingerprint, m_host);
}
