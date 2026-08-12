#ifndef LGTV_H
#define LGTV_H

#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QTimer>
#include <QWebSocket>

/*
 * Anbindung an einen LG-Fernseher mit webOS (SSAP).
 *
 * Warum C++ und nicht QML: Der Fernseher verlangt wss auf Port 3001 – das
 * unverschluesselte Port 3000 lehnt aktuelle Firmware ab – und benutzt dabei
 * ein selbstsigniertes Zertifikat. Die QML-Komponente WebSocket bietet keine
 * Moeglichkeit, das zu akzeptieren; QWebSocket::ignoreSslErrors() schon.
 *
 * Es sind zwei Verbindungen noetig: der Hauptkanal fuer Befehle und ein
 * zweiter Socket fuer die Tasten des Steuerkreuzes, dessen Adresse der
 * Fernseher erst auf Anfrage herausgibt.
 */
class LgTv : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString host READ host WRITE setHost NOTIFY hostChanged)
    Q_PROPERTY(QString clientKey READ clientKey WRITE setClientKey NOTIFY clientKeyChanged)
    Q_PROPERTY(bool linkUp READ linkUp NOTIFY stateChanged)
    Q_PROPERTY(bool registered READ registered NOTIFY stateChanged)
    Q_PROPERTY(bool pointerReady READ pointerReady NOTIFY stateChanged)
    Q_PROPERTY(QString statusText READ statusText NOTIFY statusTextChanged)
    /* Diagnose: was die SSL-Schicht und der Qt-Build hergeben */
    Q_PROPERTY(QString diagnostics READ diagnostics NOTIFY statusTextChanged)
    Q_PROPERTY(int volume READ volume NOTIFY volumeChanged)
    Q_PROPERTY(bool muted READ muted NOTIFY volumeChanged)
    /* Falsch, sobald der Ton ueber ARC an einem externen Geraet haengt:
       der Fernseher fuehrt dann einen eigenen Zaehler, der mit dem echten
       Pegel nichts zu tun hat (volumeSyncable = false). */
    Q_PROPERTY(bool volumeReliable READ volumeReliable NOTIFY volumeChanged)
    /* "tv_speaker", "external_arc", "external_optical", ... */
    Q_PROPERTY(QString soundOutput READ soundOutput NOTIFY volumeChanged)
    /* Der Fernseher meldet, ob gerade ein Textfeld auf Eingabe wartet. Ohne
       ein solches Feld verwirft er eingehenden Text stumm - mit OK quittiert,
       aber ohne Wirkung. */
    Q_PROPERTY(bool textInputReady READ textInputReady NOTIFY textInputChanged)
    Q_PROPERTY(QString textInputType READ textInputType NOTIFY textInputChanged)
    /* Wie viele Zeichen bereits im Feld stehen. Den Inhalt selbst gibt der
       Fernseher nicht heraus, nur die Laenge. */
    Q_PROPERTY(int textInputLength READ textInputLength NOTIFY textInputChanged)
    Q_PROPERTY(QString channel READ channel NOTIFY channelChanged)
    /* Steht YouTube gerade auf dem Bildschirm? Das Textfeld zeigt danach
       entweder die Lupe (suchen) oder den Haken (Text ins Feld). */
    Q_PROPERTY(bool youtubeAhead READ youtubeAhead NOTIFY foregroundAppChanged)

public:
    explicit LgTv(QObject *parent = nullptr);

    QString host() const { return m_host; }
    void setHost(const QString &h);
    QString clientKey() const { return m_clientKey; }
    void setClientKey(const QString &k);

    bool linkUp() const { return m_linkUp; }
    bool registered() const { return m_registered; }
    bool pointerReady() const { return m_pointerReady; }
    QString statusText() const { return m_status; }
    QString diagnostics() const;
    int volume() const { return m_volume; }
    bool muted() const { return m_muted; }
    bool volumeReliable() const { return m_volumeReliable; }
    QString soundOutput() const { return m_soundOutput; }
    bool textInputReady() const { return m_textInputReady; }
    QString textInputType() const { return m_textInputType; }
    int textInputLength() const { return m_textInputLength; }
    /* Leert das Feld am Fernseher, indem es so viele Zeichen loescht wie
       darin stehen. */
    Q_INVOKABLE void clearRemoteField();
    /* Umschalten zwischen TV-Lautsprecher und externem Geraet */
    Q_INVOKABLE void changeSoundOutput(const QString &out);
    QString channel() const { return m_channel; }
    bool youtubeAhead() const { return m_ytVisible; }
    /* Fragt nach, ob YouTube gerade auf dem Bildschirm steht. Das Abo meldet
       zuverlaessig, wenn die App verschwindet - der umgekehrte Weg kam im Test
       nicht immer an, deshalb fragt die Oberflaeche bei Bedarf nach. */
    Q_INVOKABLE void refreshYouTubeState();

    Q_INVOKABLE void connectTv();
    /* Meldung aus QML setzen - statusText selbst ist nur lesbar */
    Q_INVOKABLE void note(const QString &text) { setStatus(text); }
    Q_INVOKABLE void disconnectTv();
    /* Stellt die Verbindung her, falls sie fehlt - und prueft sie nach, falls
       der Socket nur offen aussieht. Wird beim Zurueckholen der App gerufen. */
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
    /* Setzt den Zaehler des Fernsehers auf einen festen Wert. Das Tongeraet
       an ARC erfaehrt davon nichts - dient allein dem Abgleich der Anzeige. */
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

    /* Sucht bei YouTube, ohne den Umweg ueber die Bildschirmtastatur: Die App
       nimmt den Suchbegriff als Startparameter entgegen und haengt ihn an ihre
       Adresse an. Der Parameter heisst "target" und nicht "contentTarget" -
       nur damit greift auch ein Start, waehrend die App schon laeuft. */
    Q_INVOKABLE void searchYouTube(const QString &text);

    /* Blendet die Eingangsleiste am unteren Bildschirmrand ein - dieselbe,
       die die Eingangstaste der Fernbedienung oeffnet. */
    Q_INVOKABLE void showInputPicker();

    Q_INVOKABLE void requestApps();
    Q_INVOKABLE void requestInputs();

    /* Systemdaten fuer die Uebersichtsseite */
    Q_INVOKABLE void requestSystemInfo();
    Q_INVOKABLE void requestNetworkInfo();
    Q_INVOKABLE void requestAudioStatus();
    Q_INVOKABLE void requestSoftwareInfo();

signals:
    void hostChanged();
    void clientKeyChanged();
    void stateChanged();
    void statusTextChanged();
    void volumeChanged();
    void textInputChanged();
    void channelChanged();
    void foregroundAppChanged();

    void pairingPrompt();                       // TV fragt nach Bestaetigung
    void appsReceived(const QVariantList &apps);
    void inputsReceived(const QVariantList &inputs);
    void systemInfoReceived(const QVariantMap &info);
    void networkInfoReceived(const QVariantMap &info);
    void audioStatusReceived(const QVariantMap &info);
    void softwareInfoReceived(const QVariantMap &info);
    void failed(const QString &message);

private slots:
    void onMainConnected();
    void onMainDisconnected();
    void onMainMessage(const QString &text);
    void onPointerConnected();
    void onPointerDisconnected();
    void onAppStateChanged(Qt::ApplicationState state);

private:
    /* WantHeartbeat ist die Antwort auf das Lebenszeichen: sie wird bewusst
       nicht ausgewertet - dass sie ankommt, ist die ganze Information. */
    enum Want { WantNothing, WantVolume, WantPointer, WantApps, WantInputs,
                WantSystem, WantNetwork, WantAudio, WantSoftware, WantChannel,
                WantKeyboard, WantTextResult, WantAppState, WantHeartbeat };

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
    void stepVolume(int delta);
    QString request(const QString &uri, const QJsonObject &payload, Want want);
    void subscribe(const QString &uri, Want want,
                   const QJsonObject &payload = QJsonObject());
    void handlePayload(Want want, const QJsonObject &payload);

    QWebSocket m_main;
    QWebSocket m_pointer;

    QString m_host;
    QString m_clientKey;
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
    bool m_ytRunning = false;
    /* Null, solange keine Suche wartet - leer waere ein gueltiger Begriff. */
    QString m_pendingSearch;

    /* Lautstaerkebefehle werden gesammelt und im Takt abgegeben. Der
       Fernseher reicht jeden Befehl per CEC an das Tongeraet weiter, und CEC
       ist langsamer als unsere Verbindung - ohne Drossel verschluckt das
       Geraet Schritte, waehrend der Zaehler im Fernseher weiterlaeuft. */
    int m_volSteps = 0;
    QTimer *m_volTimer = nullptr;

    /* Die Verbindung stirbt regelmaessig, ohne dass es der Socket merkt: das
       Telefon schlaeft, das WLAN spart Strom, der Fernseher geht aus. Ohne
       Gegenmassnahme bleibt linkUp auf wahr, die Tasten laufen ins Leere und
       es hilft nur Trennen und neu Verbinden von Hand.
       Deshalb regelmaessig nach einem Lebenszeichen fragen (m_beat), auf die
       Antwort einen Wachhund setzen (m_watch) und nach einem Abbruch von
       selbst wieder anklopfen (m_retry, mit wachsendem Abstand). */
    QTimer *m_beat = nullptr;
    QTimer *m_watch = nullptr;
    QTimer *m_retry = nullptr;
    int m_retryDelay = 2000;
    bool m_alive = true;
    /* Wahr nur nach bewusstem Trennen - dann bleibt es getrennt. */
    bool m_userClosed = false;

    int m_counter = 0;
    QHash<QString, Want> m_pending;
    /* Abonnements bleiben bestehen: der Fernseher schickt bei jeder Aenderung
       erneut unter derselben Kennung - auch wenn jemand die Original-
       fernbedienung benutzt. Deshalb duerfen sie nicht wie einmalige
       Anfragen aus der Liste entfernt werden. */
    QHash<QString, Want> m_subs;
    QString m_sslNote;
    QString m_lastError;
};

#endif // LGTV_H
