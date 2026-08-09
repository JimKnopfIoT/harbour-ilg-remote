# Third-party notices

This app is original work under the MIT license. It contains no third-party
source code, but it builds on the following external work.

## Runtime / build dependencies

Dynamically linked platform libraries, each under its own license — linking
against them does not change this app's MIT license:

* **Qt 5** (Core, Qml, Quick, Network, WebSockets) — LGPLv3 / commercial.
* **Sailfish Silica** and `libsailfishapp` — the SailfishOS UI platform.
* **nemo-qml-plugin-configuration-qt5** — settings storage.

## Protocols (no code copied)

* **LG webOS SSAP** — the app talks to the TV over LG's SSAP WebSocket
  interface (register/pairing handshake, `ssap://…` requests). The protocol is
  publicly documented by the community; no third-party code is included.
* **Wake-on-LAN** (magic packet) and **SSDP** discovery are standard,
  self-implemented.

## Launcher icons and app ids

The app-launch buttons use **neutral placeholder icons** and **example webOS
app ids** (`com.webos.app.livetv`, `youtube.leanback.v4`, `org.jellyfin.webos`,
`com.example.dashboard`). No third-party brand logos are shipped; edit the ids
and icons to match the apps on your own TV.

## Trademarks

LG and webOS are trademarks of LG Electronics. YouTube is a trademark of Google.
Jellyfin is a trademark of the Jellyfin project. All names are used only to
identify the apps you may launch; this project is not affiliated with or
endorsed by any of them.
