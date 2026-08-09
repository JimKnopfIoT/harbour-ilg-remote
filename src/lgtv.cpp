#include "lgtv.h"

#include <QJsonArray>
#include <QSslConfiguration>
#include <QStringList>
#include <QSslSocket>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>
#include <QTimer>
#include <QUrl>

/* Unsere werbefreie YouTube-App. Nicht youtube.leanback.v4 - diese ID gehoert
   der eingebauten App mit Werbung, siehe DEV-APPS.md. */
#define YT_APP "youtube.leanback.v4"

namespace {

/* Der Anmelde-Handshake, den LG-Fernseher erwarten. Der signed-Block wird
   von der Firmware nicht geprueft, muss aber vorhanden sein. */
const char *kManifest = R"JSON({
  "manifestVersion": 1,
  "appVersion": "1.0",
  "signed": {
    "created": "20140509",
    "appId": "com.lge.test",
    "vendorId": "com.lge",
    "localizedAppNames": { "": "LG Fernbedienung" },
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
    if (id == QLatin1String("external_speaker")) return QStringLiteral("externer Lautsprecher");
    if (id == QLatin1String("external_optical")) return QStringLiteral("optisch");
    if (id == QLatin1String("tv_speaker"))       return QStringLiteral("TV-Lautsprecher");
    if (id == QLatin1String("bt_soundbar"))      return QStringLiteral("Bluetooth-Soundbar");
    if (id == QLatin1String("tv_external_speaker"))
        return QStringLiteral("TV-Lautsprecher + extern");
    return id.isEmpty() ? QStringLiteral("unbekannt") : id;
}

} // namespace

LgTv::LgTv(QObject *parent)
    : QObject(parent)
    , m_main(QString(), QWebSocketProtocol::VersionLatest)
    , m_pointer(QString(), QWebSocketProtocol::VersionLatest)
    , m_host(QStringLiteral(""))
    , m_status(QStringLiteral("getrennt"))
{
    connect(&m_main, &QWebSocket::connected, this, &LgTv::onMainConnected);
    connect(&m_main, &QWebSocket::disconnected, this, &LgTv::onMainDisconnected);
    connect(&m_main, &QWebSocket::textMessageReceived, this, &LgTv::onMainMessage);

    connect(&m_pointer, &QWebSocket::connected, this, &LgTv::onPointerConnected);
    connect(&m_pointer, &QWebSocket::disconnected, this, &LgTv::onPointerDisconnected);

    // Zwei Zugestaendnisse sind noetig, damit ueberhaupt eine Verbindung
    // zustande kommt:
    //
    // 1. Protokollversion fest auf TLS 1.2. Der Fernseher bevorzugt TLS 1.3
    //    und lehnt alles unter 1.2 ab; Qt 5.6 kennt 1.3 noch nicht und
    //    handelt sonst eine zu alte Version aus. Der Fernseher schliesst
    //    dann kommentarlos - in der App sichtbar als
    //    "Remote host closed the connection".
    // 2. Keine Zertifikatspruefung. Der Fernseher weist sich mit einem
    //    selbstsignierten Zertifikat aus (CN=LGE TV SSG). Im eigenen
    //    Heimnetz gegen eine feste Adresse ist das hinnehmbar.
    QSslConfiguration ssl = QSslConfiguration::defaultConfiguration();
    ssl.setProtocol(QSsl::TlsV1_2);
    ssl.setPeerVerifyMode(QSslSocket::VerifyNone);

    auto relax = [&ssl](QWebSocket *s) {
        s->setSslConfiguration(ssl);
        connect(s, static_cast<void (QWebSocket::*)(const QList<QSslError> &)>(&QWebSocket::sslErrors),
                s, static_cast<void (QWebSocket::*)()>(&QWebSocket::ignoreSslErrors));
    };
    relax(&m_main);
    relax(&m_pointer);

    connect(&m_main, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
            this, [this](QAbstractSocket::SocketError) {
                qWarning() << "LgTv: Socketfehler:" << m_main.errorString();
                setStatus(QStringLiteral("Fehler: ") + m_main.errorString());
                emit failed(m_main.errorString());
            });

    // Zertifikatsfehler zusaetzlich sichtbar machen. Ohne das sieht man nur
    // "Remote host closed the connection" und weiss nicht, ob es an TLS lag.
    connect(&m_main, static_cast<void (QWebSocket::*)(const QList<QSslError> &)>(&QWebSocket::sslErrors),
            this, [this](const QList<QSslError> &errors) {
                QStringList texts;
                for (const QSslError &e : errors)
                    texts << e.errorString();
                m_sslNote = texts.join(QStringLiteral(" | "));
                emit statusTextChanged();
            });
}

/* Alles, was bei einem fehlgeschlagenen Verbindungsversuch zaehlt – wird in
   den Einstellungen angezeigt, damit man nicht raten muss. */
QString LgTv::diagnostics() const
{
    QStringList out;
    out << QStringLiteral("SSL im Qt-Build: ")
           + (QSslSocket::supportsSsl() ? QStringLiteral("ja") : QStringLiteral("NEIN"));
    out << QStringLiteral("SSL-Bibliothek: ") + QSslSocket::sslLibraryVersionString();
    out << QStringLiteral("Ziel: wss://") + m_host + QStringLiteral(":3001");
    if (!m_sslNote.isEmpty())
        out << QStringLiteral("Zertifikat: ") + m_sslNote;
    if (!m_lastError.isEmpty())
        out << QStringLiteral("Letzte abgelehnte Abfrage: ") + m_lastError;
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
    setStatus(QStringLiteral("verbinde ..."));
    qWarning() << "LgTv: verbinde mit wss://" << m_host << ":3001";
    // Feste Wahl: wss auf 3001. Aktuelle Firmware bedient das offene
    // Port 3000 nicht mehr.
    m_main.open(QUrl(QStringLiteral("wss://%1:3001").arg(m_host)));
}

void LgTv::disconnectTv()
{
    m_pointer.close();
    m_main.close();
    m_linkUp = m_registered = m_pointerReady = false;
    m_pending.clear();
    m_subs.clear();
    m_textInputReady = false;
    emit textInputChanged();
    emit stateChanged();
    setStatus(QStringLiteral("getrennt"));
}

void LgTv::onMainConnected()
{
    qWarning() << "LgTv: Verbindung offen, melde an";
    m_linkUp = true;
    emit stateChanged();
    sendRegister();
}

void LgTv::onMainDisconnected()
{
    m_linkUp = m_registered = m_pointerReady = false;
    m_pending.clear();
    emit stateChanged();
}

void LgTv::onPointerConnected()
{
    m_pointerReady = true;
    emit stateChanged();
}

void LgTv::onPointerDisconnected()
{
    m_pointerReady = false;
    emit stateChanged();
}

// ---------- Anmeldung ----------

void LgTv::sendRegister()
{
    QJsonObject payload;
    payload.insert(QStringLiteral("forcePairing"), false);
    payload.insert(QStringLiteral("pairingType"), QStringLiteral("PROMPT"));
    payload.insert(QStringLiteral("manifest"),
                   QJsonDocument::fromJson(QByteArray(kManifest)).object());
    if (!m_clientKey.isEmpty())
        payload.insert(QStringLiteral("client-key"), m_clientKey);
    else
        emit pairingPrompt();

    setStatus(m_clientKey.isEmpty() ? QStringLiteral("warte auf Bestätigung am Fernseher")
                                    : QStringLiteral("melde an ..."));

    QJsonObject msg;
    msg.insert(QStringLiteral("id"), QStringLiteral("register_0"));
    msg.insert(QStringLiteral("type"), QStringLiteral("register"));
    msg.insert(QStringLiteral("payload"), payload);
    m_main.sendTextMessage(QString::fromUtf8(QJsonDocument(msg).toJson(QJsonDocument::Compact)));
}

// ---------- Nachrichten ----------

void LgTv::onMainMessage(const QString &text)
{
    const QJsonObject msg = QJsonDocument::fromJson(text.toUtf8()).object();
    const QString type = msg.value(QStringLiteral("type")).toString();
    const QJsonObject payload = msg.value(QStringLiteral("payload")).toObject();

    if (type == QLatin1String("registered")) {
        qWarning() << "LgTv: angemeldet";
        m_registered = true;
        emit stateChanged();
        setStatus(QStringLiteral("verbunden"));

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
        /* Muss bestehen bleiben, solange Text geschickt werden soll: ohne
           angemeldete Fernbedienungstastatur ordnet der Fernseher den Text
           keinem Feld zu und verwirft ihn - am Geraet nachgewiesen. */
        subscribe(QStringLiteral("ssap://com.webos.service.ime/registerRemoteKeyboard"),
                  WantKeyboard);
        /* Fuer das Textfeld: ist YouTube auf dem Bildschirm, wird gesucht,
           sonst der Text in das Feld am Fernseher geschrieben.
           getForegroundAppInfo waere naheliegender, der Fernseher beantwortet
           es unserem Schluessel aber mit "401 insufficient permissions".
           getAppState ist erlaubt und meldet running und visible. */
        subscribe(QStringLiteral("ssap://system.launcher/getAppState"), WantAppState,
                  ytPayload());
        refreshVolume();
        refreshChannel();
        return;
    }

    if (type == QLatin1String("error")) {
        const QString err = msg.value(QStringLiteral("error")).toString();

        /* Sobald die Anmeldung steht, betrifft ein Fehler nur die eine
           Abfrage - etwa "401 insufficient permissions" fuer die Firmware.
           Der frueher hier stehende Rundumschlag hat in dem Fall den
           Kopplungsschluessel geloescht und die Verbindung gekappt. */
        if (m_registered) {
            m_lastError = err;
            emit statusTextChanged();
            return;
        }

        setStatus(QStringLiteral("Fehler: ") + err);
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
        handlePayload(m_subs.value(id), payload);   // bleibt bestehen
    else if (m_pending.contains(id))
        handlePayload(m_pending.take(id), payload);
}

/* Abonnement: der Fernseher meldet Aenderungen von sich aus. */
void LgTv::subscribe(const QString &uri, Want want, const QJsonObject &payload)
{
    const QString id = QStringLiteral("sub_%1").arg(++m_counter);
    m_subs.insert(id, want);
    QJsonObject msg;
    msg.insert(QStringLiteral("id"), id);
    msg.insert(QStringLiteral("type"), QStringLiteral("subscribe"));
    msg.insert(QStringLiteral("uri"), uri);
    msg.insert(QStringLiteral("payload"), payload);
    m_main.sendTextMessage(QString::fromUtf8(QJsonDocument(msg).toJson(QJsonDocument::Compact)));
}

QString LgTv::request(const QString &uri, const QJsonObject &payload, Want want)
{
    if (!m_registered && want != WantPointer)
        return QString();

    const QString id = QStringLiteral("req_%1").arg(++m_counter);
    if (want != WantNothing)
        m_pending.insert(id, want);

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
    case WantPointer: {
        const QString path = payload.value(QStringLiteral("socketPath")).toString();
        if (!path.isEmpty())
            m_pointer.open(QUrl(path));
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

        /* Laeuft der Ton ueber die TV-Lautsprecher, regelt der Fernseher
           seinen eigenen Verstaerker - dann ist der Wert echt. Haengt er per
           ARC an einem fremden Geraet, ist es nur ein Zaehler: das Geraet
           meldet seinen Pegel nie zurueck, am CEC-Bus nachgemessen. */
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
            out.append(m);
        }
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
            out.append(m);
        }
        emit inputsReceived(out);
        break;
    }
    case WantTextResult: {
        /* Antwort auf insertText festhalten - ohne das sendet die App blind
           und wir sehen nicht, ob der Fernseher den Text angenommen hat. */
        const bool ok = payload.value(QStringLiteral("returnValue")).toBool();
        m_lastError = ok ? QStringLiteral("insertText: angenommen")
                         : QStringLiteral("insertText abgelehnt: ")
                           + payload.value(QStringLiteral("errorText")).toString();
        emit statusTextChanged();
        break;
    }
    case WantKeyboard: {
        /* currentWidget beschreibt das Feld, das gerade Eingaben annimmt.
           focus=false heisst: kein Feld offen, Text waere verloren. */
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

        /* Wartet eine Suche, entscheidet sich hier der Weg: Steht die App
           schon auf dem Bildschirm, nimmt sie den Begriff im Lauf entgegen.
           Liegt sie im Hintergrund, wuerde ein Start sie nur benachrichtigen,
           ohne sie nach vorn zu holen - dann erst schliessen. */
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
        m.insert(QStringLiteral("Modell"), payload.value(QStringLiteral("modelName")).toString());
        m.insert(QStringLiteral("Seriennummer"), payload.value(QStringLiteral("serialNumber")).toString());
        m.insert(QStringLiteral("Empfangsteil"), payload.value(QStringLiteral("receiverType")).toString());
        emit systemInfoReceived(m);
        break;
    }
    case WantNetwork: {
        QVariantMap m;
        const QStringList keys = { QStringLiteral("wiredInfo"), QStringLiteral("wifiInfo"),
                                   QStringLiteral("p2pInfo") };
        const QStringList names = { QStringLiteral("MAC Kabel"), QStringLiteral("MAC WLAN"),
                                    QStringLiteral("MAC Direktverbindung") };
        for (int i = 0; i < keys.size(); ++i) {
            const QJsonObject o = payload.value(keys.at(i)).toObject();
            const QString mac = o.value(QStringLiteral("macAddress")).toString();
            if (!mac.isEmpty())
                m.insert(names.at(i), mac.toLower());
            const QString ip = o.value(QStringLiteral("ipAddress")).toString();
            if (!ip.isEmpty())
                m.insert(names.at(i) + QStringLiteral(" – IP"), ip);
        }
        emit networkInfoReceived(m);
        break;
    }
    case WantAudio: {
        const QJsonObject v = payload.value(QStringLiteral("volumeStatus")).toObject();
        QVariantMap m;
        const QString out = v.value(QStringLiteral("soundOutput")).toString();
        m.insert(QStringLiteral("Tonausgabe"), prettySoundOutput(out));
        m.insert(QStringLiteral("Lautstärke"),
                 QStringLiteral("%1 von %2").arg(v.value(QStringLiteral("volume")).toInt())
                     .arg(v.value(QStringLiteral("maxVolume")).toInt()));
        m.insert(QStringLiteral("Stumm"),
                 v.value(QStringLiteral("muteStatus")).toBool() ? QStringLiteral("ja")
                                                                : QStringLiteral("nein"));
        m.insert(QStringLiteral("Externe Steuerung"),
                 v.value(QStringLiteral("externalDeviceControl")).toBool() ? QStringLiteral("ja")
                                                                          : QStringLiteral("nein"));
        m.insert(QStringLiteral("Lautstärke regelbar"),
                 v.value(QStringLiteral("adjustVolume")).toBool() ? QStringLiteral("ja")
                                                                  : QStringLiteral("nein"));
        emit audioStatusReceived(m);
        break;
    }
    case WantSoftware: {
        QVariantMap m;
        m.insert(QStringLiteral("Firmware"),
                 payload.value(QStringLiteral("major_ver")).toString()
                 + QStringLiteral(".") + payload.value(QStringLiteral("minor_ver")).toString());
        m.insert(QStringLiteral("Produkt"), payload.value(QStringLiteral("product_name")).toString());
        m.insert(QStringLiteral("webOS"), payload.value(QStringLiteral("webos_release")).toString());
        emit softwareInfoReceived(m);
        break;
    }
    default:
        break;
    }
}

// ---------- Tastenkanal ----------

void LgTv::button(const QString &name)
{
    if (!m_pointerReady)
        return;
    m_pointer.sendTextMessage(QStringLiteral("type:button\nname:%1\n\n").arg(name));
}

void LgTv::move(int dx, int dy)
{
    if (!m_pointerReady)
        return;
    m_pointer.sendTextMessage(
        QStringLiteral("type:move\ndx:%1\ndy:%2\ndown:0\n\n").arg(dx).arg(dy));
}

void LgTv::click()
{
    if (!m_pointerReady)
        return;
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

/*
 * Lautstaerke im Takt abgeben.
 *
 * Am Geraet beobachtet: Bei schnellem Tippen oder gehaltener Taste laeuft die
 * Anzeige der Anlage der des Fernsehers hinterher - der Fernseher zaehlt jeden
 * Befehl mit und gibt ihn per CEC weiter, die Anlage schafft aber nicht jeden.
 * Deshalb werden die Schritte gesammelt und im Takt abgegeben.
 */
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

/*
 * Am Geraet gemessen: setVolume verstellt ausschliesslich den Zaehler des
 * Fernsehers. Waehrend des Aufrufs geht ueber CEC kein einziger
 * Lautstaerkebefehl hinaus - das Tongeraet bleibt, wo es ist. Genau deshalb
 * taugt der Aufruf zum Abgleich der Anzeige.
 */
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

/* Der Fernseher braucht einen Moment, bis der neue Kanal anliegt - sofortiges
   Nachfragen liefert sonst noch den alten. */
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
}

void LgTv::launchApp(const QString &id)
{
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
    note(QStringLiteral("YouTube: %1").arg(begriff));
    refreshYouTubeState();
}

void LgTv::refreshYouTubeState()
{
    request(QStringLiteral("ssap://system.launcher/getAppState"), ytPayload(), WantAppState);
}

void LgTv::switchInput(const QString &id)
{
    QJsonObject p;
    p.insert(QStringLiteral("inputId"), id);
    request(QStringLiteral("ssap://tv/switchInput"), p, WantNothing);
}

/*
 * Der Aufruf steckt nicht in system.launcher, sondern in einem eigenen
 * Dienst. Alle naheliegenden Wege fuehren daran vorbei: com.webos.app.
 * homeconnect oeffnet den Startseiten-Hub als ganze Seite, und ueber den
 * Tastenkanal gibt es keinen Namen dafuer - 44 geprueft, keiner wirkt.
 */
void LgTv::showInputPicker()
{
    request(QStringLiteral("ssap://com.webos.surfacemanager/showInputPicker"),
            QJsonObject(), WantNothing);
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

void LgTv::requestAudioStatus()
{
    request(QStringLiteral("ssap://audio/getStatus"), QJsonObject(), WantAudio);
}

void LgTv::requestSoftwareInfo()
{
    // Wird je nach erteilten Berechtigungen mit 401 abgelehnt; die Seite
    // zeigt dann schlicht keinen Firmware-Eintrag.
    request(QStringLiteral("ssap://com.webos.service.update/getCurrentSWInformation"),
            QJsonObject(), WantSoftware);
}
