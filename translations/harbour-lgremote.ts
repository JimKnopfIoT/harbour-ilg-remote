<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1">
<context>
    <name>AboutPage</name>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="18"/>
        <source>About</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="30"/>
        <source>LG remote</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="37"/>
        <source>Version %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="49"/>
        <source>Controls LG televisions running webOS over the network - no infrared, no line of sight. It speaks LG&apos;s own SSAP protocol, the same one the official remote app uses.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="52"/>
        <source>Technical notes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="60"/>
        <source>The connection uses &lt;b&gt;wss on port 3001&lt;/b&gt;. The unencrypted port 3000 that older remote apps use is refused by current firmware.

The TV identifies itself with a self-signed certificate; its fingerprint is remembered on the first connection and checked from then on. The TLS version is left to the library; the TV takes 1.2 as well as 1.3, but now and then it drops a handshake without answering - the app simply tries again.

The keys run over a second channel whose address the TV only hands out on request. Powering on works via Wake-on-LAN and needs the MAC address.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="64"/>
        <source>Origin</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="72"/>
        <source>Written from scratch. The idea for the touchpad and text entry comes from harbour-lgremote-webos by CODeRUS and Mazhoon (WTFPL); its code could not be reused because it relies on port 3000 and the QML WebSocket component.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>AppsPage</name>
    <message>
        <location filename="../qml/pages/AppsPage.qml" line="25"/>
        <source>Inputs</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AppsPage.qml" line="32"/>
        <source>Apps</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AppsPage.qml" line="53"/>
        <source>Assign tile</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AppsPage.qml" line="53"/>
        <source>Apps and inputs</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AppsPage.qml" line="59"/>
        <source>Restore the default tiles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AppsPage.qml" line="67"/>
        <source>Clear tile</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AppsPage.qml" line="73"/>
        <source>Reload</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AppsPage.qml" line="120"/>
        <source>Nothing found</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AppsPage.qml" line="121"/>
        <source>Is the television connected?</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>CoverPage</name>
    <message>
        <location filename="../qml/cover/CoverPage.qml" line="86"/>
        <source>muted</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/cover/CoverPage.qml" line="86"/>
        <source>connected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/cover/CoverPage.qml" line="87"/>
        <source>disconnected</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>DeviceEditPage</name>
    <message>
        <location filename="../qml/pages/DeviceEditPage.qml" line="25"/>
        <source>Edit device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DeviceEditPage.qml" line="25"/>
        <source>New device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DeviceEditPage.qml" line="30"/>
        <source>Name</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DeviceEditPage.qml" line="31"/>
        <source>Living room</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DeviceEditPage.qml" line="40"/>
        <source>Address</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DeviceEditPage.qml" line="51"/>
        <source>MAC address (for Wake-on-LAN)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DeviceEditPage.qml" line="65"/>
        <source>The MAC address is shown on the TV under Settings → General → About this TV. Without it everything works except powering on.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DeviceEditPage.qml" line="70"/>
        <source>Apply</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DeviceEditPage.qml" line="70"/>
        <source>Add and switch</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>DevicesPage</name>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="38"/>
        <source>Devices</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="46"/>
        <source>Tapping switches to the device. The pairing key is stored per device, so switching needs no new confirmation.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="54"/>
        <source>Searching ...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="54"/>
        <source>Search the network</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="59"/>
        <source>Add device manually</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="74"/>
        <source>Edit</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="79"/>
        <source>Remove</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="98"/>
        <source>  ·  paired</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="114"/>
        <source>Found on the network</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="123"/>
        <source>Nothing found. A TV in standby does not answer - switch it on and search again, or add it manually.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="146"/>
        <source>  ·  tap to add</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="166"/>
        <source>No device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="167"/>
        <source>Search from the menu or add one manually</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>LgTv</name>
    <message>
        <location filename="../src/lgtv.cpp" line="56"/>
        <source>external speaker</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="57"/>
        <source>optical</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="58"/>
        <source>TV speaker</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="59"/>
        <source>Bluetooth soundbar</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="61"/>
        <source>TV speaker + external</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="62"/>
        <source>unknown</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="72"/>
        <location filename="../src/lgtv.cpp" line="285"/>
        <source>disconnected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="93"/>
        <source>no answer while connecting</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="142"/>
        <source>Certificate does not match - reset the pairing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="151"/>
        <location filename="../src/lgtv.cpp" line="485"/>
        <source>Error: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="174"/>
        <source>SSL in the Qt build: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="174"/>
        <location filename="../src/lgtv.cpp" line="712"/>
        <location filename="../src/lgtv.cpp" line="714"/>
        <location filename="../src/lgtv.cpp" line="716"/>
        <source>yes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="174"/>
        <source>NO</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="175"/>
        <source>SSL library: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="176"/>
        <source>Target: wss://%1:3001</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="178"/>
        <source>Certificate: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="180"/>
        <source>Last rejected request: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="250"/>
        <location filename="../src/lgtv.cpp" line="375"/>
        <source>connecting ...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="261"/>
        <source>no device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="313"/>
        <source>connection lost</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="348"/>
        <source>no answer from the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="421"/>
        <source>waiting for confirmation on the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="422"/>
        <source>signing in ...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="447"/>
        <source>connected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="609"/>
        <source>insertText: accepted</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="610"/>
        <source>insertText rejected: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="659"/>
        <source>no screenshot from the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="679"/>
        <source>Model</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="680"/>
        <source>Serial number</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="681"/>
        <source>Tuner</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="689"/>
        <source>MAC wired</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="689"/>
        <source>MAC Wi-Fi</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="690"/>
        <source>MAC direct link</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="698"/>
        <source> - IP</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="707"/>
        <source>Sound output</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="708"/>
        <source>Volume</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="709"/>
        <source>%1 of %2</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="711"/>
        <source>Muted</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="712"/>
        <location filename="../src/lgtv.cpp" line="714"/>
        <location filename="../src/lgtv.cpp" line="716"/>
        <source>no</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="713"/>
        <source>External control</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="715"/>
        <source>Volume adjustable</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="722"/>
        <source>Firmware</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="725"/>
        <source>Product</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="960"/>
        <source>YouTube: %1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MainMenu</name>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="11"/>
        <source>Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="16"/>
        <source>Devices</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="21"/>
        <source>Apps and inputs</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="26"/>
        <source>Screenshot of the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="31"/>
        <source>System data</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="37"/>
        <source>About</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="41"/>
        <source>Disconnect</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="41"/>
        <source>Connect</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PanelMain</name>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="28"/>
        <source>muted</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="128"/>
        <source>switched off</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="144"/>
        <source>wake-up signal sent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="145"/>
        <source>invalid MAC address</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="186"/>
        <source>Back</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="190"/>
        <source>Info</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="208"/>
        <source>Input</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="214"/>
        <source>Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="230"/>
        <source>Sound</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="247"/>
        <source>Channel</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PanelPad</name>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="23"/>
        <source>Show keyboard</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="39"/>
        <source>◀   swipe here to change page   ▶</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="75"/>
        <source>not connected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="242"/>
        <source>search on YouTube</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="244"/>
        <source>opening keyboard on the TV ...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="245"/>
        <source>text to the TV</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PortScan</name>
    <message>
        <location filename="../src/portscan.cpp" line="15"/>
        <source>SSAP unencrypted (refused by the firmware)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/portscan.cpp" line="16"/>
        <source>SSAP over TLS - the connection this app uses</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/portscan.cpp" line="17"/>
        <source>AirPlay</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/portscan.cpp" line="18"/>
        <source>Developer mode SSH</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/portscan.cpp" line="19"/>
        <source>webOS internal</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/portscan.cpp" line="20"/>
        <source>SSH</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/portscan.cpp" line="21"/>
        <source>HTTP</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/portscan.cpp" line="22"/>
        <source>HTTPS</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/portscan.cpp" line="23"/>
        <source>UPnP</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/portscan.cpp" line="24"/>
        <source>HTTP alternative</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SettingsPage</name>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="22"/>
        <source>Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="32"/>
        <source>Service menus of the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="44"/>
        <source>Warning: these menus are meant for service technicians. They expose picture, sound and device parameters that the normal menu does not reach. Changes can render the TV unusable and are partly irreversible. Only open them if you know what you are doing.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="60"/>
        <source>Opening %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="72"/>
        <source>Way out: the back key, or switch the TV off and on again.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="80"/>
        <source>Device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="82"/>
        <source>Name</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="83"/>
        <source>Address</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="84"/>
        <source>MAC</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="85"/>
        <location filename="../qml/pages/SettingsPage.qml" line="167"/>
        <source>not stored</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="89"/>
        <source>Manage devices</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="100"/>
        <source>Wake-on-LAN has to be enabled on the TV: Settings → General → External devices → Turn on via mobile device.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="105"/>
        <source>Match the volume</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="113"/>
        <source>With the sound on an external device over ARC, the TV keeps a counter of its own that has nothing to do with the real level - the amplifier never reports back. Enter what the device shows and the display follows along.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="124"/>
        <source>Level on the audio device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="135"/>
        <source>Set</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="150"/>
        <source>Pairing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="159"/>
        <source>Paired. The TV no longer asks.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="160"/>
        <source>Not paired yet. Connecting brings up a prompt on the TV.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="164"/>
        <source>Certificate</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="172"/>
        <source>Reset pairing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="183"/>
        <source>Try a key code</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="191"/>
        <source>The TV accepts about 450 key names and silently drops invalid ones. Try one here without rebuilding the app - QMENU, MYAPPS, RECENT, LIST, SIMPLINK, GUIDE or SCREEN_REMOTE for instance.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="202"/>
        <source>e.g. INPUT</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="203"/>
        <source>Key name</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="213"/>
        <source>Send</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="226"/>
        <source>State</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="228"/>
        <source>Connection</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="228"/>
        <source>open</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="228"/>
        <source>closed</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="229"/>
        <source>Paired</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="229"/>
        <source>yes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="229"/>
        <source>no</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="230"/>
        <source>Key channel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="230"/>
        <source>ready</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="231"/>
        <source>not ready</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="232"/>
        <source>Message</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="233"/>
        <source>Text field on the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="235"/>
        <source>ready (%1, %2 characters)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="237"/>
        <source>no field open</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="239"/>
        <source>Diagnostics</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SystemPage</name>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="27"/>
        <source>Device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="28"/>
        <source>Address</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="31"/>
        <source>State</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="31"/>
        <source>not connected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="49"/>
        <source>Network</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="53"/>
        <source>Sound and ARC</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="57"/>
        <source>Inputs</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="66"/>
        <source>Open ports</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="67"/>
        <source>open</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="81"/>
        <source>System data</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="85"/>
        <source>Reload</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TvIcons</name>
    <message>
        <location filename="../src/tvicons.cpp" line="150"/>
        <source>Screenshot not fetched</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="156"/>
        <source>Screenshot not saved</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>harbour-lgremote</name>
    <message>
        <location filename="../qml/harbour-lgremote.qml" line="64"/>
        <source>Television</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/harbour-lgremote.qml" line="182"/>
        <source>Screenshot saved: %1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
