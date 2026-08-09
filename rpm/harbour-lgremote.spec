Name:       harbour-lgremote
Summary:    Fernbedienung für LG webOS-Fernseher
Version:    1.0.0
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
