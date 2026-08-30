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
    <message>
        <source>Glossary</source>
        <translation>Glossar</translation>
    </message>
    <message>
        <source>Error log (%1)</source>
        <translation>Fehlerprotokoll (%1)</translation>
    </message>
    <message>
        <source>Error log - empty</source>
        <translation>Fehlerprotokoll – leer</translation>
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
    <message>
        <source>Check availability</source>
        <translation>Erreichbarkeit prüfen</translation>
    </message>
    <message>
        <source>Not available, offline</source>
        <translation>Nicht verfügbar, offline</translation>
    </message>
    <message>
        <source>on</source>
        <translation>ein</translation>
    </message>
    <message>
        <source>standby · reachable</source>
        <translation>Standby · erreichbar</translation>
    </message>
    <message>
        <source>reachable</source>
        <translation>erreichbar</translation>
    </message>
    <message>
        <source>off</source>
        <translation>aus</translation>
    </message>
    <message>
        <source>%1 does not answer. It is disconnected from the mains or network standby is switched off - the power key on the first page sends the wake-up signal anyway.</source>
        <translation>%1 antwortet nicht. Vom Stromnetz getrennt, oder der Netzwerk-Standby ist abgeschaltet – die Ein-/Aus-Taste auf der ersten Seite schickt das Wecksignal trotzdem.</translation>
    </message>
    <message>
        <source>Reset pairing</source>
        <translation>Kopplung zurücksetzen</translation>
    </message>
    <message>
        <source>Pairing released. Tapping the device connects again - the TV then asks once more.</source>
        <translation>Kopplung gelöst. Ein Tipp auf das Gerät verbindet erneut – der Fernseher fragt dann wieder nach.</translation>
    </message>
    <message>
        <source>Forget device</source>
        <translation>Gerät vergessen</translation>
    </message>
    <message>
        <source>Forgetting</source>
        <translation>Wird vergessen</translation>
    </message>
</context>
<context>
    <name>Discovery</name>
    <message>
        <source>Search</source>
        <translation>Suche</translation>
    </message>
    <message>
        <source>no UDP socket for the search - is the phone on a network?</source>
        <translation>kein UDP-Socket für die Suche – hängt das Telefon in einem Netz?</translation>
    </message>
    <message>
        <source>no interface accepted the multicast - trying the default route</source>
        <translation>keine Schnittstelle nahm das Multicast an – Versuch über die Vorgaberoute</translation>
    </message>
    <message>
        <source>no address of our own in the local network - search not possible</source>
        <translation>keine eigene Adresse im lokalen Netz – Suche nicht möglich</translation>
    </message>
    <message>
        <source>device found, but it does not give up its name</source>
        <translation>Gerät gefunden, aber es rückt seinen Namen nicht heraus</translation>
    </message>
    <message>
        <source>network too large to scan - add the TV by hand</source>
        <translation>Netz zu groß zum Abklopfen – den Fernseher von Hand eintragen</translation>
    </message>
    <message>
        <source>nothing found - neither by SSDP nor on port 3001</source>
        <translation>nichts gefunden – weder per SSDP noch auf Port 3001</translation>
    </message>
</context>
<context>
    <name>ErrorLogPage</name>
    <message>
        <source>Error log</source>
        <translation>Fehlerprotokoll</translation>
    </message>
    <message>
        <source>Everything the app promised and could not deliver ends up here: a wake-up signal without a MAC address, a key without a key channel, an icon the TV would not hand out. Newest first. The log lives in memory only and is gone when the app closes.</source>
        <translation>Alles, was die App zugesagt und nicht gehalten hat, steht hier: ein Wecksignal ohne MAC-Adresse, ein Tastendruck ohne Tastenkanal, ein Symbol, das der Fernseher nicht herausgab. Neueste zuerst. Das Protokoll steht nur im Arbeitsspeicher und ist mit dem Beenden weg.</translation>
    </message>
    <message>
        <source>Copy to clipboard</source>
        <translation>In die Zwischenablage</translation>
    </message>
    <message>
        <source>Clear</source>
        <translation>Leeren</translation>
    </message>
    <message>
        <source>Nothing to report</source>
        <translation>Nichts zu melden</translation>
    </message>
    <message>
        <source>That is the normal case: everything the app started, it finished.</source>
        <translation>Das ist der Normalfall: Was die App angefangen hat, hat sie auch zu Ende gebracht.</translation>
    </message>
</context>
<context>
    <name>GlossaryPage</name>
    <message>
        <source>Keys</source>
        <translation>Tasten</translation>
    </message>
    <message>
        <source>Power</source>
        <translation>Ein/Aus</translation>
    </message>
    <message>
        <source>Back</source>
        <translation>Zurück</translation>
    </message>
    <message>
        <source>The back key of the remote. Goes over the key channel, like the arrow keys.</source>
        <translation>Die Zurück-Taste der Fernbedienung. Geht über den Tastenkanal, wie das Steuerkreuz.</translation>
    </message>
    <message>
        <source>Home</source>
        <translation>Startseite</translation>
    </message>
    <message>
        <source>Opens the home screen of the TV.</source>
        <translation>Öffnet die Startseite des Fernsehers.</translation>
    </message>
    <message>
        <source>Info</source>
        <translation>Info</translation>
    </message>
    <message>
        <source>Shows the programme information of the current channel.</source>
        <translation>Zeigt die Sendungsinformation des laufenden Kanals.</translation>
    </message>
    <message>
        <source>Guide</source>
        <translation>Programmführer</translation>
    </message>
    <message>
        <source>Opens the programme guide.</source>
        <translation>Öffnet den Programmführer.</translation>
    </message>
    <message>
        <source>Input</source>
        <translation>Eingang</translation>
    </message>
    <message>
        <source>A short tap steps through the inputs like the input key of the original remote. Hold it to get the list of all inputs and apps and switch directly.</source>
        <translation>Kurz tippen schaltet die Eingänge weiter wie die Eingangstaste des Originals. Halten öffnet die Liste aller Eingänge und Apps und schaltet direkt um.</translation>
    </message>
    <message>
        <source>Settings of the TV</source>
        <translation>Einstellungen des Fernsehers</translation>
    </message>
    <message>
        <source>The gear sends the MENU key and opens the settings on the TV. It is greyed out while the key channel is closed - the app&apos;s own settings are in the pull-down menu.</source>
        <translation>Das Zahnrad schickt die Taste MENU und öffnet die Einstellungen am Fernseher. Es ist blass, solange der Tastenkanal zu ist – die Einstellungen der App stehen im Ausklappmenü.</translation>
    </message>
    <message>
        <source>Text row</source>
        <translation>Textzeile</translation>
    </message>
    <message>
        <source>Send text</source>
        <translation>Text schicken</translation>
    </message>
    <message>
        <source>Puts the typed text into the input field open on the TV. Without a field the TV discards the text - the error log says so when that happens.</source>
        <translation>Setzt den eingegebenen Text in das offene Feld am Fernseher. Ohne Feld verwirft der Fernseher ihn – das Fehlerprotokoll sagt es dann.</translation>
    </message>
    <message>
        <source>Search on YouTube</source>
        <translation>Bei YouTube suchen</translation>
    </message>
    <message>
        <source>Hands the term to YouTube as a launch parameter. No on-screen keyboard is involved, which is why this way works even where the app draws its own keyboard.</source>
        <translation>Gibt den Begriff als Startparameter an YouTube. Dabei ist keine Bildschirmtastatur im Spiel – deshalb greift dieser Weg auch dort, wo die App ihre eigene Tastatur zeichnet.</translation>
    </message>
    <message>
        <source>Clear the field</source>
        <translation>Feld leeren</translation>
    </message>
    <message>
        <source>Empties the text field in the app - not on the TV.</source>
        <translation>Leert das Textfeld in der App – nicht am Fernseher.</translation>
    </message>
    <message>
        <source>Tiles</source>
        <translation>Kacheln</translation>
    </message>
    <message>
        <source>Screenshot</source>
        <translation>Bildschirmfoto</translation>
    </message>
    <message>
        <source>Four corners around a lens: the TV takes a picture of its own screen and the app saves it to the gallery under LG Remote. The TV refuses this while copy protection is active - a film from a streaming app usually comes out black.</source>
        <translation>Vier Ecken um eine Linse: Der Fernseher fotografiert seinen eigenen Bildschirm, die App legt das Bild in der Galerie unter LG Remote ab. Bei aktivem Kopierschutz verweigert er das – ein Film aus einer Streaming-App kommt meist schwarz heraus.</translation>
    </message>
    <message>
        <source>Free tile</source>
        <translation>Freie Kachel</translation>
    </message>
    <message>
        <source>An empty tile. Tap it to pick an app or an input; a long press on any tile reassigns it.</source>
        <translation>Eine leere Kachel. Tippen wählt eine App oder einen Eingang; langes Drücken belegt jede Kachel neu.</translation>
    </message>
    <message>
        <source>Devices</source>
        <translation>Geräte</translation>
    </message>
    <message>
        <source>paired</source>
        <translation>gekoppelt</translation>
    </message>
    <message>
        <source>A pairing key for this TV is stored. Switching devices then needs no new confirmation on the screen.</source>
        <translation>Für diesen Fernseher liegt ein Kopplungsschlüssel vor. Ein Gerätewechsel braucht dann keine neue Bestätigung am Bildschirm.</translation>
    </message>
    <message>
        <source>Words</source>
        <translation>Wörter</translation>
    </message>
    <message>
        <source>ARC</source>
        <translation>ARC</translation>
    </message>
    <message>
        <source>The sound runs over the HDMI return channel to an external device. The TV then only counts steps and never learns the real volume - that is why a number would be misleading and ARC is shown instead.</source>
        <translation>Der Ton läuft über den HDMI-Rückkanal an ein fremdes Gerät. Der Fernseher zählt dann nur Schritte und erfährt den wirklichen Pegel nie – eine Zahl wäre irreführend, deshalb steht dort ARC.</translation>
    </message>
    <message>
        <source>SSAP</source>
        <translation>SSAP</translation>
    </message>
    <message>
        <source>LG&apos;s own protocol on port 3001, the same one the official remote app uses. Encrypted, with the self-signed certificate of the TV.</source>
        <translation>Das eigene Protokoll von LG auf Port 3001, dasselbe, das die offizielle Fernbedien-App benutzt. Verschlüsselt, mit dem selbstsignierten Zertifikat des Fernsehers.</translation>
    </message>
    <message>
        <source>Wake-on-LAN</source>
        <translation>Wake-on-LAN</translation>
    </message>
    <message>
        <source>A broadcast packet that wakes the TV. It is addressed by MAC, not by IP - without the MAC address there is no switching on. The TV only names it while connected; it can also be typed in under Devices.</source>
        <translation>Ein Rundsendepaket, das den Fernseher weckt. Es wird über die MAC angesprochen, nicht über die IP – ohne MAC-Adresse kein Einschalten. Der Fernseher nennt sie nur im verbundenen Zustand; unter Geräte lässt sie sich auch eintragen.</translation>
    </message>
    <message>
        <source>Glossary</source>
        <translation>Glossar</translation>
    </message>
    <message>
        <source>What the symbols on the pages mean.</source>
        <translation>Was die Zeichen auf den Seiten bedeuten.</translation>
    </message>
    <message>
        <source>Short tap sends the wake-up signal over the network (Wake-on-LAN); holding it for two seconds switches the TV off. The colour is the state of the TV, not of the connection: green running, steady orange in standby, blinking orange while connecting, red no connection.</source>
        <translation>Kurz tippen schickt das Wecksignal über das Netz (Wake-on-LAN), zwei Sekunden halten schaltet den Fernseher aus. Die Farbe ist der Zustand des Fernsehers, nicht der der Verbindung: grün läuft, ruhiges Orange Bereitschaft, blinkendes Orange im Aufbau, rot keine Verbindung.</translation>
    </message>
    <message>
        <source>green - on</source>
        <translation>grün – an</translation>
    </message>
    <message>
        <source>The TV says so itself: it is running and can be operated. Only the TV the app is connected to can say this.</source>
        <translation>Der Fernseher sagt es selbst: Er läuft und lässt sich bedienen. Sagen kann das nur der Fernseher, mit dem die App verbunden ist.</translation>
    </message>
    <message>
        <source>orange - standby or reachable</source>
        <translation>orange – Bereitschaft oder erreichbar</translation>
    </message>
    <message>
        <source>red - off</source>
        <translation>rot – aus</translation>
    </message>
    <message>
        <source>No answer at all: disconnected from the mains, or network standby switched off in the TV settings. It stays in the list - the power key sends the wake-up signal, which needs the MAC address.</source>
        <translation>Gar keine Antwort: vom Stromnetz getrennt, oder der Netzwerk-Standby ist in den Einstellungen des Fernsehers abgeschaltet. Er bleibt in der Liste – die Ein-/Aus-Taste schickt das Wecksignal, und das braucht die MAC-Adresse.</translation>
    </message>
    <message>
        <source>The TV answers on port 3001, but it is not running: network standby. Answering is not the same as being awake, which is why this is not green. For a TV the app is not connected to, the state cannot be told apart - it then only says reachable.</source>
        <translation>Der Fernseher antwortet auf Port 3001, läuft aber nicht: Netzwerk-Standby. Antworten ist nicht wach sein, deshalb steht hier kein Grün. Bei einem Fernseher, mit dem die App nicht verbunden ist, lässt sich der Zustand nicht unterscheiden – dann steht dort nur erreichbar.</translation>
    </message>
    <message>
        <source>tap and hold</source>
        <translation>Tippen und Halten</translation>
    </message>
    <message>
        <source>A tap switches to the device and opens its system data - there you can see what state it is in. Holding the entry opens the menu: edit, release the pairing, forget the device. Its first line is deliberately empty so that letting go does nothing.</source>
        <translation>Ein Tipp wechselt auf das Gerät und öffnet seine Systemdaten – dort steht, woran man ist. Halten öffnet das Menü: bearbeiten, Kopplung zurücksetzen, Gerät vergessen. Die erste Zeile darin ist mit Absicht leer, damit Loslassen nichts auslöst.</translation>
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
    <message>
        <source>Connection</source>
        <translation>Verbindung</translation>
    </message>
    <message>
        <source>no answer during the TLS handshake</source>
        <translation>keine Antwort beim TLS-Handschlag</translation>
    </message>
    <message>
        <source>Certificate</source>
        <translation>Zertifikat</translation>
    </message>
    <message>
        <source>the TV shows a different certificate than the one remembered - reset the pairing</source>
        <translation>der Fernseher zeigt ein anderes Zertifikat als das gemerkte – Kopplung zurücksetzen</translation>
    </message>
    <message>
        <source>no sign of life within 8 s - the connection counts as dead</source>
        <translation>kein Lebenszeichen binnen 8 s – die Verbindung gilt als tot</translation>
    </message>
    <message>
        <source>Key channel</source>
        <translation>Tastenkanal</translation>
    </message>
    <message>
        <source>the TV does not hand out the address for the key channel - arrow keys, OK and Back stay locked</source>
        <translation>der Fernseher rückt die Adresse für den Tastenkanal nicht heraus – Steuerkreuz, OK und Zurück bleiben gesperrt</translation>
    </message>
    <message>
        <source>Sign-on</source>
        <translation>Anmeldung</translation>
    </message>
    <message>
        <source>volume</source>
        <translation>Lautstärke</translation>
    </message>
    <message>
        <source>key channel</source>
        <translation>Tastenkanal</translation>
    </message>
    <message>
        <source>app list</source>
        <translation>App-Liste</translation>
    </message>
    <message>
        <source>input list</source>
        <translation>Eingangsliste</translation>
    </message>
    <message>
        <source>system data</source>
        <translation>Systemdaten</translation>
    </message>
    <message>
        <source>network data (MAC address)</source>
        <translation>Netzdaten (MAC-Adresse)</translation>
    </message>
    <message>
        <source>sound settings</source>
        <translation>Toneinstellungen</translation>
    </message>
    <message>
        <source>channel</source>
        <translation>Kanal</translation>
    </message>
    <message>
        <source>remote keyboard</source>
        <translation>Fernbedienungstastatur</translation>
    </message>
    <message>
        <source>text entry</source>
        <translation>Texteingabe</translation>
    </message>
    <message>
        <source>app state</source>
        <translation>App-Zustand</translation>
    </message>
    <message>
        <source>sign of life</source>
        <translation>Lebenszeichen</translation>
    </message>
    <message>
        <source>screenshot</source>
        <translation>Bildschirmfoto</translation>
    </message>
    <message>
        <source>command</source>
        <translation>Befehl</translation>
    </message>
    <message>
        <source>Command not sent</source>
        <translation>Befehl nicht abgesetzt</translation>
    </message>
    <message>
        <source>not signed on to the TV</source>
        <translation>nicht am Fernseher angemeldet</translation>
    </message>
    <message>
        <source>the TV answered without an address for the key channel</source>
        <translation>der Fernseher antwortete ohne Adresse für den Tastenkanal</translation>
    </message>
    <message>
        <source>Text entry</source>
        <translation>Texteingabe</translation>
    </message>
    <message>
        <source>the TV rejected the text</source>
        <translation>der Fernseher hat den Text abgelehnt</translation>
    </message>
    <message>
        <source>Screenshot</source>
        <translation>Bildschirmfoto</translation>
    </message>
    <message>
        <source>the TV took the order but names no image</source>
        <translation>der Fernseher nahm den Auftrag an, nennt aber kein Bild</translation>
    </message>
    <message>
        <source>MAC address</source>
        <translation>MAC-Adresse</translation>
    </message>
    <message>
        <source>the TV answered without a MAC address - no wake-on-LAN possible</source>
        <translation>der Fernseher antwortete ohne MAC-Adresse – kein Wake-on-LAN möglich</translation>
    </message>
    <message>
        <source>Key</source>
        <translation>Taste</translation>
    </message>
    <message>
        <source>key channel not open - keystroke discarded</source>
        <translation>Tastenkanal nicht offen – Tastendruck verfallen</translation>
    </message>
    <message>
        <source>Pointer</source>
        <translation>Zeiger</translation>
    </message>
    <message>
        <source>key channel not open - click discarded</source>
        <translation>Tastenkanal nicht offen – Klick verfallen</translation>
    </message>
    <message>
        <source>no input field focused on the TV - the text may be discarded</source>
        <translation>kein Feld am Fernseher im Zugriff – der Text kann verworfen werden</translation>
    </message>
    <message>
        <source>asked three times without success - enter the MAC by hand under Connected devices</source>
        <translation>dreimal vergeblich gefragt – die MAC unter Verbundene Geräte von Hand eintragen</translation>
    </message>
    <message>
        <source>power state</source>
        <translation>Einschaltzustand</translation>
    </message>
    <message>
        <source>the TV does not state whether it is running - the device list cannot tell on from standby</source>
        <translation>der Fernseher nennt seinen Einschaltzustand nicht – die Geräteliste kann an nicht von Bereitschaft unterscheiden</translation>
    </message>
    <message>
        <source>the built-in handshake is unreadable - pairing is impossible</source>
        <translation>der eingebaute Anmelde-Handschlag ist unlesbar – Koppeln nicht möglich</translation>
    </message>
    <message>
        <source>the TV names an address outside itself for the key channel - not opened</source>
        <translation>der Fernseher nennt für den Tastenkanal eine Adresse außerhalb seiner selbst – nicht geöffnet</translation>
    </message>
    <message>
        <source>the TV names the image somewhere other than on itself - not fetched</source>
        <translation>der Fernseher nennt das Bild woanders als bei sich selbst – nicht geholt</translation>
    </message>
    <message>
        <source>%1 characters</source>
        <translation>%1 Zeichen</translation>
    </message>
    <message>
        <source>%1 entries name their icon outside the TV - icons ignored</source>
        <translation>%1 Einträge nennen ihr Symbol außerhalb des Fernsehers – Symbole übergangen</translation>
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
    <message>
        <source>no MAC address stored - see the error log</source>
        <translation>keine MAC-Adresse hinterlegt – siehe Fehlerprotokoll</translation>
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
        <source>no TV - text stays here</source>
        <translation>kein Fernseher - der Text bleibt hier</translation>
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
    <message>
        <source>A pairing belongs to one television. Releasing it is therefore done in the device list: hold the entry, then Reset pairing.</source>
        <translation>Eine Kopplung gehört zu einem Fernseher. Gelöst wird sie deshalb in der Geräteliste: Eintrag halten, dann Kopplung zurücksetzen.</translation>
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
    <message>
        <source>Error log (%1)</source>
        <translation>Fehlerprotokoll (%1)</translation>
    </message>
    <message>
        <source>Error log - empty</source>
        <translation>Fehlerprotokoll – leer</translation>
    </message>
    <message>
        <source>not stated</source>
        <translation>nicht genannt</translation>
    </message>
    <message>
        <source>on</source>
        <translation>ein</translation>
    </message>
    <message>
        <source>on, screen dark</source>
        <translation>an, Bildschirm dunkel</translation>
    </message>
    <message>
        <source>standby</source>
        <translation>Bereitschaft</translation>
    </message>
    <message>
        <source>connecting ...</source>
        <translation>verbinde ...</translation>
    </message>
    <message>
        <source>Power state</source>
        <translation>Einschaltzustand</translation>
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
    <message>
        <source>Icon</source>
        <translation>Symbol</translation>
    </message>
    <message>
        <source>no certificate remembered yet - connect to the TV once, then the icons will load</source>
        <translation>noch kein Zertifikat gemerkt – einmal mit dem Fernseher verbinden, dann laden die Symbole</translation>
    </message>
    <message>
        <source>not fetched from the TV after three tries</source>
        <translation>nach drei Versuchen nicht vom Fernseher geholt</translation>
    </message>
    <message>
        <source>the TV shows a different certificate than the one remembered</source>
        <translation>der Fernseher zeigt ein anderes Zertifikat als das gemerkte</translation>
    </message>
    <message>
        <source>TLS error without a certificate to check</source>
        <translation>TLS-Fehler ohne Zertifikat zum Prüfen</translation>
    </message>
    <message>
        <source>Screenshot</source>
        <translation>Bildschirmfoto</translation>
    </message>
    <message>
        <source>not fetched from the TV</source>
        <translation>nicht vom Fernseher geholt</translation>
    </message>
    <message>
        <source>could not be written to the gallery</source>
        <translation>ließ sich nicht in die Galerie schreiben</translation>
    </message>
    <message>
        <source>Tile</source>
        <translation>Kachel</translation>
    </message>
    <message>
        <source>icon not fetched: no certificate of the TV remembered yet</source>
        <translation>Symbol nicht geholt: noch kein Zertifikat des Fernsehers gemerkt</translation>
    </message>
    <message>
        <source>icon not fetched from the TV</source>
        <translation>Symbol nicht vom Fernseher geholt</translation>
    </message>
    <message>
        <source>icon could not be cached</source>
        <translation>Symbol ließ sich nicht zwischenspeichern</translation>
    </message>
    <message>
        <source>this address does not lead to the TV - not fetched</source>
        <translation>diese Adresse führt nicht zum Fernseher – nicht geholt</translation>
    </message>
    <message>
        <source>icon not fetched: this address does not lead to the TV</source>
        <translation>Symbol nicht geholt: diese Adresse führt nicht zum Fernseher</translation>
    </message>
</context>
<context>
    <name>Wol</name>
    <message>
        <source>Wake-on-LAN</source>
        <translation>Wake-on-LAN</translation>
    </message>
    <message>
        <source>no MAC address stored for this device - the TV only names it while connected, or enter it by hand</source>
        <translation>für dieses Gerät ist keine MAC-Adresse hinterlegt – der Fernseher nennt sie nur im verbundenen Zustand, sonst von Hand eintragen</translation>
    </message>
    <message>
        <source>the stored MAC address does not have twelve hex digits</source>
        <translation>die hinterlegte MAC-Adresse hat keine zwölf Hexziffern</translation>
    </message>
    <message>
        <source>the stored MAC address contains characters that are not hex digits</source>
        <translation>die hinterlegte MAC-Adresse enthält Zeichen, die keine Hexziffern sind</translation>
    </message>
    <message>
        <source>the magic packet could not be sent - no network on the phone?</source>
        <translation>das Weckpaket ging nicht hinaus – kein Netz am Telefon?</translation>
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
    <message>
        <source>Devices</source>
        <translation>Geräte</translation>
    </message>
    <message>
        <source>the stored device list is unreadable</source>
        <translation>die gespeicherte Geräteliste ist unlesbar</translation>
    </message>
    <message>
        <source>Tiles</source>
        <translation>Kacheln</translation>
    </message>
    <message>
        <source>the stored tiles are unreadable</source>
        <translation>die gespeicherten Kacheln sind unlesbar</translation>
    </message>
    <message>
        <source>Tile</source>
        <translation>Kachel</translation>
    </message>
    <message>
        <source>the TV names no icon for this entry</source>
        <translation>der Fernseher nennt zu diesem Eintrag kein Symbol</translation>
    </message>
</context>
</TS>
