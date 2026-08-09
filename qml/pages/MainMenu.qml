import QtQuick 2.0
import Sailfish.Silica 1.0

/* Das Menue muss in einem scrollbaren Element sitzen. Die Seite selbst ist
   keins - deshalb liegt es hier und wird in jedes Panel eingehaengt. */
PullDownMenu {
    property var tv
    property var window

    MenuItem {
        text: "Einstellungen"
        onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"),
                                  { tv: tv, window: window })
    }
    MenuItem {
        text: "Geräte"
        onClicked: pageStack.push(Qt.resolvedUrl("DevicesPage.qml"),
                                  { tv: tv, window: window })
    }
    MenuItem {
        text: "Apps und Eingänge"
        enabled: tv.registered
        onClicked: pageStack.push(Qt.resolvedUrl("AppsPage.qml"), { tv: tv })
    }
    MenuItem {
        text: "Systemdaten"
        enabled: tv.registered
        onClicked: pageStack.push(Qt.resolvedUrl("SystemPage.qml"),
                                  { tv: tv, window: window })
    }
    MenuItem {
        text: "Über"
        onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
    }
    MenuItem {
        text: tv.linkUp ? "Trennen" : "Verbinden"
        onClicked: tv.linkUp ? tv.disconnectTv() : tv.connectTv()
    }
}
