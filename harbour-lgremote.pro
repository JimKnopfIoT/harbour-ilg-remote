TARGET = harbour-lgremote

CONFIG += sailfishapp sailfishapp_i18n
QT += network websockets

SOURCES += \
    src/harbour-lgremote.cpp \
    src/discovery.cpp \
    src/errorlog.cpp \
    src/lgtv.cpp \
    src/portscan.cpp \
    src/tvicons.cpp \
    src/wol.cpp

HEADERS += \
    src/discovery.h \
    src/errorlog.h \
    src/lgtv.h \
    src/portscan.h \
    src/tvicons.h \
    src/wol.h

TRANSLATIONS += translations/harbour-lgremote-de.ts

lupdate_only {
    SOURCES += qml/*.qml qml/cover/*.qml qml/pages/*.qml
}

DISTFILES += \
    qml/harbour-lgremote.qml \
    qml/pages/RemotePage.qml \
    qml/pages/RemoteKey.qml \
    qml/pages/MainMenu.qml \
    qml/pages/IconKey.qml \
    qml/pages/PanelMain.qml \
    qml/pages/PanelNumbers.qml \
    qml/pages/PanelPad.qml \
    qml/pages/SystemPage.qml \
    qml/pages/AboutPage.qml \
    qml/pages/GlossaryPage.qml \
    qml/pages/ErrorLogPage.qml \
    qml/pages/AppsPage.qml \
    qml/pages/DevicesPage.qml \
    qml/pages/DeviceEditPage.qml \
    qml/pages/SettingsPage.qml \
    qml/cover/CoverPage.qml \
    qml/images/shutter.png \
    qml/images/vol-up.png \
    qml/images/vol-down.png \
    qml/images/tv.png \
    qml/images/youtube.png \
    qml/images/jellyfin.png \
    qml/images/power.png \
    qml/images/speaker.png \
    qml/images/mute.png \
    rpm/harbour-lgremote.spec \
    harbour-lgremote.desktop \
    translations/harbour-lgremote-de.ts

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172
