import QtQuick 2.0
import Sailfish.Silica 1.0

/* Das Menue muss in einem scrollbaren Element sitzen. Die Seite selbst ist
   keins - deshalb liegt es hier und wird in jedes Panel eingehaengt. */
PullDownMenu {
    property var tv
    property var window

    MenuItem {
        text: qsTr("About")
        onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
    }
    MenuItem {
        text: qsTr("Connected devices")
        onClicked: pageStack.push(Qt.resolvedUrl("DevicesPage.qml"),
                                  { tv: tv, window: window })
    }
    MenuItem {
        text: qsTr("Settings")
        onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"),
                                  { tv: tv, window: window })
    }
    MenuItem {
        text: qsTr("System data")
        enabled: tv.registered
        onClicked: pageStack.push(Qt.resolvedUrl("SystemPage.qml"),
                                  { tv: tv, window: window })
    }
    MenuItem {
        text: qsTr("Apps and inputs")
        enabled: tv.registered
        onClicked: pageStack.push(Qt.resolvedUrl("AppsPage.qml"), { tv: tv })
    }
}
