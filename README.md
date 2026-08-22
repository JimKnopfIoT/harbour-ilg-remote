# iLG remote

A native **SailfishOS** remote control for **LG webOS** televisions.

It speaks the LG **SSAP** WebSocket protocol (over TLS) directly — d-pad,
volume, channels, inputs, media keys, a pointer/touchpad, a number pad and app
launching — and powers the TV on with **Wake-on-LAN**. TVs are found by SSDP
discovery, with a fallback scan of the local subnet, and several TVs can be
stored and switched between.

> Package id: `harbour-lgremote`. Built and used on a Sony Xperia 10 III
> (SailfishOS 5.x). English and German user interface.

|  |  |  |
|---|---|---|
| ![Remote](docs/screenshots/1_remote.png) | ![Number pad](docs/screenshots/2_numbers.png) | ![Pointer and keyboard](docs/screenshots/3_pointer.png) |

*(The three carousel pages — remote, number pad, and the pointer page with the
keyboard: the surface moves the cursor, the text row sends text to a field on
the TV or searches YouTube. On the number pad, the six quick-launch tiles: five
assignable ones — brand logos replaced by neutral placeholders here — and the
fixed shutter tile.)*

![Screenshot taken from the TV](docs/screenshots/4_tv-capture.jpg)

*(What the shutter tile brings back: the TV's current picture at 960×540,
stored in the gallery. Example content.)*

## Features

* Pairing with the TV's prompt; the per-device client key is stored locally.
* Directional pad, OK/Back/Home, volume and channel, input switching.
* A pointer / touchpad panel (magic-remote style) and an on-screen keyboard bridge.
* Number pad and a 2×3 quick-launch block: five tiles you assign yourself
  (press and hold one to pick an app or input), plus a fixed **screenshot**
  tile that stores the TV's current picture in the gallery.
* Apps and inputs listed with the icons the TV serves, sorted by name.
* **Wake-on-LAN** power-on via a magic packet.
* A **self-healing connection**: a heartbeat spots a link that died silently
  (phone asleep, TV switched off), and the app reconnects on its own with a
  growing delay. Deliberate disconnects stay disconnected.
* **Discovery** by SSDP — repeated on every network interface, and if nothing
  answers, the local subnet is probed on port 3001.
* **Certificate pinning**: the TV's self-signed certificate is remembered on the
  first connection and checked from then on.
* Multiple devices — add, edit and switch between TVs.
* A cover with play/pause and connection state.

## Building

Uses the SailfishOS Platform SDK (`mb2`):

```sh
mb2 -t <target> build
```

Requires `qt5-qtwebsockets`, `nemo-qml-plugin-configuration-qt5` and the usual
Sailfish/Qt5 build dependencies (see `rpm/harbour-lgremote.spec`).

## Status

**Proof of concept / work in progress.** A hobby project, shared **as is** with
**no warranty** of any kind (see [LICENSE](LICENSE)). It may be incomplete,
rough around the edges, or change without notice — use it at your own risk. It
talks only to **your own** TV on your own network.

## License

MIT — see [LICENSE](LICENSE) and [THIRD-PARTY-NOTICES.md](THIRD-PARTY-NOTICES.md).
