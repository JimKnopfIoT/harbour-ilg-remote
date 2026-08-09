TARGET = harbour-lgremote

CONFIG += sailfishapp
QT += network websockets

SOURCES += \
    src/harbour-lgremote.cpp \
    src/discovery.cpp \
    src/lgtv.cpp \
    src/portscan.cpp \
    src/wol.cpp

HEADERS += \
    src/discovery.h \
    src/lgtv.h \
    src/portscan.h \
    src/wol.h

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
    qml/pages/AppsPage.qml \
    qml/pages/DevicesPage.qml \
    qml/pages/DeviceEditPage.qml \
    qml/pages/SettingsPage.qml \
    qml/cover/CoverPage.qml \
    qml/images/tv.png \
    qml/images/youtube.png \
    qml/images/jellyfin.png \
    qml/images/balkon.png \
    rpm/harbour-lgremote.spec \
    harbour-lgremote.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172
