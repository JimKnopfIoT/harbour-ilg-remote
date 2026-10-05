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
        <location filename="../qml/pages/AboutPage.qml" line="46"/>
        <source>Glossary</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="54"/>
        <source>Error log (%1)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="55"/>
        <source>Error log - empty</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="66"/>
        <source>Controls LG televisions running webOS over the network - no infrared, no line of sight. It speaks LG&apos;s own SSAP protocol, the same one the official remote app uses.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="69"/>
        <source>Technical notes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="77"/>
        <source>The connection uses &lt;b&gt;wss on port 3001&lt;/b&gt;. The unencrypted port 3000 that older remote apps use is refused by current firmware.

The TV identifies itself with a self-signed certificate; its fingerprint is remembered on the first connection and checked from then on. The TLS version is left to the library; the TV takes 1.2 as well as 1.3, but now and then it drops a handshake without answering - the app simply tries again.

The keys run over a second channel whose address the TV only hands out on request. Powering on works via Wake-on-LAN and needs the MAC address.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="81"/>
        <source>Origin</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AboutPage.qml" line="89"/>
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
        <location filename="../qml/pages/AppsPage.qml" line="136"/>
        <source>Nothing found</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/AppsPage.qml" line="137"/>
        <source>Is the television connected?</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>CoverPage</name>
    <message>
        <location filename="../qml/cover/CoverPage.qml" line="91"/>
        <source>muted</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/cover/CoverPage.qml" line="91"/>
        <source>connected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/cover/CoverPage.qml" line="92"/>
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
        <location filename="../qml/pages/DevicesPage.qml" line="72"/>
        <source>Devices</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="80"/>
        <source>Tapping switches to the device. The pairing key is stored per device, so switching needs no new confirmation.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="99"/>
        <source>Disconnect</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="99"/>
        <source>Connect</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="103"/>
        <source>Searching ...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="103"/>
        <source>Search the network</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="108"/>
        <source>Check availability</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="112"/>
        <source>Add device manually</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="149"/>
        <source>Edit</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="154"/>
        <source>Reset pairing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="159"/>
        <source>Pairing released. Tapping the device connects again - the TV then asks once more.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="163"/>
        <source>Forget device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="164"/>
        <source>Forgetting</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="199"/>
        <source>on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="200"/>
        <source>standby · reachable</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="201"/>
        <source>reachable</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="202"/>
        <source>off</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="218"/>
        <source>  ·  paired</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="231"/>
        <source>Not available, offline</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="232"/>
        <source>%1 does not answer. It is disconnected from the mains or network standby is switched off - the power key on the first page sends the wake-up signal anyway.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="247"/>
        <source>Found on the network</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="256"/>
        <source>Nothing found. A TV in standby does not answer - switch it on and search again, or add it manually.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="279"/>
        <source>  ·  tap to add</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="299"/>
        <source>No device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/DevicesPage.qml" line="300"/>
        <source>Search from the menu or add one manually</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Discovery</name>
    <message>
        <location filename="../src/discovery.cpp" line="127"/>
        <location filename="../src/discovery.cpp" line="160"/>
        <location filename="../src/discovery.cpp" line="197"/>
        <location filename="../src/discovery.cpp" line="210"/>
        <location filename="../src/discovery.cpp" line="255"/>
        <location filename="../src/discovery.cpp" line="324"/>
        <source>Search</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/discovery.cpp" line="127"/>
        <source>no UDP socket for the search - is the phone on a network?</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/discovery.cpp" line="161"/>
        <source>no interface accepted the multicast - trying the default route</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/discovery.cpp" line="198"/>
        <source>no address of our own in the local network - search not possible</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/discovery.cpp" line="211"/>
        <source>network too large to scan - add the TV by hand</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/discovery.cpp" line="256"/>
        <source>nothing found - neither by SSDP nor on port 3001</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/discovery.cpp" line="324"/>
        <source>device found, but it does not give up its name</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>ErrorLogPage</name>
    <message>
        <location filename="../qml/pages/ErrorLogPage.qml" line="20"/>
        <source>Error log</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/ErrorLogPage.qml" line="28"/>
        <source>Everything the app promised and could not deliver ends up here: a wake-up signal without a MAC address, a key without a key channel, an icon the TV would not hand out. Newest first. The log lives in memory only and is gone when the app closes.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/ErrorLogPage.qml" line="36"/>
        <source>Copy to clipboard</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/ErrorLogPage.qml" line="41"/>
        <source>Clear</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/ErrorLogPage.qml" line="86"/>
        <source>Nothing to report</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/ErrorLogPage.qml" line="87"/>
        <source>That is the normal case: everything the app started, it finished.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>GlossaryPage</name>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="15"/>
        <source>Keys</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="17"/>
        <source>Power</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="18"/>
        <source>Short tap sends the wake-up signal over the network (Wake-on-LAN); holding it for two seconds switches the TV off. The colour is the state of the TV, not of the connection: green running, steady orange in standby, blinking orange while connecting, red no connection.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="20"/>
        <source>Back</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="21"/>
        <source>The back key of the remote. Goes over the key channel, like the arrow keys.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="22"/>
        <source>Home</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="23"/>
        <source>Opens the home screen of the TV.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="24"/>
        <source>Info</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="25"/>
        <source>Shows the programme information of the current channel.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="26"/>
        <source>Guide</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="27"/>
        <source>Opens the programme guide.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="28"/>
        <source>Input</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="29"/>
        <source>A short tap steps through the inputs like the input key of the original remote. Hold it to get the list of all inputs and apps and switch directly.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="30"/>
        <source>Settings of the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="31"/>
        <source>The gear sends the MENU key and opens the settings on the TV. It is greyed out while the key channel is closed - the app&apos;s own settings are in the pull-down menu.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="33"/>
        <source>Text row</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="34"/>
        <source>Send text</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="35"/>
        <source>Puts the typed text into the input field open on the TV. Without a field the TV discards the text - the error log says so when that happens.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="36"/>
        <source>Search on YouTube</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="37"/>
        <source>Hands the term to YouTube as a launch parameter. No on-screen keyboard is involved, which is why this way works even where the app draws its own keyboard.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="38"/>
        <source>Clear the field</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="39"/>
        <source>Empties the text field in the app - not on the TV.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="41"/>
        <source>Tiles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="42"/>
        <source>Screenshot</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="43"/>
        <source>Four corners around a lens: the TV takes a picture of its own screen and the app saves it to the gallery under LG Remote. The TV refuses this while copy protection is active - a film from a streaming app usually comes out black.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="44"/>
        <source>Free tile</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="45"/>
        <source>An empty tile. Tap it to pick an app or an input; a long press on any tile reassigns it.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="47"/>
        <source>Devices</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="48"/>
        <source>green - on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="49"/>
        <source>The TV says so itself: it is running and can be operated. Only the TV the app is connected to can say this.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="50"/>
        <source>orange - standby or reachable</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="51"/>
        <source>The TV answers on port 3001, but it is not running: network standby. Answering is not the same as being awake, which is why this is not green. For a TV the app is not connected to, the state cannot be told apart - it then only says reachable.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="52"/>
        <source>red - off</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="53"/>
        <source>No answer at all: disconnected from the mains, or network standby switched off in the TV settings. It stays in the list - the power key sends the wake-up signal, which needs the MAC address.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="54"/>
        <source>tap and hold</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="55"/>
        <source>A tap switches to the device and opens its system data - there you can see what state it is in. Holding the entry opens the menu: edit, release the pairing, forget the device. Its first line is deliberately empty so that letting go does nothing.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="56"/>
        <source>paired</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="57"/>
        <source>A pairing key for this TV is stored. Switching devices then needs no new confirmation on the screen.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="59"/>
        <source>Words</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="60"/>
        <source>ARC</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="61"/>
        <source>The sound runs over the HDMI return channel to an external device. The TV then only counts steps and never learns the real volume - that is why a number would be misleading and ARC is shown instead.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="62"/>
        <source>SSAP</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="63"/>
        <source>LG&apos;s own protocol on port 3001, the same one the official remote app uses. Encrypted, with the self-signed certificate of the TV.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="64"/>
        <source>Wake-on-LAN</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="65"/>
        <source>A broadcast packet that wakes the TV. It is addressed by MAC, not by IP - without the MAC address there is no switching on. The TV only names it while connected; it can also be typed in under Devices.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="76"/>
        <source>Glossary</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/GlossaryPage.qml" line="84"/>
        <source>What the symbols on the pages mean.</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>LgTv</name>
    <message>
        <location filename="../src/lgtv.cpp" line="89"/>
        <source>external speaker</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="90"/>
        <source>optical</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="91"/>
        <source>TV speaker</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="92"/>
        <source>Bluetooth soundbar</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="94"/>
        <source>TV speaker + external</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="95"/>
        <location filename="../src/lgtv.cpp" line="252"/>
        <source>unknown</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="105"/>
        <location filename="../src/lgtv.cpp" line="459"/>
        <source>disconnected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="125"/>
        <location filename="../src/lgtv.cpp" line="187"/>
        <location filename="../src/lgtv.cpp" line="492"/>
        <location filename="../src/lgtv.cpp" line="527"/>
        <source>Connection</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="125"/>
        <source>no answer during the TLS handshake</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="127"/>
        <source>no answer while connecting</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="176"/>
        <source>Certificate</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="177"/>
        <source>the TV shows a different certificate than the one remembered - reset the pairing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="179"/>
        <source>Certificate does not match - reset the pairing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="188"/>
        <location filename="../src/lgtv.cpp" line="624"/>
        <location filename="../src/lgtv.cpp" line="755"/>
        <source>Error: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="213"/>
        <source>not connected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="243"/>
        <source>no answer</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="269"/>
        <source>SSL in the Qt build: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="269"/>
        <location filename="../src/lgtv.cpp" line="1125"/>
        <location filename="../src/lgtv.cpp" line="1127"/>
        <source>yes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="269"/>
        <source>NO</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="270"/>
        <source>SSL library: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="271"/>
        <source>Target: wss://%1:3001</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="273"/>
        <source>Certificate: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="275"/>
        <source>Last rejected request: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="422"/>
        <location filename="../src/lgtv.cpp" line="556"/>
        <source>connecting ...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="433"/>
        <source>no device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="492"/>
        <location filename="../src/lgtv.cpp" line="493"/>
        <source>connection lost</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="528"/>
        <source>no sign of life within 8 s - the connection counts as dead</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="529"/>
        <source>no answer from the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="596"/>
        <location filename="../src/lgtv.cpp" line="843"/>
        <location filename="../src/lgtv.cpp" line="849"/>
        <source>Key channel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="597"/>
        <source>the TV does not hand out the address for the key channel - arrow keys, OK and Back stay locked</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="599"/>
        <location filename="../src/lgtv.cpp" line="852"/>
        <source>key channel stays closed</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="621"/>
        <location filename="../src/lgtv.cpp" line="754"/>
        <source>Sign-on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="622"/>
        <source>the built-in handshake is unreadable - pairing is impossible</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="637"/>
        <source>waiting for confirmation on the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="638"/>
        <source>signing in ...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="664"/>
        <source>connected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="701"/>
        <location filename="../src/lgtv.cpp" line="784"/>
        <source>power state</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="702"/>
        <source>the TV does not state whether it is running - the device list cannot tell on from standby</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="776"/>
        <source>volume</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="777"/>
        <source>key channel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="778"/>
        <source>app list</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="779"/>
        <source>input list</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="780"/>
        <source>system data</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="781"/>
        <source>network data (MAC address)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="782"/>
        <source>sound settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="783"/>
        <source>channel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="785"/>
        <source>remote keyboard</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="786"/>
        <source>text entry</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="787"/>
        <source>app state</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="788"/>
        <source>sign of life</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="789"/>
        <source>screenshot</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="792"/>
        <source>command</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="814"/>
        <source>Command not sent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="815"/>
        <source>not signed on to the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="844"/>
        <source>the TV answered without an address for the key channel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="850"/>
        <source>the TV names an address outside itself for the key channel - not opened</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="907"/>
        <location filename="../src/lgtv.cpp" line="932"/>
        <source>%1 entries name their icon outside the TV - icons ignored</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="941"/>
        <location filename="../src/lgtv.cpp" line="1205"/>
        <source>Text entry</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="941"/>
        <source>the TV rejected the text</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="943"/>
        <source>insertText: accepted</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="944"/>
        <source>insertText rejected: %1</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="994"/>
        <location filename="../src/lgtv.cpp" line="999"/>
        <source>Screenshot</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="995"/>
        <source>the TV took the order but names no image</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="996"/>
        <location filename="../src/lgtv.cpp" line="1002"/>
        <source>no screenshot from the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1000"/>
        <source>the TV names the image somewhere other than on itself - not fetched</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1034"/>
        <source>Model</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1035"/>
        <source>Serial number</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1141"/>
        <source>Key</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1141"/>
        <source>key channel not open - keystroke discarded</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1179"/>
        <source>Pointer</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1179"/>
        <source>key channel not open - click discarded</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1206"/>
        <source>no input field focused on the TV - the text may be discarded</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1207"/>
        <source>%1 characters</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1466"/>
        <source>asked three times without success - enter the MAC by hand under Connected devices</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1053"/>
        <source>MAC wired</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1053"/>
        <source>MAC Wi-Fi</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1054"/>
        <source>MAC direct link</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1066"/>
        <source> - IP</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1106"/>
        <location filename="../src/lgtv.cpp" line="1465"/>
        <source>MAC address</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1107"/>
        <source>the TV answered without a MAC address - no wake-on-LAN possible</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1117"/>
        <source>Sound output</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1118"/>
        <source>Volume</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1119"/>
        <source>%1 of %2</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1125"/>
        <location filename="../src/lgtv.cpp" line="1127"/>
        <source>no</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1124"/>
        <source>External control</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1122"/>
        <source>Mute</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1123"/>
        <source>on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1123"/>
        <source>off</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1126"/>
        <source>Volume adjustable</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/lgtv.cpp" line="1394"/>
        <source>YouTube: %1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>MainMenu</name>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="15"/>
        <source>Connected devices</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="20"/>
        <source>Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="31"/>
        <source>Apps and inputs</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="25"/>
        <source>System data</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/MainMenu.qml" line="11"/>
        <source>About</source>
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
        <location filename="../qml/pages/PanelMain.qml" line="137"/>
        <source>switched off</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="154"/>
        <source>wake-up signal sent</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="156"/>
        <source>no MAC address stored - see the error log</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="157"/>
        <source>invalid MAC address</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="198"/>
        <source>Back</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="202"/>
        <source>Info</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="223"/>
        <source>Input</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="229"/>
        <source>Settings</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="245"/>
        <source>Sound</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelMain.qml" line="263"/>
        <source>Channel</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>PanelPad</name>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="56"/>
        <source>Show keyboard</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="77"/>
        <source>◀   swipe here to change page   ▶</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="117"/>
        <source>not connected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="293"/>
        <source>no text field on the TV - use the magnifier for YouTube</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="330"/>
        <source>opening keyboard on the TV ...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="332"/>
        <source>text to the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/PanelPad.qml" line="333"/>
        <source>no TV - text stays here</source>
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
        <location filename="../qml/pages/SettingsPage.qml" line="160"/>
        <source>not stored</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="93"/>
        <source>Wake-on-LAN has to be enabled on the TV: Settings → General → External devices → Turn on via mobile device.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="98"/>
        <source>Match the volume</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="106"/>
        <source>With the sound on an external device over ARC, the TV keeps a counter of its own that has nothing to do with the real level - the amplifier never reports back. Enter what the device shows and the display follows along.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="117"/>
        <source>Level on the audio device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="128"/>
        <source>Set</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="143"/>
        <source>Pairing</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="152"/>
        <source>Paired. The TV no longer asks.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="153"/>
        <source>Not paired yet. Connecting brings up a prompt on the TV.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="157"/>
        <source>Certificate</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="171"/>
        <source>A pairing belongs to one television. Releasing it is therefore done in the device list: hold the entry, then Reset pairing.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="176"/>
        <source>Try a key code</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="184"/>
        <source>The TV accepts about 450 key names and silently drops invalid ones. Try one here without rebuilding the app - QMENU, MYAPPS, RECENT, LIST, SIMPLINK, GUIDE or SCREEN_REMOTE for instance.</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="195"/>
        <source>e.g. INPUT</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="196"/>
        <source>Key name</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="206"/>
        <source>Send</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="219"/>
        <source>State</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="221"/>
        <source>Connection</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="221"/>
        <source>open</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="221"/>
        <source>closed</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="222"/>
        <source>Paired</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="222"/>
        <source>yes</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="222"/>
        <source>no</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="223"/>
        <source>Key channel</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="223"/>
        <source>ready</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="224"/>
        <source>not ready</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="225"/>
        <source>Message</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="226"/>
        <source>Text field on the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="228"/>
        <source>ready (%1, %2 characters)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="230"/>
        <source>no field open</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SettingsPage.qml" line="232"/>
        <source>Diagnostics</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>SystemPage</name>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="18"/>
        <location filename="../qml/pages/SystemPage.qml" line="86"/>
        <location filename="../qml/pages/SystemPage.qml" line="92"/>
        <location filename="../qml/pages/SystemPage.qml" line="105"/>
        <location filename="../qml/pages/SystemPage.qml" line="108"/>
        <source>Device</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="62"/>
        <source>not stated</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="63"/>
        <source>on</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="64"/>
        <source>on, screen dark</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="66"/>
        <source>standby</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="83"/>
        <source>Address</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="86"/>
        <source>State</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="87"/>
        <source>not connected</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="18"/>
        <location filename="../qml/pages/SystemPage.qml" line="83"/>
        <location filename="../qml/pages/SystemPage.qml" line="110"/>
        <location filename="../qml/pages/SystemPage.qml" line="113"/>
        <source>Network</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="19"/>
        <location filename="../qml/pages/SystemPage.qml" line="111"/>
        <source>Sound and ARC</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="20"/>
        <location filename="../qml/pages/SystemPage.qml" line="109"/>
        <location filename="../qml/pages/SystemPage.qml" line="117"/>
        <source>Inputs</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="19"/>
        <location filename="../qml/pages/SystemPage.qml" line="123"/>
        <source>Open ports</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="87"/>
        <source>connecting ...</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="92"/>
        <location filename="../qml/pages/SystemPage.qml" line="105"/>
        <source>Power state</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="109"/>
        <source>Tuner</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="113"/>
        <source>Encryption</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="124"/>
        <source>open</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="135"/>
        <source>System data</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="139"/>
        <source>Error log (%1)</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="140"/>
        <source>Error log - empty</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/pages/SystemPage.qml" line="144"/>
        <source>Reload</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>TvIcons</name>
    <message>
        <location filename="../src/tvicons.cpp" line="73"/>
        <location filename="../src/tvicons.cpp" line="82"/>
        <location filename="../src/tvicons.cpp" line="109"/>
        <location filename="../src/tvicons.cpp" line="118"/>
        <location filename="../src/tvicons.cpp" line="144"/>
        <source>Icon</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="119"/>
        <source>no certificate remembered yet - connect to the TV once, then the icons will load</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="144"/>
        <source>not fetched from the TV after three tries</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="83"/>
        <source>the TV shows a different certificate than the one remembered</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="74"/>
        <source>TLS error without a certificate to check</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="198"/>
        <location filename="../src/tvicons.cpp" line="222"/>
        <location filename="../src/tvicons.cpp" line="233"/>
        <source>Screenshot</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="222"/>
        <source>not fetched from the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="200"/>
        <location filename="../src/tvicons.cpp" line="228"/>
        <source>Screenshot not fetched</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="110"/>
        <location filename="../src/tvicons.cpp" line="199"/>
        <source>this address does not lead to the TV - not fetched</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="233"/>
        <source>could not be written to the gallery</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="235"/>
        <source>Screenshot not saved</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="257"/>
        <location filename="../src/tvicons.cpp" line="262"/>
        <location filename="../src/tvicons.cpp" line="276"/>
        <location filename="../src/tvicons.cpp" line="281"/>
        <source>Tile</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="258"/>
        <source>icon not fetched: this address does not lead to the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="263"/>
        <source>icon not fetched: no certificate of the TV remembered yet</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="276"/>
        <source>icon not fetched from the TV</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/tvicons.cpp" line="281"/>
        <source>icon could not be cached</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>Wol</name>
    <message>
        <location filename="../src/wol.cpp" line="20"/>
        <location filename="../src/wol.cpp" line="37"/>
        <location filename="../src/wol.cpp" line="47"/>
        <location filename="../src/wol.cpp" line="57"/>
        <location filename="../src/wol.cpp" line="99"/>
        <source>Wake-on-LAN</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/wol.cpp" line="21"/>
        <location filename="../src/wol.cpp" line="38"/>
        <source>no MAC address stored for this device - the TV only names it while connected, or enter it by hand</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/wol.cpp" line="48"/>
        <source>the stored MAC address does not have twelve hex digits</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/wol.cpp" line="58"/>
        <source>the stored MAC address contains characters that are not hex digits</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../src/wol.cpp" line="100"/>
        <source>the magic packet could not be sent - no network on the phone?</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>harbour-lgremote</name>
    <message>
        <location filename="../qml/harbour-lgremote.qml" line="85"/>
        <source>Devices</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/harbour-lgremote.qml" line="85"/>
        <source>the stored device list is unreadable</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/harbour-lgremote.qml" line="92"/>
        <source>Television</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/harbour-lgremote.qml" line="125"/>
        <source>Tiles</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/harbour-lgremote.qml" line="125"/>
        <source>the stored tiles are unreadable</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/harbour-lgremote.qml" line="153"/>
        <source>Tile</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/harbour-lgremote.qml" line="153"/>
        <source>the TV names no icon for this entry</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="../qml/harbour-lgremote.qml" line="282"/>
        <source>Screenshot saved: %1</source>
        <translation type="unfinished"></translation>
    </message>
</context>
</TS>
