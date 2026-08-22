<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="de_DE" sourcelanguage="en">
<context>
    <name>AboutPage</name>
    <message>
        <source>About</source>
        <translation>Über</translation>
    </message>
    <message>
        <source>LG remote</source>
        <translation>LG-Fernbedienung</translation>
    </message>
    <message>
        <source>Version %1</source>
        <translation>Version %1</translation>
    </message>
    <message>
        <source>Controls LG televisions running webOS over the network - no infrared, no line of sight. It speaks LG&apos;s own SSAP protocol, the same one the official remote app uses.</source>
        <translation>Steuert LG-Fernseher mit webOS über das Netzwerk – ohne Infrarot, ohne Sichtverbindung. Verwendet wird LGs eigenes SSAP-Protokoll, dasselbe, das auch die offizielle Fernbedienungs-App spricht.</translation>
    </message>
    <message>
        <source>Technical notes</source>
        <translation>Technische Hinweise</translation>
    </message>
    <message>
        <source>Origin</source>
        <translation>Herkunft</translation>
    </message>
    <message>
        <source>Written from scratch. The idea for the touchpad and text entry comes from harbour-lgremote-webos by CODeRUS and Mazhoon (WTFPL); its code could not be reused because it relies on port 3000 and the QML WebSocket component.</source>
        <translation>Eigenentwicklung. Die Idee zu Touchpad und Texteingabe stammt aus harbour-lgremote-webos von CODeRUS und Mazhoon (WTFPL); dessen Code selbst ließ sich nicht verwenden, weil er auf Port 3000 und die QML-WebSocket-Komponente setzt.</translation>
    </message>
    <message>
        <source>The connection uses &lt;b&gt;wss on port 3001&lt;/b&gt;. The unencrypted port 3000 that older remote apps use is refused by current firmware.

The TV identifies itself with a self-signed certificate; its fingerprint is remembered on the first connection and checked from then on. The TLS version is left to the library; the TV takes 1.2 as well as 1.3, but now and then it drops a handshake without answering - the app simply tries again.

The keys run over a second channel whose address the TV only hands out on request. Powering on works via Wake-on-LAN and needs the MAC address.</source>
        <translation>Die Verbindung läuft über &lt;b&gt;wss auf Port 3001&lt;/b&gt;. Das unverschlüsselte Port 3000, das ältere Fernbedienungs-Apps verwenden, wird von aktueller Firmware abgewiesen.

Der Fernseher weist sich mit einem selbstsignierten Zertifikat aus; dessen Fingerabdruck wird beim ersten Verbinden gemerkt und danach geprüft. Die TLS-Version bleibt der Bibliothek überlassen; der Fernseher nimmt 1.2 wie 1.3, verwirft aber hin und wieder einen Handshake ohne Antwort – die App versucht es dann erneut.

Die Tasten laufen über einen zweiten Kanal, dessen Adresse der Fernseher erst auf Anfrage herausgibt. Einschalten geschieht per Wake-on-LAN, dafür wird die MAC-Adresse benötigt.</translation>
    </message>
</context>
<context>
    <name>AppsPage</name>
    <message>
        <source>Inputs</source>
        <translation>Eingänge</translation>
    </message>
    <message>
        <source>Apps</source>
        <translation>Apps</translation>
    </message>
    <message>
        <source>Assign tile</source>
        <translation>Kachel belegen</translation>
    </message>
    <message>
        <source>Apps and inputs</source>
        <translation>Apps und Eingänge</translation>
    </message>
    <message>
        <source>Clear tile</source>
        <translation>Kachel leeren</translation>
    </message>
    <message>
        <source>Reload</source>
        <translation>Neu einlesen</translation>
    </message>
    <message>
        <source>Nothing found</source>
        <translation>Nichts gefunden</translation>
    </message>
    <message>
        <source>Is the television connected?</source>
        <translation>Ist der Fernseher verbunden?</translation>
    </message>
    <message>
        <source>Restore the default tiles</source>
        <translation>Kacheln zurücksetzen</translation>
    </message>
</context>
<context>
    <name>CoverPage</name>
    <message>
        <source>muted</source>
        <translation>stumm</translation>
    </message>
    <message>
        <source>connected</source>
        <translation>verbunden</translation>
    </message>
    <message>
        <source>disconnected</source>
        <translation>getrennt</translation>
    </message>
</context>
<context>
    <name>DeviceEditPage</name>
    <message>
        <source>Edit device</source>
        <translation>Gerät bearbeiten</translation>
    </message>
    <message>
        <source>New device</source>
        <translation>Neues Gerät</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Name</translation>
    </message>
    <message>
        <source>Living room</source>
        <translation>Wohnzimmer</translation>
    </message>
    <message>
        <source>Address</source>
        <translation>Adresse</translation>
    </message>
    <message>
        <source>MAC address (for Wake-on-LAN)</source>
        <translation>MAC-Adresse (für Wake-on-LAN)</translation>
    </message>
    <message>
        <source>The MAC address is shown on the TV under Settings → General → About this TV. Without it everything works except powering on.</source>
        <translation>Die MAC-Adresse steht am Fernseher unter Einstellungen → Allgemein → Info zum TV. Ohne sie funktioniert alles außer dem Einschalten.</translation>
    </message>
    <message>
        <source>Apply</source>
        <translation>Übernehmen</translation>
    </message>
    <message>
        <source>Add and switch</source>
        <translation>Hinzufügen und wechseln</translation>
    </message>
</context>
<context>
    <name>DevicesPage</name>
    <message>
        <source>Devices</source>
        <translation>Geräte</translation>
    </message>
    <message>
        <source>Tapping switches to the device. The pairing key is stored per device, so switching needs no new confirmation.</source>
        <translation>Antippen wechselt zum Gerät. Der Kopplungsschlüssel wird je Gerät gespeichert – ein Wechsel verlangt also keine neue Bestätigung.</translation>
    </message>
    <message>
        <source>Searching ...</source>
        <translation>Suche läuft ...</translation>
    </message>
    <message>
        <source>Search the network</source>
        <translation>Fernseher im Netz suchen</translation>
    </message>
    <message>
        <source>Add device manually</source>
        <translation>Gerät von Hand hinzufügen</translation>
    </message>
    <message>
        <source>Edit</source>
        <translation>Bearbeiten</translation>
    </message>
    <message>
        <source>Remove</source>
        <translation>Entfernen</translation>
    </message>
    <message>
        <source>  ·  paired</source>
        <translation>  ·  gekoppelt</translation>
    </message>
    <message>
        <source>Found on the network</source>
        <translation>Im Netz gefunden</translation>
    </message>
    <message>
        <source>Nothing found. A TV in standby does not answer - switch it on and search again, or add it manually.</source>
        <translation>Nichts gefunden. Ein Fernseher im Bereitschaftsbetrieb antwortet nicht – einschalten und erneut suchen oder von Hand hinzufügen.</translation>
    </message>
    <message>
        <source>  ·  tap to add</source>
        <translation>  ·  antippen zum Übernehmen</translation>
    </message>
    <message>
        <source>No device</source>
        <translation>Kein Gerät</translation>
    </message>
    <message>
        <source>Search from the menu or add one manually</source>
        <translation>Über das Menü suchen oder von Hand hinzufügen</translation>
    </message>
    <message>
        <source>Disconnect</source>
        <translation>Trennen</translation>
    </message>
    <message>
        <source>Connect</source>
        <translation>Verbinden</translation>
    </message>
</context>
<context>
    <name>LgTv</name>
    <message>
        <source>external speaker</source>
        <translation>externer Lautsprecher</translation>
    </message>
    <message>
        <source>optical</source>
        <translation>optisch</translation>
    </message>
    <message>
        <source>TV speaker</source>
        <translation>TV-Lautsprecher</translation>
    </message>
    <message>
        <source>Bluetooth soundbar</source>
        <translation>Bluetooth-Soundbar</translation>
    </message>
    <message>
        <source>TV speaker + external</source>
        <translation>TV-Lautsprecher + extern</translation>
    </message>
    <message>
        <source>unknown</source>
        <translation>unbekannt</translation>
    </message>
    <message>
        <source>disconnected</source>
        <translation>getrennt</translation>
    </message>
    <message>
        <source>Certificate does not match - reset the pairing</source>
        <translation>Zertifikat passt nicht – Kopplung zurücksetzen</translation>
    </message>
    <message>
        <source>Error: %1</source>
        <translation>Fehler: %1</translation>
    </message>
    <message>
        <source>SSL in the Qt build: %1</source>
        <translation>SSL im Qt-Build: %1</translation>
    </message>
    <message>
        <source>yes</source>
        <translation>ja</translation>
    </message>
    <message>
        <source>NO</source>
        <translation>NEIN</translation>
    </message>
    <message>
        <source>SSL library: %1</source>
        <translation>SSL-Bibliothek: %1</translation>
    </message>
    <message>
        <source>Target: wss://%1:3001</source>
        <translation>Ziel: wss://%1:3001</translation>
    </message>
    <message>
        <source>Certificate: %1</source>
        <translation>Zertifikat: %1</translation>
    </message>
    <message>
        <source>Last rejected request: %1</source>
        <translation>Letzte abgelehnte Abfrage: %1</translation>
    </message>
    <message>
        <source>connecting ...</source>
        <translation>verbinde ...</translation>
    </message>
    <message>
        <source>no device</source>
        <translation>kein Gerät</translation>
    </message>
    <message>
        <source>connection lost</source>
        <translation>Verbindung verloren</translation>
    </message>
    <message>
        <source>no answer from the TV</source>
        <translation>keine Antwort vom Fernseher</translation>
    </message>
    <message>
        <source>waiting for confirmation on the TV</source>
        <translation>warte auf Bestätigung am Fernseher</translation>
    </message>
    <message>
        <source>signing in ...</source>
        <translation>melde an ...</translation>
    </message>
    <message>
        <source>connected</source>
        <translation>verbunden</translation>
    </message>
    <message>
        <source>insertText: accepted</source>
        <translation>insertText: angenommen</translation>
    </message>
    <message>
        <source>insertText rejected: %1</source>
        <translation>insertText abgelehnt: %1</translation>
    </message>
    <message>
        <source>Model</source>
        <translation>Modell</translation>
    </message>
    <message>
        <source>Serial number</source>
        <translation>Seriennummer</translation>
    </message>
    <message>
        <source>MAC wired</source>
        <translation>MAC Kabel</translation>
    </message>
    <message>
        <source>MAC Wi-Fi</source>
        <translation>MAC WLAN</translation>
    </message>
    <message>
        <source>MAC direct link</source>
        <translation>MAC Direktverbindung</translation>
    </message>
    <message>
        <source> - IP</source>
        <translation> – IP</translation>
    </message>
    <message>
        <source>Sound output</source>
        <translation>Tonausgabe</translation>
    </message>
    <message>
        <source>Volume</source>
        <translation>Lautstärke</translation>
    </message>
    <message>
        <source>%1 of %2</source>
        <translation>%1 von %2</translation>
    </message>
    <message>
        <source>no</source>
        <translation>nein</translation>
    </message>
    <message>
        <source>External control</source>
        <translation>Externe Steuerung</translation>
    </message>
    <message>
        <source>Volume adjustable</source>
        <translation>Lautstärke regelbar</translation>
    </message>
    <message>
        <source>Firmware</source>
        <translation>Firmware</translation>
    </message>
    <message>
        <source>Product</source>
        <translation>Produkt</translation>
    </message>
    <message>
        <source>YouTube: %1</source>
        <translation>YouTube: %1</translation>
    </message>
    <message>
        <source>no screenshot from the TV</source>
        <translation>kein Bildschirmfoto vom Fernseher</translation>
    </message>
    <message>
        <source>no answer while connecting</source>
        <translation>keine Antwort beim Verbinden</translation>
    </message>
    <message>
        <source>key channel stays closed</source>
        <translation>Tastenkanal bleibt zu</translation>
    </message>
    <message>
        <source>not connected</source>
        <translation>nicht verbunden</translation>
    </message>
    <message>
        <source>Mute</source>
        <translation>Stummschaltung</translation>
    </message>
    <message>
        <source>on</source>
        <translation>ein</translation>
    </message>
    <message>
        <source>off</source>
        <translation>aus</translation>
    </message>
    <message>
        <source>no answer</source>
        <translation>keine Antwort</translation>
    </message>
</context>
<context>
    <name>MainMenu</name>
    <message>
        <source>Settings</source>
        <translation>Einstellungen</translation>
    </message>
    <message>
        <source>Apps and inputs</source>
        <translation>Apps und Eingänge</translation>
    </message>
    <message>
        <source>System data</source>
        <translation>Systemdaten</translation>
    </message>
    <message>
        <source>About</source>
        <translation>Über</translation>
    </message>
    <message>
        <source>Connected devices</source>
        <translation>Verbundene Geräte</translation>
    </message>
</context>
<context>
    <name>PanelMain</name>
    <message>
        <source>muted</source>
        <translation>stumm</translation>
    </message>
    <message>
        <source>switched off</source>
        <translation>ausgeschaltet</translation>
    </message>
    <message>
        <source>wake-up signal sent</source>
        <translation>Einschaltsignal gesendet</translation>
    </message>
    <message>
        <source>invalid MAC address</source>
        <translation>MAC-Adresse ungültig</translation>
    </message>
    <message>
        <source>Back</source>
        <translation>Zurück</translation>
    </message>
    <message>
        <source>Info</source>
        <translation>Info</translation>
    </message>
    <message>
        <source>Input</source>
        <translation>Eingang</translation>
    </message>
    <message>
        <source>Settings</source>
        <translation>Einstellungen</translation>
    </message>
    <message>
        <source>Sound</source>
        <translation>Ton</translation>
    </message>
    <message>
        <source>Channel</source>
        <translation>Kanal</translation>
    </message>
</context>
<context>
    <name>PanelPad</name>
    <message>
        <source>Show keyboard</source>
        <translation>Tastatur einblenden</translation>
    </message>
    <message>
        <source>◀   swipe here to change page   ▶</source>
        <translation>◀   hier wischen zum Blättern   ▶</translation>
    </message>
    <message>
        <source>not connected</source>
        <translation>nicht verbunden</translation>
    </message>
    <message>
        <source>text to the TV</source>
        <translation>Text an den Fernseher</translation>
    </message>
    <message>
        <source>opening keyboard on the TV ...</source>
        <translation>oeffne Tastatur am Fernseher ...</translation>
    </message>
    <message>
        <source>no text field on the TV - use the magnifier for YouTube</source>
        <translation>kein Textfeld am Fernseher - für YouTube die Lupe nehmen</translation>
    </message>
</context>
<context>
    <name>PortScan</name>
    <message>
        <source>SSAP unencrypted (refused by the firmware)</source>
        <translation>SSAP unverschlüsselt (von der Firmware abgewiesen)</translation>
    </message>
    <message>
        <source>SSAP over TLS - the connection this app uses</source>
        <translation>SSAP über TLS – die Verbindung dieser App</translation>
    </message>
    <message>
        <source>AirPlay</source>
        <translation>AirPlay</translation>
    </message>
    <message>
        <source>Developer mode SSH</source>
        <translation>Developer Mode SSH</translation>
    </message>
    <message>
        <source>webOS internal</source>
        <translation>webOS intern</translation>
    </message>
    <message>
        <source>SSH</source>
        <translation>SSH</translation>
    </message>
    <message>
        <source>HTTP</source>
        <translation>HTTP</translation>
    </message>
    <message>
        <source>HTTPS</source>
        <translation>HTTPS</translation>
    </message>
    <message>
        <source>UPnP</source>
        <translation>UPnP</translation>
    </message>
    <message>
        <source>HTTP alternative</source>
        <translation>HTTP alternativ</translation>
    </message>
</context>
<context>
    <name>SettingsPage</name>
    <message>
        <source>Settings</source>
        <translation>Einstellungen</translation>
    </message>
    <message>
        <source>Service menus of the TV</source>
        <translation>Service-Menüs des Fernsehers</translation>
    </message>
    <message>
        <source>Warning: these menus are meant for service technicians. They expose picture, sound and device parameters that the normal menu does not reach. Changes can render the TV unusable and are partly irreversible. Only open them if you know what you are doing.</source>
        <translation>Achtung: Diese Menüs sind für den Kundendienst gedacht. Dort lassen sich Bild-, Ton- und Geräteparameter verstellen, die im normalen Menü nicht erreichbar sind. Änderungen können den Fernseher unbrauchbar machen und sind teils nicht zurücknehmbar. Nur öffnen, wenn du weißt, was du tust.</translation>
    </message>
    <message>
        <source>Opening %1</source>
        <translation>%1 wird geöffnet</translation>
    </message>
    <message>
        <source>Way out: the back key, or switch the TV off and on again.</source>
        <translation>Herauskommen: Zurück-Taste, notfalls den Fernseher aus- und wieder einschalten.</translation>
    </message>
    <message>
        <source>Device</source>
        <translation>Gerät</translation>
    </message>
    <message>
        <source>Name</source>
        <translation>Name</translation>
    </message>
    <message>
        <source>Address</source>
        <translation>Adresse</translation>
    </message>
    <message>
        <source>MAC</source>
        <translation>MAC</translation>
    </message>
    <message>
        <source>not stored</source>
        <translation>nicht hinterlegt</translation>
    </message>
    <message>
        <source>Wake-on-LAN has to be enabled on the TV: Settings → General → External devices → Turn on via mobile device.</source>
        <translation>Wake-on-LAN muss am Fernseher aktiviert sein: Einstellungen → Allgemein → Externe Geräte → Über Mobilgerät einschalten.</translation>
    </message>
    <message>
        <source>Match the volume</source>
        <translation>Lautstärke abgleichen</translation>
    </message>
    <message>
        <source>With the sound on an external device over ARC, the TV keeps a counter of its own that has nothing to do with the real level - the amplifier never reports back. Enter what the device shows and the display follows along.</source>
        <translation>Hängt der Ton über ARC an einem externen Gerät, führt der Fernseher einen eigenen Zähler, der mit dem echten Pegel nichts zu tun hat – die Anlage meldet ihren Stand nie zurück. Trag hier ein, was am Gerät steht, dann zieht die Anzeige nach.</translation>
    </message>
    <message>
        <source>Level on the audio device</source>
        <translation>Pegel am Tongerät</translation>
    </message>
    <message>
        <source>Set</source>
        <translation>Setzen</translation>
    </message>
    <message>
        <source>Pairing</source>
        <translation>Kopplung</translation>
    </message>
    <message>
        <source>Paired. The TV no longer asks.</source>
        <translation>Gekoppelt. Der Fernseher fragt nicht mehr nach.</translation>
    </message>
    <message>
        <source>Not paired yet. Connecting brings up a prompt on the TV.</source>
        <translation>Noch nicht gekoppelt. Beim Verbinden erscheint eine Abfrage am Fernseher.</translation>
    </message>
    <message>
        <source>Certificate</source>
        <translation>Zertifikat</translation>
    </message>
    <message>
        <source>Reset pairing</source>
        <translation>Kopplung zurücksetzen</translation>
    </message>
    <message>
        <source>Try a key code</source>
        <translation>Tastencode ausprobieren</translation>
    </message>
    <message>
        <source>The TV accepts about 450 key names and silently drops invalid ones. Try one here without rebuilding the app - QMENU, MYAPPS, RECENT, LIST, SIMPLINK, GUIDE or SCREEN_REMOTE for instance.</source>
        <translation>Der Fernseher nimmt rund 450 Tastennamen entgegen; ungültige verwirft er stumm. Hier lässt sich einer ausprobieren, ohne die App neu zu bauen – etwa QMENU, MYAPPS, RECENT, LIST, SIMPLINK, GUIDE oder SCREEN_REMOTE.</translation>
    </message>
    <message>
        <source>e.g. INPUT</source>
        <translation>z. B. INPUT</translation>
    </message>
    <message>
        <source>Key name</source>
        <translation>Tastenname</translation>
    </message>
    <message>
        <source>Send</source>
        <translation>Senden</translation>
    </message>
    <message>
        <source>Yedi master</source>
        <translation>Yedi-Master</translation>
    </message>
    <message>
        <source>Claim priority</source>
        <translation>Vorrang beanspruchen</translation>
    </message>
    <message>
        <source>While this app is in the foreground, the Android remotes in the house lock themselves. Put the phone away and they release after a minute.</source>
        <translation>Solange diese App im Vordergrund ist, sperren sich die Android-Fernbedienungen im Haus. Legst du das Telefon weg, geben sie nach einer Minute wieder frei.</translation>
    </message>
    <message>
        <source>Home Assistant</source>
        <translation>Home Assistant</translation>
    </message>
    <message>
        <source>Access token</source>
        <translation>Zugangstoken</translation>
    </message>
    <message>
        <source>long-lived token from Home Assistant</source>
        <translation>langlebiges Token aus Home Assistant</translation>
    </message>
    <message>
        <source>State</source>
        <translation>Zustand</translation>
    </message>
    <message>
        <source>Connection</source>
        <translation>Verbindung</translation>
    </message>
    <message>
        <source>open</source>
        <translation>offen</translation>
    </message>
    <message>
        <source>closed</source>
        <translation>getrennt</translation>
    </message>
    <message>
        <source>Paired</source>
        <translation>Gekoppelt</translation>
    </message>
    <message>
        <source>yes</source>
        <translation>ja</translation>
    </message>
    <message>
        <source>no</source>
        <translation>nein</translation>
    </message>
    <message>
        <source>Key channel</source>
        <translation>Tastenkanal</translation>
    </message>
    <message>
        <source>ready</source>
        <translation>bereit</translation>
    </message>
    <message>
        <source>not ready</source>
        <translation>nicht bereit</translation>
    </message>
    <message>
        <source>Message</source>
        <translation>Meldung</translation>
    </message>
    <message>
        <source>Text field on the TV</source>
        <translation>Textfeld am TV</translation>
    </message>
    <message>
        <source>ready (%1, %2 characters)</source>
        <translation>bereit (%1, %2 Zeichen)</translation>
    </message>
    <message>
        <source>no field open</source>
        <translation>kein Feld offen</translation>
    </message>
    <message>
        <source>Diagnostics</source>
        <translation>Diagnose</translation>
    </message>
</context>
<context>
    <name>SystemPage</name>
    <message>
        <source>Device</source>
        <translation>Gerät</translation>
    </message>
    <message>
        <source>Address</source>
        <translation>Adresse</translation>
    </message>
    <message>
        <source>State</source>
        <translation>Zustand</translation>
    </message>
    <message>
        <source>not connected</source>
        <translation>nicht verbunden</translation>
    </message>
    <message>
        <source>Network</source>
        <translation>Netzwerk</translation>
    </message>
    <message>
        <source>Sound and ARC</source>
        <translation>Ton und ARC</translation>
    </message>
    <message>
        <source>Inputs</source>
        <translation>Eingänge</translation>
    </message>
    <message>
        <source>Open ports</source>
        <translation>Offene Ports</translation>
    </message>
    <message>
        <source>open</source>
        <translation>offen</translation>
    </message>
    <message>
        <source>System data</source>
        <translation>Systemdaten</translation>
    </message>
    <message>
        <source>Reload</source>
        <translation>Neu einlesen</translation>
    </message>
    <message>
        <source>Encryption</source>
        <translation>Verschluesselung</translation>
    </message>
    <message>
        <source>Tuner</source>
        <translation>Empfangsteil</translation>
    </message>
</context>
<context>
    <name>TvIcons</name>
    <message>
        <source>Screenshot not fetched</source>
        <translation>Bildschirmfoto nicht geholt</translation>
    </message>
    <message>
        <source>Screenshot not saved</source>
        <translation>Bildschirmfoto nicht gespeichert</translation>
    </message>
</context>
<context>
    <name>harbour-lgremote</name>
    <message>
        <source>Television</source>
        <translation>Fernseher</translation>
    </message>
    <message>
        <source>Screenshot saved: %1</source>
        <translation>Bildschirmfoto gespeichert: %1</translation>
    </message>
</context>
</TS>
