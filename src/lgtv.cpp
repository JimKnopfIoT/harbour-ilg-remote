#include "lgtv.h"

#include "errorlog.h"

#include <algorithm>

#include <QCryptographicHash>
#include <QGuiApplication>
#include <QJsonArray>
#include <QPointer>
#include <QSslCertificate>
#include <QSslCipher>
#include <QSslConfiguration>
#include <QStringList>
#include <QSslSocket>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>
#include <QTimer>
#include <QUrl>

/* Die YouTube-App des Fernsehers. Meldet handlesRelaunch, siehe launchApp. */
#define YT_APP "youtube.leanback.v4"

namespace {

// Wie oft der Tastenkanal neu erfragt wird, bevor Ruhe einkehrt
const int kPointerTries = 4;

// Der TV nimmt hoechstens sechs Verbindungen an und raeumt aufgegebene
// Versuche nur langsam ab - deshalb selten wiederholen
const int kHandshakeWait = 4000;
const int kFirstRetry = 3000;
const int kRetryCap = 15000;

// Anlaeufe fuer probeTls
const int kTlsTries = 2;
const int kTlsWait = 2000;

/* Anmelde-Handshake der LG-Fernseher. Der signed-Block wird nicht geprueft,
   muss aber da sein.

   ACHTUNG: Das hier ist JSON, kein C++. Ein Kommentar zwischen den Klammern
   macht es unlesbar, und QJsonDocument liefert dann stillschweigend ein
   leeres Objekt - die App meldet sich mit leerem Manifest an, der Fernseher
   zeigt keine Abfrage mehr, und mit vorhandenem Schluessel faellt es nicht
   einmal auf. Am 23.08.2026 genau so passiert. Anmerkungen gehoeren hierher.

   Die Liste unten ist die, nach der der Fernseher die Rechte erteilt - die im
   signed-Block zaehlt nicht. Sie ist trotzdem nicht beliebig erweiterbar:
   READ_UPDATE_INFO und UPDATE_FROM_REMOTE_APP nachzutragen, um den
   Firmware-Stand zu bekommen, kostete am Geraet die HDMI-Eingaenge aus
   getExternalInputList. Der Fernseher erteilt offenbar nicht additiv. Die
   Eingangsliste wiegt schwerer als eine Zeile Firmware.

   Die Rechte haengen am Kopplungsschluessel: Wer hier etwas aendert, muss die
   Kopplung zuruecksetzen, sonst gilt weiter der alte Umfang. */
const char *kManifest = R"JSON({
  "manifestVersion": 1,
  "appVersion": "1.0",
  "signed": {
    "created": "20140509",
    "appId": "com.lge.test",
    "vendorId": "com.lge",
    "localizedAppNames": { "": "LG Remote" },
    "localizedVendorNames": { "": "LG Electronics" },
    "permissions": ["TEST_SECURE","CONTROL_INPUT_TEXT","CONTROL_MOUSE_AND_KEYBOARD",
      "READ_INSTALLED_APPS","READ_LGE_SDX","READ_NOTIFICATIONS","SEARCH","WRITE_SETTINGS",
      "WRITE_NOTIFICATION_ALERT","CONTROL_POWER","READ_CURRENT_CHANNEL","READ_RUNNING_APPS",
      "READ_UPDATE_INFO","UPDATE_FROM_REMOTE_APP","READ_LGE_TV_INPUT_EVENTS","READ_TV_CURRENT_TIME"],
    "serial": "2f930e2d2cfe083771f68e4fe7bb07"
  },
  "permissions": ["LAUNCH","LAUNCH_WEBAPP","APP_TO_APP","CONTROL_AUDIO","CONTROL_DISPLAY",
    "CONTROL_INPUT_JOYSTICK","CONTROL_INPUT_MEDIA_RECORDING","CONTROL_INPUT_MEDIA_PLAYBACK",
    "CONTROL_INPUT_TV","CONTROL_POWER","READ_APP_STATUS","READ_CURRENT_CHANNEL",
    "READ_INPUT_DEVICE_LIST","READ_NETWORK_STATE","READ_TV_CHANNEL_LIST",
    "WRITE_NOTIFICATION_TOAST","READ_POWER_STATE","READ_COUNTRY_INFO","READ_INSTALLED_APPS",
    "CONTROL_INPUT_TEXT","CONTROL_MOUSE_AND_KEYBOARD"],
  "signatures": [{
    "signatureVersion": 1,
    "signature": "eyJhbGdvcml0aG0iOiJSU0EtU0hBMjU2Iiwia2V5SWQiOiJ0ZXN0LXNpZ25pbmctY2VydCIsIm"
  }]
})JSON";

/* Die Kennungen der Tonausgabe sind fuer sich genommen unverstaendlich. */
QString prettySoundOutput(const QString &id)
{
    if (id == QLatin1String("external_arc"))     return QStringLiteral("HDMI ARC (external_arc)");
    if (id == QLatin1String("external_speaker")) return LgTv::tr("external speaker");
    if (id == QLatin1String("external_optical")) return LgTv::tr("optical");
    if (id == QLatin1String("tv_speaker"))       return LgTv::tr("TV speaker");
    if (id == QLatin1String("bt_soundbar"))      return LgTv::tr("Bluetooth soundbar");
    if (id == QLatin1String("tv_external_speaker"))
        return LgTv::tr("TV speaker + external");
    return id.isEmpty() ? LgTv::tr("unknown") : id;
}

} // namespace

LgTv::LgTv(QObject *parent)
    : QObject(parent)
    , m_main(QString(), QWebSocketProtocol::VersionLatest)
    , m_pointer(QString(), QWebSocketProtocol::VersionLatest)
    , m_host(QStringLiteral(""))
    , m_status(tr("disconnected"))
{
    connect(&m_main, &QWebSocket::connected, this, &LgTv::onMainConnected);
    connect(&m_main, &QWebSocket::disconnected, this, &LgTv::onMainDisconnected);
    connect(&m_main, &QWebSocket::textMessageReceived, this, &LgTv::onMainMessage);

    connect(&m_pointer, &QWebSocket::connected, this, &LgTv::onPointerConnected);
    connect(&m_pointer, &QWebSocket::disconnected, this, &LgTv::onPointerDisconnected);

    // Jede Antwort des Fernsehers zaehlt als Lebenszeichen, auch das Pong
    connect(&m_main, &QWebSocket::pong, this, [this](quint64, const QByteArray &) {
        m_alive = true;
    });

    m_connect = new QTimer(this);
    m_connect->setSingleShot(true);
    m_connect->setInterval(kHandshakeWait);
    connect(m_connect, &QTimer::timeout, this, [this]() {
        if (m_main.state() == QAbstractSocket::ConnectedState)
            return;
        ErrorLog::note(tr("Connection"), tr("no answer during the TLS handshake"),
                       m_host);
        setStatus(tr("no answer while connecting"));
        m_main.abort();
        scheduleRetry();
    });

    m_beat = new QTimer(this);
    m_beat->setInterval(20000);
    connect(m_beat, &QTimer::timeout, this, &LgTv::probe);

    m_watch = new QTimer(this);
    m_watch->setSingleShot(true);
    m_watch->setInterval(8000);
    connect(m_watch, &QTimer::timeout, this, [this]() {
        if (!m_alive)
            handleDrop();
    });

    m_retry = new QTimer(this);
    m_retry->setSingleShot(true);
    connect(m_retry, &QTimer::timeout, this, [this]() {
        /* Abstand erst danach verdoppeln: der erste Versuch kommt schnell.
           Deckel bei 15 s: jeder Versuch belegt einen der sechs Plaetze am
           Fernseher, und zwar bis er ihn von sich aus abraeumt. Der
           Wiederholer laeuft ohnehin nur im Vordergrund. */
        m_retryDelay = qMin(m_retryDelay * 2, kRetryCap);
        openMain();
    });

    // Beim Zurueckholen nachsehen, im Hintergrund ruhen
    connect(qGuiApp, &QGuiApplication::applicationStateChanged,
            this, &LgTv::onAppStateChanged);

    /* Der Fernseher nimmt 1.2 wie 1.3, weist Handshakes aber zeitweise ohne
       Antwort ab - in der App sichtbar als "Remote host closed the
       connection", dagegen hilft nur der Wiederholer. Die Version bleibt
       deshalb der Bibliothek ueberlassen, statt auf 1.2 festgenagelt zu sein. */
    QSslConfiguration ssl = QSslConfiguration::defaultConfiguration();
    ssl.setProtocol(QSsl::TlsV1_2OrLater);

    // Selbstsigniert, also beim ersten Mal merken und danach vergleichen
    auto pin = [this, &ssl](QWebSocket *s) {
        s->setSslConfiguration(ssl);
        connect(s, static_cast<void (QWebSocket::*)(const QList<QSslError> &)>(&QWebSocket::sslErrors),
                this, [this, s](const QList<QSslError> &errors) {
                    if (acceptCert(errors)) {
                        s->ignoreSslErrors();
                        return;
                    }
                    m_certBlocked = true;
                    ErrorLog::note(tr("Certificate"),
                                   tr("the TV shows a different certificate than the one remembered - reset the pairing"),
                                   m_host);
                    setStatus(tr("Certificate does not match - reset the pairing"));
                });
    };
    pin(&m_main);
    pin(&m_pointer);

    connect(&m_main, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
            this, [this](QAbstractSocket::SocketError) {
                ErrorLog::note(tr("Connection"), m_main.errorString(), m_host);
                setStatus(tr("Error: %1").arg(m_main.errorString()));
                emit failed(m_main.errorString());
                /* Scheitert schon der Verbindungsaufbau - Fernseher aus,
                   Netz noch nicht da -, kommt nur dieses Signal und kein
                   disconnected. Ohne den Anstoss hier bliebe es dabei. */
                scheduleRetry();
            });

    // Zertifikatsfehler sichtbar machen - sonst raet man bei TLS-Problemen
    connect(&m_main, static_cast<void (QWebSocket::*)(const QList<QSslError> &)>(&QWebSocket::sslErrors),
            this, [this](const QList<QSslError> &errors) {
                QStringList texts;
                for (const QSslError &e : errors)
                    texts << e.errorString();
                m_sslNote = texts.join(QStringLiteral(" | "));
                emit statusTextChanged();
            });
}

// Was bei einem fehlgeschlagenen Versuch zaehlt; steht in den Einstellungen
/* Eigener Handschlag, weil QtWebSockets 5.5 die ausgehandelte Sitzung nicht
   herausgibt. Ueber den Cipher gelesen - TlsV1_3 gibt es erst ab Qt 5.12. */
void LgTv::requestTlsInfo()
{
    if (m_host.isEmpty()) {
        m_tls = tr("not connected");
        emit tlsInfoChanged();
        return;
    }
    m_tlsTries = 0;
    probeTls();
}

// Ein Anlauf genuegt nicht, wenn die sechs Plaetze belegt sind
void LgTv::probeTls()
{
    QSslSocket *probe = new QSslSocket(this);
    probe->setProperty("done", false);

    // Gewachter Zeiger und Anschluesse am Socket: nach dem Abraeumen darf
    // nichts mehr zugreifen
    QPointer<QSslSocket> wache(probe);
    auto finish = [this, wache](const QString &text) {
        if (!wache || wache->property("done").toBool())
            return;
        wache->setProperty("done", true);
        wache->abort();
        wache->deleteLater();
        if (!text.isEmpty()) {
            m_tls = text;
            emit tlsInfoChanged();
            return;
        }
        // Leerer Text heisst: dieser Anlauf ging daneben
        if (++m_tlsTries >= kTlsTries) {
            m_tls = tr("no answer");
            emit tlsInfoChanged();
            return;
        }
        QTimer::singleShot(300, this, [this]() { probeTls(); });
    };

    connect(probe, &QSslSocket::encrypted, probe, [probe, finish]() {
        const QSslCipher c = probe->sessionCipher();
        finish(c.isNull() ? tr("unknown")
                          : QStringLiteral("%1, %2").arg(c.protocolString(), c.name()));
    });
    // Geprueft wird das Zertifikat am Hauptkanal
    connect(probe, static_cast<void (QSslSocket::*)(const QList<QSslError> &)>(&QSslSocket::sslErrors),
            probe, [probe](const QList<QSslError> &) { probe->ignoreSslErrors(); });
    connect(probe, static_cast<void (QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
            probe, [finish](QAbstractSocket::SocketError) { finish(QString()); });
    // Bleibt der Handschlag liegen, dann eben nicht
    QTimer::singleShot(kTlsWait, probe, [finish]() { finish(QString()); });

    probe->connectToHostEncrypted(m_host, 3001);
}

QString LgTv::diagnostics() const
{
    QStringList out;
    out << tr("SSL in the Qt build: %1").arg(QSslSocket::supportsSsl() ? tr("yes") : tr("NO"));
    out << tr("SSL library: %1").arg(QSslSocket::sslLibraryVersionString());
    out << tr("Target: wss://%1:3001").arg(m_host);
    if (!m_sslNote.isEmpty())
        out << tr("Certificate: %1").arg(m_sslNote);
    if (!m_lastError.isEmpty())
        out << tr("Last rejected request: %1").arg(m_lastError);
    return out.join(QStringLiteral("\n"));
}

void LgTv::setHost(const QString &h)
{
    if (h == m_host)
        return;
    m_host = h;
    emit hostChanged();
}

void LgTv::setClientKey(const QString &k)
{
    if (k == m_clientKey)
        return;
    m_clientKey = k;
    emit clientKeyChanged();
}

void LgTv::setCertFingerprint(const QString &f)
{
    if (f == m_certFingerprint)
        return;
    m_certFingerprint = f;
    m_certBlocked = false;
    emit certFingerprintChanged();
}

/* Erste Verbindung merkt den Fingerabdruck, spaetere muessen ihn zeigen.
   Welche Fehler das Zertifikat sonst hat, ist gleichgueltig - massgeblich
   ist, dass es dasselbe Geraet ist. */
/* Der TV schickt eine Kette; die Reihenfolge der Fehler liegt nicht in
   unserer Hand. Gemeint ist sein eigenes Zertifikat - jenes, das keinem
   anderen der Kette als Aussteller dient. */
bool LgTv::acceptCert(const QList<QSslError> &errors)
{
    QList<QSslCertificate> kette;
    for (const QSslError &e : errors) {
        const QSslCertificate c = e.certificate();
        if (!c.isNull() && !kette.contains(c))
            kette << c;
    }
    if (kette.isEmpty())
        return false;

    QSslCertificate blatt = kette.first();
    for (const QSslCertificate &c : kette) {
        bool istAussteller = false;
        for (const QSslCertificate &d : kette) {
            if (d != c && d.issuerInfo(QSslCertificate::CommonName)
                          == c.subjectInfo(QSslCertificate::CommonName)) {
                istAussteller = true;
                break;
            }
        }
        if (!istAussteller) {
            blatt = c;
            break;
        }
    }

    const QString shown = QString::fromLatin1(
        blatt.digest(QCryptographicHash::Sha256).toHex());
    if (m_certFingerprint.isEmpty()) {
        m_certFingerprint = shown;
        emit certFingerprintChanged();
        return true;
    }
    if (m_certFingerprint == shown)
        return true;

    // Aeltere Fassungen merkten sich womoeglich die Zwischenstelle
    for (const QSslCertificate &c : kette) {
        if (m_certFingerprint == QString::fromLatin1(
                c.digest(QCryptographicHash::Sha256).toHex())) {
            m_certFingerprint = shown;
            emit certFingerprintChanged();
            return true;
        }
    }

    qWarning() << "LgTv: fremdes Zertifikat" << shown << "erwartet" << m_certFingerprint;
    return false;
}

void LgTv::setStatus(const QString &s)
{
    if (s == m_status)
        return;
    m_status = s;
    emit statusTextChanged();
}

// ---------- Verbindung ----------

void LgTv::connectTv()
{
    disconnectTv();
    // ... dieser Versuch ist gewollt, disconnectTv hat das Gegenteil vermerkt
    m_userClosed = false;
    m_certBlocked = false;
    m_retryDelay = kFirstRetry;
    setStatus(tr("connecting ..."));
    openMain();
}

// Einziger Weg zum Hauptsocket; der Zustandstest schuetzt eine laufende
// Verbindung vor dem Wiederholer
void LgTv::openMain()
{
    if (m_main.state() != QAbstractSocket::UnconnectedState || m_certBlocked)
        return;
    if (m_host.isEmpty()) {
        setStatus(tr("no device"));
        return;
    }
    qWarning() << "LgTv: verbinde mit wss://" << m_host << ":3001";
    // Feste Wahl: wss auf 3001. Aktuelle Firmware bedient das offene
    // Port 3000 nicht mehr.
    m_main.open(QUrl(QStringLiteral("wss://%1:3001").arg(m_host)));
    m_connect->start();
}

void LgTv::disconnectTv()
{
    m_userClosed = true;
    m_connect->stop();
    m_retry->stop();
    stopBeat();
    m_pointer.close();
    m_main.close();
    m_linkUp = m_registered = m_pointerReady = false;
    m_pending.clear();
    m_subs.clear();
    m_textInputReady = false;
    m_power.clear();
    emit powerStateChanged();
    emit textInputChanged();
    emit stateChanged();
    setStatus(tr("disconnected"));
}

void LgTv::onMainConnected()
{
    m_connect->stop();
    qWarning() << "LgTv: Verbindung offen, melde an";
    m_linkUp = true;
    m_alive = true;
    m_retryDelay = kFirstRetry;
    emit stateChanged();
    sendRegister();
}

void LgTv::onMainDisconnected()
{
    m_connect->stop();
    m_linkUp = m_registered = m_pointerReady = false;
    m_power.clear();
    emit powerStateChanged();
    m_pending.clear();
    /* Die Abos galten fuer die alte Verbindung; nach der Neuanmeldung
       vergibt der Fernseher neue Kennungen. */
    m_subs.clear();
    stopBeat();
    emit stateChanged();

    if (m_userClosed)
        return;
    ErrorLog::note(tr("Connection"), tr("connection lost"), m_host);
    setStatus(tr("connection lost"));
    scheduleRetry();
}

// ---------- Lebenszeichen und Wiederverbinden ----------

void LgTv::startBeat()
{
    if (m_registered && qGuiApp->applicationState() == Qt::ApplicationActive)
        m_beat->start();
}

void LgTv::stopBeat()
{
    m_beat->stop();
    m_watch->stop();
}

/* Harmlose Abfrage; der Ping allein waere sparsamer, aber nicht jede
   Firmware beantwortet ihn. */
void LgTv::probe()
{
    if (!m_registered)
        return;
    m_alive = false;
    m_main.ping();
    request(QStringLiteral("ssap://audio/getStatus"), QJsonObject(), WantHeartbeat);
    m_watch->start();
}

// Tot trotz offenem Socket: abort() statt close(), auf einen Abschiedsgruss
// zu warten hat keinen Zweck
void LgTv::handleDrop()
{
    ErrorLog::note(tr("Connection"),
                   tr("no sign of life within 8 s - the connection counts as dead"), m_host);
    setStatus(tr("no answer from the TV"));
    m_pointer.abort();
    m_main.abort();
    // Falls abort() kein disconnected ausgeloest hat, den Weg selbst gehen
    if (m_linkUp || m_registered)
        onMainDisconnected();
}

void LgTv::scheduleRetry()
{
    if (m_userClosed || m_certBlocked || m_host.isEmpty() || m_retry->isActive())
        return;
    // Ein neuer Versuch laeuft bereits - etwa der aus connectTv()
    if (m_main.state() != QAbstractSocket::UnconnectedState)
        return;
    // Im Hintergrund ruhen; onAppStateChanged klopft beim Zurueckholen an
    if (qGuiApp->applicationState() != Qt::ApplicationActive)
        return;
    m_retry->start(m_retryDelay);
}

void LgTv::ensureConnected()
{
    if (m_userClosed)
        return;
    if (m_main.state() == QAbstractSocket::UnconnectedState) {
        m_retryDelay = kFirstRetry;
        setStatus(tr("connecting ..."));
        openMain();
        return;
    }
    // Sieht offen aus - nach dem Aufwachen ist das kein Beweis
    if (m_registered)
        probe();
}

void LgTv::onAppStateChanged(Qt::ApplicationState state)
{
    if (state == Qt::ApplicationActive) {
        ensureConnected();
        startBeat();
    } else {
        stopBeat();
        m_retry->stop();
    }
}

void LgTv::onPointerConnected()
{
    m_pointerReady = true;
    m_pointerTries = 0;
    emit stateChanged();
}

// Faellt der Tastenkanal weg, bleibt die Fernbedienung halb gesperrt
void LgTv::onPointerDisconnected()
{
    m_pointerReady = false;
    emit stateChanged();
    askPointer();
}

void LgTv::askPointer()
{
    if (!m_registered || m_userClosed || m_pointerReady)
        return;
    if (m_pointerTries >= kPointerTries) {
        ErrorLog::note(tr("Key channel"),
                       tr("the TV does not hand out the address for the key channel - arrow keys, OK and Back stay locked"),
                       m_host);
        setStatus(tr("key channel stays closed"));
        return;
    }
    const int wait = ++m_pointerTries * 1000;
    QTimer::singleShot(wait, this, [this]() {
        if (!m_registered || m_userClosed || m_pointerReady)
            return;
        request(QStringLiteral("ssap://com.webos.service.networkinput/getPointerInputSocket"),
                QJsonObject(), WantPointer);
    });
}

// ---------- Anmeldung ----------

void LgTv::sendRegister()
{
    QJsonParseError fehler;
    const QJsonObject manifest =
        QJsonDocument::fromJson(QByteArray(kManifest), &fehler).object();
    /* Ein unlesbares Manifest faellt sonst nirgends auf: der Fernseher
       antwortet auf die Anmeldung dann einfach nicht mehr. */
    if (manifest.isEmpty()) {
        ErrorLog::note(tr("Sign-on"),
                       tr("the built-in handshake is unreadable - pairing is impossible"),
                       fehler.errorString());
        setStatus(tr("Error: %1").arg(fehler.errorString()));
        return;
    }

    QJsonObject payload;
    payload.insert(QStringLiteral("forcePairing"), false);
    payload.insert(QStringLiteral("pairingType"), QStringLiteral("PROMPT"));
    payload.insert(QStringLiteral("manifest"), manifest);
    if (!m_clientKey.isEmpty())
        payload.insert(QStringLiteral("client-key"), m_clientKey);
    else
        emit pairingPrompt();

    setStatus(m_clientKey.isEmpty() ? tr("waiting for confirmation on the TV")
                                    : tr("signing in ..."));

    QJsonObject msg;
    msg.insert(QStringLiteral("id"), QStringLiteral("register_0"));
    msg.insert(QStringLiteral("type"), QStringLiteral("register"));
    msg.insert(QStringLiteral("payload"), payload);
    m_main.sendTextMessage(QString::fromUtf8(QJsonDocument(msg).toJson(QJsonDocument::Compact)));
}

// ---------- Nachrichten ----------

void LgTv::onMainMessage(const QString &text)
{
    // Jede Antwort beweist, dass die Verbindung noch traegt
    m_alive = true;
    m_watch->stop();

    const QJsonObject msg = QJsonDocument::fromJson(text.toUtf8()).object();
    const QString type = msg.value(QStringLiteral("type")).toString();
    const QJsonObject payload = msg.value(QStringLiteral("payload")).toObject();

    if (type == QLatin1String("registered")) {
        qWarning() << "LgTv: angemeldet";
        m_registered = true;
        m_pointerTries = 0;
        emit stateChanged();
        setStatus(tr("connected"));

        const QString key = payload.value(QStringLiteral("client-key")).toString();
        if (!key.isEmpty() && key != m_clientKey) {
            m_clientKey = key;
            emit clientKeyChanged();
        }
        request(QStringLiteral("ssap://com.webos.service.networkinput/getPointerInputSocket"),
                QJsonObject(), WantPointer);
        // Abonnieren statt pollen: so wird die Anzeige auch dann richtig,
        // wenn jemand die Originalfernbedienung benutzt.
        subscribe(QStringLiteral("ssap://audio/getVolume"), WantVolume);
        subscribe(QStringLiteral("ssap://tv/getCurrentChannel"), WantChannel);
        /* Der Einschaltzustand. Ohne ihn gilt eine stehende Verbindung als
           "Fernseher an" - im Netzwerk-Standby ist das falsch. */
        subscribe(QStringLiteral("ssap://com.webos.service.tvpower/power/getPowerState"),
                  WantPower);
        // Das Abo meldet Aenderungen; der Stand von jetzt kommt auf Nachfrage
        requestPowerState();
        /* Ohne angemeldete Fernbedienungstastatur ordnet der TV Text keinem
           Feld zu und verwirft ihn - am Geraet nachgewiesen. */
        subscribe(QStringLiteral("ssap://com.webos.service.ime/registerRemoteKeyboard"),
                  WantKeyboard);
        /* getForegroundAppInfo waere naheliegender, wird unserem Schluessel
           aber mit "401 insufficient permissions" beantwortet. */
        subscribe(QStringLiteral("ssap://system.launcher/getAppState"), WantAppState,
                  ytPayload());
        refreshVolume();
        refreshChannel();
        // liefert die MAC zum Aufwecken; die Suche im Netz kann sie nicht
        m_netTries = 0;
        requestNetworkInfo();
        /* Nennt der Fernseher seinen Einschaltzustand nicht, kann die
           Geraeteliste "an" nicht von "Bereitschaft" unterscheiden. Dann
           soll wenigstens dastehen, woran es liegt. */
        QTimer::singleShot(5000, this, [this]() {
            if (m_registered && m_power.isEmpty())
                ErrorLog::note(tr("power state"),
                               tr("the TV does not state whether it is running - the device list cannot tell on from standby"),
                               m_host);
        });
        startBeat();
        return;
    }

    if (type == QLatin1String("error")) {
        const QString err = msg.value(QStringLiteral("error")).toString();

        /* Nach der Anmeldung betrifft ein Fehler nur die eine Abfrage -
           nicht die Verbindung und nicht den Schluessel. */
        if (m_registered) {
            m_lastError = err;
            emit statusTextChanged();
            // Die Abfrage ist weg, der Auftrag darf es nicht sein
            const QString fid = msg.value(QStringLiteral("id")).toString();
            /* Abonnements stehen in m_subs, nicht in m_pending. Ohne diesen
               Blick liefe jeder abgewiesene Dauerauftrag namenlos als
               "Befehl" ins Protokoll. */
            const Pending offen = m_pending.contains(fid) ? m_pending.take(fid)
                                                          : m_subs.value(fid);
            /* Drei Abfuhren sind eingeplant und haben ihren eigenen Weg.
               getAppState wird auf mancher Firmware grundsaetzlich abgewiesen
               (dann wird YouTube neu gestartet), der Tastenkanal wird ohnehin
               wiederholt erfragt, und der Kanal ist bei laufendem
               HDMI-Eingang schlicht keiner. Alle drei antworten unten selbst -
               im Protokoll haetten sie nur bei jeder Anmeldung dasselbe
               wiederholt. */
            const bool eingeplant = offen.want == WantAppState || offen.want == WantPointer
                                    || offen.want == WantChannel;
            if (!eingeplant)
                ErrorLog::note(wantName(offen.want), err,
                               offen.uri.isEmpty() ? m_host : offen.uri);
            if (offen.want == WantAppState) {
                relaunchYouTube();
            } else if (offen.want == WantPointer) {
                askPointer();
            } else if (offen.want == WantNetwork) {
                chaseNetworkInfo();
            } else if (offen.want == WantChannel) {
                /* Kein Kanal ist kein Fehler: auf einem HDMI-Eingang gibt es
                   keinen. Die Anzeige muss dann leer sein und nicht den
                   letzten Sender von vorgestern zeigen. */
                if (!m_channel.isEmpty()) {
                    m_channel.clear();
                    emit channelChanged();
                }
            }
            return;
        }

        ErrorLog::note(tr("Sign-on"), err, m_host);
        setStatus(tr("Error: %1").arg(err));
        emit failed(err);
        // Nur eine abgelehnte Anmeldung entwertet den Schluessel
        if (err.contains(QLatin1String("401"))) {
            m_clientKey.clear();
            emit clientKeyChanged();
        }
        return;
    }

    const QString id = msg.value(QStringLiteral("id")).toString();
    if (m_subs.contains(id))
        handlePayload(m_subs.value(id).want, payload);   // bleibt bestehen
    else if (m_pending.contains(id))
        handlePayload(m_pending.take(id).want, payload);
}

/* Klartext fuer das Protokoll - eine SSAP-Adresse sagt dem Nutzer nichts. */
QString LgTv::wantName(Want want)
{
    switch (want) {
    case WantVolume:     return tr("volume");
    case WantPointer:    return tr("key channel");
    case WantApps:       return tr("app list");
    case WantInputs:     return tr("input list");
    case WantSystem:     return tr("system data");
    case WantNetwork:    return tr("network data (MAC address)");
    case WantAudio:      return tr("sound settings");
    case WantChannel:    return tr("channel");
    case WantPower:      return tr("power state");
    case WantKeyboard:   return tr("remote keyboard");
    case WantTextResult: return tr("text entry");
    case WantAppState:   return tr("app state");
    case WantHeartbeat:  return tr("sign of life");
    case WantCapture:    return tr("screenshot");
    case WantNothing:    break;
    }
    return tr("command");
}

/* Abonnement: der Fernseher meldet Aenderungen von sich aus. */
void LgTv::subscribe(const QString &uri, Want want, const QJsonObject &payload)
{
    const QString id = QStringLiteral("sub_%1").arg(++m_counter);
    m_subs.insert(id, Pending{ want, uri });
    QJsonObject msg;
    msg.insert(QStringLiteral("id"), id);
    msg.insert(QStringLiteral("type"), QStringLiteral("subscribe"));
    msg.insert(QStringLiteral("uri"), uri);
    msg.insert(QStringLiteral("payload"), payload);
    m_main.sendTextMessage(QString::fromUtf8(QJsonDocument(msg).toJson(QJsonDocument::Compact)));
}

QString LgTv::request(const QString &uri, const QJsonObject &payload, Want want)
{
    /* Alles hier hindurch setzt eine angemeldete Verbindung voraus. Wer den
       Fernseher im Bereitschaftsbetrieb bedient, soll nicht raten muessen,
       warum nichts geschieht. */
    if (!m_registered && want != WantPointer) {
        ErrorLog::note(tr("Command not sent"),
                       tr("not signed on to the TV"), uri);
        return QString();
    }

    const QString id = QStringLiteral("req_%1").arg(++m_counter);
    /* Auch die Befehle ohne erwartete Antwort werden vermerkt: der Fernseher
       beantwortet jede Anfrage, und ein Fehler soll seine Adresse nennen. */
    m_pending.insert(id, Pending{ want, uri });

    QJsonObject msg;
    msg.insert(QStringLiteral("id"), id);
    msg.insert(QStringLiteral("type"), QStringLiteral("request"));
    msg.insert(QStringLiteral("uri"), uri);
    msg.insert(QStringLiteral("payload"), payload);
    m_main.sendTextMessage(QString::fromUtf8(QJsonDocument(msg).toJson(QJsonDocument::Compact)));
    return id;
}

void LgTv::handlePayload(Want want, const QJsonObject &payload)
{
    switch (want) {
    case WantHeartbeat:
        // Angekommen ist genug - der Inhalt interessiert nicht
        break;
    case WantPointer: {
        const QString path = payload.value(QStringLiteral("socketPath")).toString();
        if (path.isEmpty()) {
            ErrorLog::note(tr("Key channel"),
                           tr("the TV answered without an address for the key channel"), m_host);
            askPointer();
        } else {
            m_pointer.open(QUrl(path));
        }
        break;
    }
    case WantVolume: {
        // Je nach Firmware liegen die Werte direkt oder unter volumeStatus
        QJsonObject src = payload;
        if (payload.contains(QStringLiteral("volumeStatus")))
            src = payload.value(QStringLiteral("volumeStatus")).toObject();
        if (src.contains(QStringLiteral("volume")))
            m_volume = src.value(QStringLiteral("volume")).toInt(-1);
        if (src.contains(QStringLiteral("muted")))
            m_muted = src.value(QStringLiteral("muted")).toBool();
        else if (src.contains(QStringLiteral("muteStatus")))
            m_muted = src.value(QStringLiteral("muteStatus")).toBool();

        /* Nur an den TV-Lautsprechern ist der Wert echt. Ueber ARC ist es ein
           Zaehler - das Geraet meldet seinen Pegel nie zurueck (CEC gemessen). */
        const QString out = src.value(QStringLiteral("soundOutput")).toString();
        if (!out.isEmpty() && out != m_soundOutput)
            m_soundOutput = out;
        m_volumeReliable = src.value(QStringLiteral("volumeSyncable")).toBool()
                           || m_soundOutput == QLatin1String("tv_speaker")
                           || m_soundOutput.isEmpty();
        emit volumeChanged();
        break;
    }
    case WantApps: {
        QVariantList out;
        const QJsonArray points = payload.value(QStringLiteral("launchPoints")).toArray();
        for (const QJsonValue &v : points) {
            const QJsonObject o = v.toObject();
            const QString title = o.value(QStringLiteral("title")).toString();
            if (title.isEmpty())
                continue;   // Systemeintraege ohne Titel sind unbedienbar
            QVariantMap m;
            m.insert(QStringLiteral("ident"), o.value(QStringLiteral("id")).toString());
            m.insert(QStringLiteral("label"), title);
            m.insert(QStringLiteral("icon"), o.value(QStringLiteral("icon")).toString());
            out.append(m);
        }
        // Der Fernseher liefert ungeordnet - Live TV stand auf Platz 31
        std::sort(out.begin(), out.end(), [](const QVariant &a, const QVariant &b) {
            return a.toMap().value(QStringLiteral("label")).toString().localeAwareCompare(
                       b.toMap().value(QStringLiteral("label")).toString()) < 0;
        });
        emit appsReceived(out);
        break;
    }
    case WantInputs: {
        QVariantList out;
        const QJsonArray devices = payload.value(QStringLiteral("devices")).toArray();
        for (const QJsonValue &v : devices) {
            const QJsonObject o = v.toObject();
            const QString id = o.value(QStringLiteral("id")).toString();
            QVariantMap m;
            m.insert(QStringLiteral("ident"), id);
            const QString label = o.value(QStringLiteral("label")).toString();
            m.insert(QStringLiteral("label"), label.isEmpty() ? id : label);
            m.insert(QStringLiteral("icon"), o.value(QStringLiteral("icon")).toString());
            out.append(m);
        }
        emit inputsReceived(out);
        break;
    }
    case WantTextResult: {
        // Ohne diese Antwort sendet die App blind
        const bool ok = payload.value(QStringLiteral("returnValue")).toBool();
        if (!ok)
            ErrorLog::note(tr("Text entry"), tr("the TV rejected the text"),
                           payload.value(QStringLiteral("errorText")).toString());
        m_lastError = ok ? tr("insertText: accepted")
                         : tr("insertText rejected: %1").arg(payload.value(QStringLiteral("errorText")).toString());
        emit statusTextChanged();
        break;
    }
    case WantKeyboard: {
        // focus=false heisst: kein Feld offen, Text waere verloren
        const QJsonObject w = payload.value(QStringLiteral("currentWidget")).toObject();
        const bool ready = w.value(QStringLiteral("focus")).toBool();
        const QString type = w.value(QStringLiteral("contentType")).toString();
        const int len = w.value(QStringLiteral("surroundingTextLength")).toInt();
        if (ready != m_textInputReady || type != m_textInputType || len != m_textInputLength) {
            m_textInputReady = ready;
            m_textInputType = type;
            m_textInputLength = len;
            emit textInputChanged();
        }
        break;
    }
    case WantAppState: {
        const bool sichtbar = payload.value(QStringLiteral("visible")).toBool();
        const bool laeuft = payload.value(QStringLiteral("running")).toBool();
        if (sichtbar != m_ytVisible) {
            m_ytVisible = sichtbar;
            emit foregroundAppChanged();
        }
        m_ytRunning = laeuft;

        /* Sichtbar: der Begriff geht im Lauf hinein. Im Hintergrund wuerde
           ein Start nur benachrichtigen - deshalb erst schliessen. */
        if (!m_pendingSearch.isNull()) {
            const QString begriff = m_pendingSearch;
            m_pendingSearch = QString();
            if (sichtbar) {
                launchYouTube(begriff);
            } else {
                if (laeuft) {
                    QJsonObject p;
                    p.insert(QStringLiteral("id"), QStringLiteral(YT_APP));
                    request(QStringLiteral("ssap://system.launcher/close"), p, WantNothing);
                }
                QTimer::singleShot(laeuft ? 600 : 0, this,
                                   [this, begriff]() { launchYouTube(begriff); });
            }
        }
        break;
    }
    case WantCapture: {
        const QString uri = payload.value(QStringLiteral("imageUri")).toString();
        if (uri.isEmpty()) {
            ErrorLog::note(tr("Screenshot"),
                           tr("the TV took the order but names no image"), m_host);
            setStatus(tr("no screenshot from the TV"));
        }
        else
            emit captureReady(uri);
        break;
    }
    case WantPower: {
        /* Bekannte Werte: Active, Screen Off, Screen Saver, Active Standby,
           Suspend, Power Off. Bei "processing" ist der Fernseher im Uebergang
           und meldet gleich noch einmal. */
        const QString zustand = payload.value(QStringLiteral("state")).toString();
        if (!zustand.isEmpty() && zustand != m_power) {
            m_power = zustand;
            emit powerStateChanged();
        }
        break;
    }
    case WantChannel: {
        // Nummer und Name zusammensetzen, soweit vorhanden
        const QString nr = payload.value(QStringLiteral("channelNumber")).toString();
        const QString name = payload.value(QStringLiteral("channelName")).toString();
        QString text = nr;
        if (!name.isEmpty())
            text += (nr.isEmpty() ? QString() : QStringLiteral("  ")) + name;
        if (text != m_channel) {
            m_channel = text;
            emit channelChanged();
        }
        break;
    }
    case WantSystem: {
        QVariantMap m;
        m.insert(tr("Model"), payload.value(QStringLiteral("modelName")).toString());
        m.insert(tr("Serial number"), payload.value(QStringLiteral("serialNumber")).toString());
        emit systemInfoReceived(m);

        const QString modell = payload.value(QStringLiteral("modelName")).toString();
        const QString nummer = payload.value(QStringLiteral("serialNumber")).toString();
        if (modell != m_model || nummer != m_serial) {
            m_model = modell;
            m_serial = nummer;
            emit deviceInfoChanged();
        }
        // Das Empfangsteil ist technisch ein Eingang und steht dort
        emit tunerReceived(payload.value(QStringLiteral("receiverType")).toString());
        break;
    }
    case WantNetwork: {
        QVariantMap m;
        const QStringList keys = { QStringLiteral("wiredInfo"), QStringLiteral("wifiInfo"),
                                   QStringLiteral("p2pInfo") };
        const QStringList names = { tr("MAC wired"), tr("MAC Wi-Fi"),
                                    tr("MAC direct link") };
        // MAC zum Aufwecken: Schnittstelle mit unserer IP, sonst die erste
        // verbundene. p2p nie - nicht anfunkbar.
        QString wakeMac;
        bool byAddress = false;
        for (int i = 0; i < keys.size(); ++i) {
            const QJsonObject o = payload.value(keys.at(i)).toObject();
            const QString mac = o.value(QStringLiteral("macAddress")).toString().toLower();
            if (!mac.isEmpty())
                m.insert(names.at(i), mac);
            const QString ip = o.value(QStringLiteral("ipAddress")).toString();
            if (!ip.isEmpty())
                m.insert(names.at(i) + tr(" - IP"), ip);

            if (mac.isEmpty() || byAddress
                || keys.at(i) == QLatin1String("p2pInfo"))
                continue;
            if (!ip.isEmpty() && ip == m_host) {
                wakeMac = mac;
                byAddress = true;
            } else if (wakeMac.isEmpty()
                       && o.value(QStringLiteral("state")).toString()
                              .compare(QLatin1String("connected"), Qt::CaseInsensitive) == 0) {
                wakeMac = mac;
            }
        }
        /* Am eigenen Geraet gemessen (23.08.2026): Diese Firmware nennt zu
           den Schnittstellen weder ipAddress noch state, nur je eine MAC -
           und davon drei. Welche die richtige ist, laesst sich daraus nicht
           entscheiden. Also wird gar nicht entschieden: Das Weckpaket ist
           eine Rundsendung, zwei davon kosten nichts. p2p bleibt draussen,
           die Strecke ist nicht anfunkbar. */
        QStringList alle;
        for (int i = 0; i < keys.size(); ++i) {
            if (keys.at(i) == QLatin1String("p2pInfo"))
                continue;
            const QString mac = payload.value(keys.at(i)).toObject()
                                    .value(QStringLiteral("macAddress")).toString().toLower();
            if (!mac.isEmpty() && !alle.contains(mac))
                alle.append(mac);
        }
        // Die per Adresse oder Zustand erkannte zuerst - sie steht im Eintrag
        if (!wakeMac.isEmpty()) {
            alle.removeAll(wakeMac);
            alle.prepend(wakeMac);
        }

        emit networkInfoReceived(m);
        if (!alle.isEmpty()) {
            m_netTries = 0;
            emit macsDiscovered(alle);
        } else {
            ErrorLog::note(tr("MAC address"),
                           tr("the TV answered without a MAC address - no wake-on-LAN possible"),
                           m_host);
            chaseNetworkInfo();
        }
        break;
    }
    case WantAudio: {
        const QJsonObject v = payload.value(QStringLiteral("volumeStatus")).toObject();
        QVariantMap m;
        const QString out = v.value(QStringLiteral("soundOutput")).toString();
        m.insert(tr("Sound output"), prettySoundOutput(out));
        m.insert(tr("Volume"),
                 tr("%1 of %2").arg(v.value(QStringLiteral("volume")).toInt())
                     .arg(v.value(QStringLiteral("maxVolume")).toInt()));
        // Zustand, keine Faehigkeit - daher an/aus statt ja/nein
        m.insert(tr("Mute"),
                 v.value(QStringLiteral("muteStatus")).toBool() ? tr("on") : tr("off"));
        m.insert(tr("External control"),
                 v.value(QStringLiteral("externalDeviceControl")).toBool() ? tr("yes") : tr("no"));
        m.insert(tr("Volume adjustable"),
                 v.value(QStringLiteral("adjustVolume")).toBool() ? tr("yes") : tr("no"));
        emit audioStatusReceived(m);
        break;
    }
    default:
        break;
    }
}

// ---------- Tastenkanal ----------

void LgTv::button(const QString &name)
{
    if (!m_pointerReady) {
        ErrorLog::note(tr("Key"), tr("key channel not open - keystroke discarded"), name);
        return;
    }
    m_pointer.sendTextMessage(QStringLiteral("type:button\nname:%1\n\n").arg(name));
}

void LgTv::move(int dx, int dy)
{
    if (!m_pointerReady)
        return;
    m_moveX += dx;
    m_moveY += dy;

    if (!m_moveTimer) {
        m_moveTimer = new QTimer(this);
        m_moveTimer->setInterval(40);
        connect(m_moveTimer, &QTimer::timeout, this, &LgTv::flushMove);
    }
    if (!m_moveTimer->isActive()) {
        flushMove();            // erster Schritt sofort
        m_moveTimer->start();
    }
}

void LgTv::flushMove()
{
    if (m_moveX == 0 && m_moveY == 0) {
        m_moveTimer->stop();
        return;
    }
    m_pointer.sendTextMessage(
        QStringLiteral("type:move\ndx:%1\ndy:%2\ndown:0\n\n").arg(m_moveX).arg(m_moveY));
    m_moveX = m_moveY = 0;
}

void LgTv::click()
{
    if (!m_pointerReady) {
        ErrorLog::note(tr("Pointer"), tr("key channel not open - click discarded"), m_host);
        return;
    }
    m_pointer.sendTextMessage(QStringLiteral("type:click\n\n"));
}

void LgTv::scroll(int dx, int dy)
{
    if (!m_pointerReady)
        return;
    m_pointer.sendTextMessage(
        QStringLiteral("type:scroll\ndx:%1\ndy:%2\n\n").arg(dx).arg(dy));
}

// ---------- Texteingabe ----------

void LgTv::insertText(const QString &text)
{
    /* Ohne offenes Feld nimmt der Fernseher den Text an und wirft ihn weg -
       am Geraet nachgewiesen. Das ist keine Panne, sondern ein Zustand, ueber
       den sich berichten laesst. */
    if (!m_textInputReady)
        ErrorLog::note(tr("Text entry"),
                       tr("no input field focused on the TV - the text may be discarded"),
                       text.left(40));
    QJsonObject p;
    p.insert(QStringLiteral("text"), text);
    p.insert(QStringLiteral("replace"), 0);
    request(QStringLiteral("ssap://com.webos.service.ime/insertText"), p, WantTextResult);
}

void LgTv::clearRemoteField()
{
    if (m_textInputLength > 0)
        deleteCharacters(m_textInputLength);
}

void LgTv::deleteCharacters(int count)
{
    QJsonObject p;
    p.insert(QStringLiteral("count"), count);
    request(QStringLiteral("ssap://com.webos.service.ime/deleteCharacters"), p, WantNothing);
}

void LgTv::sendEnter()
{
    request(QStringLiteral("ssap://com.webos.service.ime/sendEnterKey"),
            QJsonObject(), WantNothing);
}

// ---------- Befehle ----------

/* Schritte sammeln und im Takt abgeben: der TV zaehlt jeden Befehl mit und
   reicht ihn per CEC weiter, die Anlage schafft aber nicht jeden. */
void LgTv::stepVolume(int delta)
{
    m_volSteps += delta;

    if (!m_volTimer) {
        m_volTimer = new QTimer(this);
        m_volTimer->setInterval(200);
        connect(m_volTimer, &QTimer::timeout, this, [this]() {
            if (m_volSteps == 0) {
                m_volTimer->stop();
                return;              // das Abonnement meldet den Stand von selbst
            }
            const bool up = m_volSteps > 0;
            m_volSteps += up ? -1 : 1;
            request(up ? QStringLiteral("ssap://audio/volumeUp")
                       : QStringLiteral("ssap://audio/volumeDown"),
                    QJsonObject(), WantNothing);
        });
    }

    if (!m_volTimer->isActive()) {
        // Der erste Schritt sofort, damit es sich nicht traege anfuehlt
        const bool up = m_volSteps > 0;
        m_volSteps += up ? -1 : 1;
        request(up ? QStringLiteral("ssap://audio/volumeUp")
                   : QStringLiteral("ssap://audio/volumeDown"),
                QJsonObject(), WantNothing);
        m_volTimer->start();
    }
}

void LgTv::volumeUp()   { stepVolume(+1); }
void LgTv::volumeDown() { stepVolume(-1); }

void LgTv::setMute(bool on)
{
    QJsonObject p;
    p.insert(QStringLiteral("mute"), on);
    request(QStringLiteral("ssap://audio/setMute"), p, WantNothing);
    m_muted = on;
    emit volumeChanged();
}

/* Gemessen: setVolume verstellt nur den Zaehler des TV, ueber CEC geht dabei
   nichts hinaus. Genau deshalb taugt es zum Abgleich der Anzeige. */
void LgTv::setVolume(int v)
{
    if (v < 0) v = 0;
    if (v > 100) v = 100;
    QJsonObject p;
    p.insert(QStringLiteral("volume"), v);
    request(QStringLiteral("ssap://audio/setVolume"), p, WantNothing);
    m_volume = v;
    emit volumeChanged();
}

void LgTv::changeSoundOutput(const QString &out)
{
    QJsonObject p;
    p.insert(QStringLiteral("output"), out);
    request(QStringLiteral("ssap://audio/changeSoundOutput"), p, WantNothing);
    refreshVolume();
}

void LgTv::refreshVolume()
{
    request(QStringLiteral("ssap://audio/getVolume"), QJsonObject(), WantVolume);
}

void LgTv::refreshChannel()
{
    request(QStringLiteral("ssap://tv/getCurrentChannel"), QJsonObject(), WantChannel);
}

// Der TV braucht einen Moment, sonst kommt noch der alte Kanal
void LgTv::channelUp()
{
    request(QStringLiteral("ssap://tv/channelUp"), QJsonObject(), WantNothing);
    QTimer::singleShot(700, this, &LgTv::refreshChannel);
}

void LgTv::channelDown()
{
    request(QStringLiteral("ssap://tv/channelDown"), QJsonObject(), WantNothing);
    QTimer::singleShot(700, this, &LgTv::refreshChannel);
}

void LgTv::openChannel(const QString &number)
{
    QJsonObject p;
    p.insert(QStringLiteral("channelNumber"), number);
    request(QStringLiteral("ssap://tv/openChannel"), p, WantNothing);
    QTimer::singleShot(700, this, &LgTv::refreshChannel);
}

void LgTv::turnOff()
{
    request(QStringLiteral("ssap://system/turnOff"), QJsonObject(), WantNothing);
    /* Das Abo meldet den Uebergang meist von selbst. Meist ist zu wenig: sonst
       stuende die Anzeige bis zum naechsten Lebenszeichen auf gruen, also bis
       zu halbe Minute lang falsch. */
    QTimer::singleShot(1500, this, &LgTv::requestPowerState);
    QTimer::singleShot(5000, this, &LgTv::requestPowerState);
}

bool LgTv::awake() const
{
    return m_power == QLatin1String("Active")
           || m_power == QLatin1String("Screen Off")
           || m_power == QLatin1String("Screen Saver");
}

void LgTv::requestPowerState()
{
    request(QStringLiteral("ssap://com.webos.service.tvpower/power/getPowerState"),
            QJsonObject(), WantPower);
}

/* YouTube meldet handlesRelaunch: liegt die App im Hintergrund, holt
   ein Startbefehl sie nicht nach vorn. Deshalb denselben Umweg wie die Suche
   gehen - leerer Begriff heisst "nur oeffnen". */
void LgTv::launchApp(const QString &id)
{
    if (id == QLatin1String(YT_APP)) {
        m_pendingSearch = QStringLiteral("");
        refreshYouTubeState();
        return;
    }
    QJsonObject p;
    p.insert(QStringLiteral("id"), id);
    request(QStringLiteral("ssap://system.launcher/launch"), p, WantNothing);
}

QJsonObject LgTv::ytPayload()
{
    QJsonObject p;
    p.insert(QStringLiteral("id"), QStringLiteral(YT_APP));
    return p;
}

void LgTv::launchYouTube(const QString &begriff)
{
    QJsonObject p = ytPayload();
    if (!begriff.isEmpty()) {
        QJsonObject params;
        params.insert(QStringLiteral("target"), QStringLiteral("q=") + begriff);
        p.insert(QStringLiteral("params"), params);
    }
    request(QStringLiteral("ssap://system.launcher/launch"), p, WantNothing);
}

void LgTv::searchYouTube(const QString &text)
{
    const QString begriff = text.trimmed();
    if (begriff.isEmpty())
        return;
    m_pendingSearch = begriff;
    note(tr("YouTube: %1").arg(begriff));
    refreshYouTubeState();
}

void LgTv::refreshYouTubeState()
{
    request(QStringLiteral("ssap://system.launcher/getAppState"), ytPayload(), WantAppState);
}

/* getAppState wird mit "403 access denied" abgewiesen. Ohne Zustandsauskunft
   bleibt nur schliessen und neu starten. */
void LgTv::relaunchYouTube()
{
    if (m_pendingSearch.isNull())
        return;
    const QString begriff = m_pendingSearch;
    m_pendingSearch = QString();
    request(QStringLiteral("ssap://system.launcher/close"), ytPayload(), WantNothing);
    QTimer::singleShot(600, this, [this, begriff]() { launchYouTube(begriff); });
}

void LgTv::switchInput(const QString &id)
{
    QJsonObject p;
    p.insert(QStringLiteral("inputId"), id);
    request(QStringLiteral("ssap://tv/switchInput"), p, WantNothing);
}

/* Eigener Dienst, nicht system.launcher: homeconnect oeffnet den ganzen Hub,
   und ueber den Tastenkanal gibt es keinen Namen dafuer (44 geprueft). */
void LgTv::showInputPicker()
{
    request(QStringLiteral("ssap://com.webos.surfacemanager/showInputPicker"),
            QJsonObject(), WantNothing);
}

void LgTv::captureScreen()
{
    request(QStringLiteral("ssap://tv/executeOneShot"), QJsonObject(), WantCapture);
}

void LgTv::requestApps()
{
    request(QStringLiteral("ssap://com.webos.applicationManager/listLaunchPoints"),
            QJsonObject(), WantApps);
}

void LgTv::requestInputs()
{
    request(QStringLiteral("ssap://tv/getExternalInputList"), QJsonObject(), WantInputs);
}

// ---------- Systemdaten ----------

void LgTv::requestSystemInfo()
{
    request(QStringLiteral("ssap://system/getSystemInfo"), QJsonObject(), WantSystem);
}

void LgTv::requestNetworkInfo()
{
    request(QStringLiteral("ssap://com.webos.service.connectionmanager/getinfo"),
            QJsonObject(), WantNetwork);
}

/* Die MAC gibt es nur hier, und ohne sie laesst sich der Fernseher nicht mehr
   einschalten - deshalb wird nachgefasst statt aufgegeben. Zwei weitere
   Versuche mit Abstand; danach steht der Grund im Protokoll. */
void LgTv::chaseNetworkInfo()
{
    if (++m_netTries > 3) {
        ErrorLog::note(tr("MAC address"),
                       tr("asked three times without success - enter the MAC by hand under Connected devices"),
                       m_host);
        return;
    }
    QTimer::singleShot(m_netTries * 2000, this, [this]() {
        if (m_registered)
            requestNetworkInfo();
    });
}

void LgTv::requestAudioStatus()
{
    request(QStringLiteral("ssap://audio/getStatus"), QJsonObject(), WantAudio);
}

