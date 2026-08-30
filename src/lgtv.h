#ifndef LGTV_H
#define LGTV_H

#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <QSslCertificate>
#include <QSslError>
#include <QString>
#include <QStringList>
#include <QVariantList>
#include <QVariantMap>
#include <QTimer>
#include <QWebSocket>

class QUrl;

/*
 * Anbindung an einen LG-Fernseher mit webOS (SSAP).
 *
 * C++ statt QML, weil der Fernseher wss auf 3001 mit selbstsigniertem
 * Zertifikat verlangt - die QML-Komponente WebSocket kann das nicht annehmen.
 * Zwei Verbindungen: Hauptkanal fuer Befehle, zweiter Socket fuer Tasten und
 * Zeiger, dessen Adresse der Fernseher erst auf Anfrage nennt.
 */
class LgTv : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(QString clientKey READ clientKey WRITE setClientKey NOTIFY clientKeyChanged)
    /* SHA-256 des Zertifikats, beim ersten Verbinden gemerkt. Ohne diese
       Pruefung koennte sich jeder als der Fernseher ausgeben. */
    Q_PROPERTY(QString certFingerprint READ certFingerprint WRITE setCertFingerprint NOTIFY certFingerprintChanged)
    Q_PROPERTY(bool linkUp READ linkUp NOTIFY stateChanged)
    Q_PROPERTY(bool registered READ registered NOTIFY stateChanged)
    Q_PROPERTY(bool pointerReady READ pointerReady NOTIFY stateChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    /* Diagnose: was die SSL-Schicht und der Qt-Build hergeben */
    Q_PROPERTY(QString diagnostics READ diagnostics NOTIFY statusTextChanged)
    // Vom verbundenen Fernseher gemeldet, fuer die Geraeteliste
    Q_PROPERTY(QString model READ model NOTIFY deviceInfoChanged)
    Q_PROPERTY(QString serial READ serial NOTIFY deviceInfoChanged)
    // Ausgehandelte Verschluesselung, siehe requestTlsInfo
    Q_PROPERTY(QString tlsVersion READ tlsVersion NOTIFY tlsInfoChanged)
    Q_PROPERTY(int volume READ volume NOTIFY volumeChanged)
    Q_PROPERTY(bool muted READ muted NOTIFY volumeChanged)
    // Falsch bei Ton ueber ARC: der TV zaehlt dann nur (volumeSyncable=false)
    Q_PROPERTY(bool volumeReliable READ volumeReliable NOTIFY volumeChanged)
    /* "tv_speaker", "external_arc", "external_optical", ... */
    Q_PROPERTY(QString soundOutput READ soundOutput NOTIFY volumeChanged)
    // Ohne offenes Feld verwirft der TV Text stumm - mit OK quittiert
    Q_PROPERTY(bool textInputReady READ textInputReady NOTIFY textInputChanged)
    Q_PROPERTY(QString textInputType READ textInputType NOTIFY textInputChanged)
    // Nur die Laenge gibt der TV heraus, nicht den Inhalt
    Q_PROPERTY(int textInputLength READ textInputLength NOTIFY textInputChanged)
    Q_PROPERTY(QString channel READ channel NOTIFY channelChanged)
    // Steht YouTube auf dem Bildschirm? Danach richtet sich das Textfeld
    Q_PROPERTY(bool youtubeAhead READ youtubeAhead NOTIFY foregroundAppChanged)
    /* Der Fernseher meldet seinen Einschaltzustand selbst. Ohne diese Auskunft
       hiesse "Verbindung steht" faelschlich "Fernseher an": im Netzwerk-
       Standby nimmt er Verbindungen an, ist aber aus. */
    Q_PROPERTY(QString powerState READ powerState NOTIFY powerStateChanged)
    Q_PROPERTY(bool awake READ awake NOTIFY powerStateChanged)
    // Wahr, solange der Fernseher den Zustand nicht genannt hat
    Q_PROPERTY(bool powerUnknown READ powerUnknown NOTIFY powerStateChanged)

public:
    explicit LgTv(QObject *parent = nullptr);

    QString host() const { return m_host; }
    void setHost(const QString &h);
    QString clientKey() const { return m_clientKey; }
    void setClientKey(const QString &k);
    QString certFingerprint() const { return m_certFingerprint; }
    void setCertFingerprint(const QString &f);

    bool linkUp() const { return m_linkUp; }
    bool registered() const { return m_registered; }
    bool pointerReady() const { return m_pointerReady; }
    QString statusText() const { return m_status; }
    QString diagnostics() const;
    QString tlsVersion() const { return m_tls; }
    QString model() const { return m_model; }
    QString serial() const { return m_serial; }
    // QtWebSockets 5.5 gibt die ausgehandelte Sitzung nicht heraus
    Q_INVOKABLE void requestTlsInfo();
    int volume() const { return m_volume; }
    bool muted() const { return m_muted; }
    bool volumeReliable() const { return m_volumeReliable; }
    QString soundOutput() const { return m_soundOutput; }
    bool textInputReady() const { return m_textInputReady; }
    QString textInputType() const { return m_textInputType; }
    int textInputLength() const { return m_textInputLength; }
    // Loescht so viele Zeichen, wie im Feld stehen
    Q_INVOKABLE void clearRemoteField();
    /* Umschalten zwischen TV-Lautsprecher und externem Geraet */
    Q_INVOKABLE void changeSoundOutput(const QString &out);
    QString channel() const { return m_channel; }
    bool youtubeAhead() const { return m_ytVisible; }
    QString powerState() const { return m_power; }
    bool powerUnknown() const { return m_power.isEmpty(); }
    /* "Screen Off" heisst an, nur der Bildschirm ist dunkel - etwa bei
       Musikwiedergabe. "Active Standby" und "Suspend" heissen aus. */
    bool awake() const;
    Q_INVOKABLE void requestPowerState();
    /* Das Abo meldet zuverlaessig nur das Verschwinden - deshalb bei Bedarf
       nachfragen. */
    Q_INVOKABLE void refreshYouTubeState();

    Q_INVOKABLE void connectTv();
    /* Meldung aus QML setzen - statusText selbst ist nur lesbar */
    Q_INVOKABLE void note(const QString &text) { setStatus(text); }
    Q_INVOKABLE void disconnectTv();
    // Verbinden oder nachpruefen; beim Zurueckholen der App gerufen
    Q_INVOKABLE void ensureConnected();

    /* Tasten: UP, DOWN, LEFT, RIGHT, ENTER, BACK, EXIT, HOME, MENU, INFO,
       0-9, DASH, RED, GREEN, YELLOW, BLUE */
    Q_INVOKABLE void button(const QString &name);

    /* Zeigersteuerung ueber denselben Kanal wie die Tasten */
    Q_INVOKABLE void move(int dx, int dy);
    Q_INVOKABLE void click();
    Q_INVOKABLE void scroll(int dx, int dy);

    /* Texteingabe in Suchfelder des Fernsehers */
    Q_INVOKABLE void insertText(const QString &text);
    Q_INVOKABLE void deleteCharacters(int count);
    Q_INVOKABLE void sendEnter();

    Q_INVOKABLE void volumeUp();
    Q_INVOKABLE void volumeDown();
    Q_INVOKABLE void setMute(bool on);
    Q_INVOKABLE void refreshVolume();
    // Setzt nur den Zaehler des TV; ARC erfaehrt davon nichts
    Q_INVOKABLE void setVolume(int v);
    Q_INVOKABLE void refreshChannel();
    /* Zum Ausprobieren unbekannter Tastennamen, siehe Einstellungen */
    Q_INVOKABLE void sendRaw(const QString &name) { button(name); }

    Q_INVOKABLE void channelUp();
    Q_INVOKABLE void channelDown();
    Q_INVOKABLE void openChannel(const QString &number);

    Q_INVOKABLE void turnOff();
    Q_INVOKABLE void launchApp(const QString &id);
    Q_INVOKABLE void switchInput(const QString &id);

    /* Suchbegriff als Startparameter, ohne Bildschirmtastatur. Er heisst
       "target", nicht "contentTarget" - nur so greift er bei laufender App. */
    Q_INVOKABLE void searchYouTube(const QString &text);

    // Blendet die Eingangsleiste ein wie die Eingangstaste am Original
    Q_INVOKABLE void showInputPicker();

    // Bildschirmfoto: der TV legt es ab und nennt die Adresse
    Q_INVOKABLE void captureScreen();

    Q_INVOKABLE void requestApps();
    Q_INVOKABLE void requestInputs();

    /* Systemdaten fuer die Uebersichtsseite */
    Q_INVOKABLE void requestSystemInfo();
    Q_INVOKABLE void requestNetworkInfo();
    // Wie oben, aber mit Nachfassen, wenn keine MAC dabei ist
    void chaseNetworkInfo();
    Q_INVOKABLE void requestAudioStatus();

signals:
    void hostChanged();
    void clientKeyChanged();
    void certFingerprintChanged();
    void stateChanged();
    void statusTextChanged();
    void volumeChanged();
    void textInputChanged();
    void channelChanged();
    void foregroundAppChanged();
    void powerStateChanged();

    void pairingPrompt();                       // TV fragt nach Bestaetigung
    void appsReceived(const QVariantList &apps);
    void inputsReceived(const QVariantList &inputs);
    void systemInfoReceived(const QVariantMap &info);
    void tunerReceived(const QString &type);
    void deviceInfoChanged();
    void networkInfoReceived(const QVariantMap &info);
    /* Alle anfunkbaren MACs des Fernsehers, die erkannte zuerst. Mehrzahl
       mit Absicht: manche Firmware nennt zu ihren Schnittstellen weder
       Adresse noch Zustand, dann ist keine Wahl zu treffen. */
    void macsDiscovered(const QStringList &macs);
    void audioStatusReceived(const QVariantMap &info);
    void tlsInfoChanged();
    void captureReady(const QString &url);
    void failed(const QString &message);

private slots:
    void onMainConnected();
    void onMainDisconnected();
    void onMainMessage(const QString &text);
    void onPointerConnected();
    void onPointerDisconnected();
    void onAppStateChanged(Qt::ApplicationState state);

private:
    // WantHeartbeat: dass die Antwort ankommt, ist die ganze Information
    enum Want { WantNothing, WantVolume, WantPointer, WantApps, WantInputs,
                WantSystem, WantNetwork, WantAudio, WantChannel,
                WantKeyboard, WantTextResult, WantAppState, WantHeartbeat, WantCapture,
                WantPower };

    /* Zu jeder offenen Anfrage die Adresse mitfuehren: kommt statt der
       Antwort ein Fehler, soll im Protokoll stehen, was misslungen ist -
       nicht nur, dass etwas misslang. */
    struct Pending {
        Want want;              // ohne Vorgabe: so bleibt es ein Aggregat
        QString uri;
    };
    static QString wantName(Want want);

    bool acceptCert(const QSslCertificate &vorgelegt, const QList<QSslError> &errors);
    /* Der Fernseher nennt uns Adressen: den Tastenkanal, das Bildschirmfoto,
       die App-Symbole. Keine davon wird ungeprueft benutzt - sie muss zu ihm
       selbst zurueckfuehren. Verglichen wird gegen die eingetragene Adresse
       und gegen die tatsaechliche Gegenstelle, damit auch ein Geraetename
       statt einer IP im Eintrag traegt. */
    bool vomFernseher(const QUrl &u) const;
    /* Symboladresse aus der App-Liste: durchgereicht wird sie nur,
       wenn sie auf den Fernseher zeigt - sonst leer, dann steht die
       Beschriftung an ihrer Stelle. */
    QString pruefeSymbol(const QString &url) const;
    void flushMove();
    QJsonObject ytPayload();
    void launchYouTube(const QString &begriff);
    void setStatus(const QString &s);
    void openMain();
    void startBeat();
    void stopBeat();
    void probe();
    void handleDrop();
    void scheduleRetry();
    void sendRegister();
    void askPointer();
    void probeTls();
    void relaunchYouTube();
    void stepVolume(int delta);
    QString request(const QString &uri, const QJsonObject &payload, Want want);
    void subscribe(const QString &uri, Want want,
                   const QJsonObject &payload = QJsonObject());
    void handlePayload(Want want, const QJsonObject &payload);

    QWebSocket m_main;
    QWebSocket m_pointer;

    QString m_host;
    // Gegenstelle des offenen Hauptkanals, als Adresse
    QString m_peer;
    QString m_clientKey;
    QString m_certFingerprint;
    /* Gesetzt, wenn das Zertifikat nicht zum gemerkten passt: dann keine
       Wiederholungsversuche, bis der Nutzer die Kopplung zuruecksetzt. */
    bool m_certBlocked = false;
    QString m_status;
    bool m_linkUp = false;
    bool m_registered = false;
    bool m_pointerReady = false;
    int m_volume = -1;
    bool m_muted = false;
    bool m_volumeReliable = true;
    QString m_soundOutput;
    bool m_textInputReady = false;
    QString m_textInputType;
    int m_textInputLength = 0;
    QString m_channel;
    bool m_ytVisible = false;
    QString m_power;
    bool m_ytRunning = false;
    /* Null: nichts offen. Leer: App nur nach vorn holen. Sonst Suchbegriff. */
    QString m_pendingSearch;

    /* Lautstaerke im Takt: der TV reicht jeden Schritt per CEC weiter, und
       CEC ist langsamer als diese Verbindung. */
    int m_volSteps = 0;
    QTimer *m_volTimer = nullptr;

    // Zeigerbewegungen buendeln, sonst dutzende TLS-Rahmen je Sekunde
    int m_moveX = 0;
    int m_moveY = 0;
    QTimer *m_moveTimer = nullptr;

    /* Die Verbindung stirbt oft, ohne dass der Socket es merkt (Telefon
       schlaeft, TV aus): Lebenszeichen (m_beat), Wachhund auf die Antwort
       (m_watch), Wiederverbinden mit wachsendem Abstand (m_retry). */
    /* Der Fernseher nimmt die TCP-Verbindung zeitweise an, beantwortet den
       TLS-Hello aber nicht; erst nach ~15 s faellt sie. So lange soll die
       Oberflaeche nicht warten. */
    QTimer *m_connect = nullptr;
    QTimer *m_beat = nullptr;
    QTimer *m_watch = nullptr;
    QTimer *m_retry = nullptr;
    int m_retryDelay = 2000;
    bool m_alive = true;
    /* Wahr nur nach bewusstem Trennen - dann bleibt es getrennt. */
    bool m_userClosed = false;
    int m_pointerTries = 0;
    QString m_tls;
    int m_tlsTries = 0;
    QString m_model;
    QString m_serial;
    /* Die MAC kommt nur vom verbundenen Fernseher, und nur diese eine
       Abfrage nennt sie. Bleibt sie aus, wird nachgefasst. */
    int m_netTries = 0;

    int m_counter = 0;
    QHash<QString, Pending> m_pending;
    /* Abos bleiben stehen: der TV schickt jede Aenderung unter derselben
       Kennung, auch bei Bedienung ueber die Originalfernbedienung. */
    QHash<QString, Pending> m_subs;
    QString m_sslNote;
    QString m_lastError;
};

#endif // LGTV_H
