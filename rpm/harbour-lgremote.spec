Name:       harbour-lgremote
# Keep the build machine's name out of the RPM header.
%define _buildhost reproducible-builder
Summary:    Fernbedienung für LG webOS-Fernseher
Version:    1.1.3
Release:    1
License:    MIT
URL:        https://github.com/JimKnopfIoT/harbour-ilg-remote
Source0:    %{name}-%{version}.tar.bz2
Requires:   sailfishsilica-qt5 >= 0.10.9
Requires:   nemo-qml-plugin-configuration-qt5
Requires:   qt5-qtwebsockets
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5Network)
BuildRequires:  pkgconfig(Qt5WebSockets)
BuildRequires:  desktop-file-utils

%description
Steuert einen LG-Fernseher mit webOS über das SSAP-WebSocket-Protokoll:
Steuerkreuz, Lautstärke, Kanäle, Eingänge und Apps. Einschalten per
Wake-on-LAN.

%prep
%setup -q -n %{name}-%{version}

%build
# Nicht %qtc_qmake5 verwenden – das ist ein Qt-Creator-Makro und in der
# reinen mb2-Umgebung nicht definiert.
%qmake5
make %{?_smp_mflags}

%install
%qmake5_install
desktop-file-install --delete-original \
  --dir %{buildroot}%{_datadir}/applications \
  %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png

%changelog
* Sat Aug 22 2026 harbour-lgremote contributors 1.1.2-1
- The TV certificate is picked out of the chain properly. The TV sends its own
  certificate together with the intermediate that issued it, and the order of
  the errors is not ours to choose - taking the first one compared the
  intermediate against the pinned fingerprint and locked the app out entirely.
- Reconnect timing matched to the TV: it accepts at most six connections at a
  time and reclaims abandoned attempts only slowly, so retrying quickly locked
  the app out of its own TV. Attempts are now spaced further apart.
- The key channel is requested again when it drops. Until now a single drop
  left the D-pad, the arrow keys and the number pad greyed out until a restart.
- The YouTube tile works again. Recent firmware answers system.launcher/
  getAppState with "403 access denied" for every app, and the failed query left
  the pending launch waiting forever, so nothing happened at all.
- Text field: separate buttons for text and for search. Without a text field
  reported by the TV, no ENTER is sent any more - in apps that draw their own
  keyboard, YouTube among them, it only pressed the highlighted key.
- The keyboard stays open on the pointer page and the pointer area keeps its
  size instead of growing and shrinking.
- System data is grouped in fixed sections regardless of the order the TV
  answers in: device, network, ports, sound, inputs. New: the negotiated
  encryption. The tuner sits with the inputs, and mute reads on/off since it
  is a state, not a capability.
- Pull-down menu reordered; connect and disconnect moved to the device list,
  which now also shows model, serial number and MAC address.
- Portrait only - no page rotates any more.

* Sat Aug 22 2026 harbour-lgremote contributors 1.1.1-1
- Wake-on-LAN works for devices added by network discovery: the search can
  only report an IP address, so the MAC field stayed empty and the power
  button did nothing. The app now asks the connected TV for the MAC of the
  interface it is reachable on and fills the field in. An address entered by
  hand is left alone.
- Text is no longer preceded by a blind ENTER. When the TV reports no text
  field at all, that key press just hit whatever was highlighted - a key of
  the on-screen keyboard, for instance. The app now says so instead.

* Sat Aug 22 2026 harbour-lgremote contributors 1.1.0-1
- User interface in English, with a German translation.
- Quick launch on the number pad is now a 2x3 block: five freely assignable
  tiles (press and hold to assign an app or input) and a fixed sixth tile that
  takes a screenshot of the TV and stores it in the gallery.
- Apps and inputs are listed with the icons the TV serves, sorted by name -
  the TV hands them out unsorted, which buried Live TV near the end.
- More reliable discovery: the SSDP search is repeated on every network
  interface, and if nothing answers the local subnet is probed on port 3001.
- The TV certificate is remembered on the first connection and checked from
  then on; a mismatch stops the connection instead of being ignored. The same
  check covers the icon and screenshot downloads.
- The TLS version is no longer pinned to 1.2; the TV takes 1.2 and 1.3 alike.
  Downloads from the TV are retried, because it refuses a handshake now and
  then - measured at roughly one in five.
- A Sailjail profile (Internet, Pictures) instead of no declaration at all.
- Pointer movements are sent in batches, and without a configured device the
  app no longer retries in a loop.
- Apps and inputs are requested independently, so one rejected query no
  longer leaves the list empty.

* Tue Aug 18 2026 harbour-lgremote contributors 1.0.1-1
- Release build with a neutral build host in the package header (the 1.0.0
  packages carried the build machine's name) and the first version offered on
  OpenRepos. No change to the app.
