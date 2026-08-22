import QtQuick 2.0
import Sailfish.Silica 1.0

/* Das Menue muss in einem scrollbaren Element sitzen. Die Seite selbst ist
   keins - deshalb liegt es hier und wird in jedes Panel eingehaengt. */
PullDownMenu {
    property var tv
    property var window

    MenuItem {
        text: qsTr("Settings")
        onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"),
                                  { tv: tv, window: window })
    }
    MenuItem {
        text: qsTr("Devices")
        onClicked: pageStack.push(Qt.resolvedUrl("DevicesPage.qml"),
                                  { tv: tv, window: window })
    }
    MenuItem {
        text: qsTr("Apps and inputs")
        enabled: tv.registered
        onClicked: pageStack.push(Qt.resolvedUrl("AppsPage.qml"), { tv: tv })
    }
    MenuItem {
        text: qsTr("Screenshot of the TV")
        enabled: tv.registered
        onClicked: tv.captureScreen()
    }
    MenuItem {
        text: qsTr("System data")
        enabled: tv.registered
        onClicked: pageStack.push(Qt.resolvedUrl("SystemPage.qml"),
                                  { tv: tv, window: window })
    }
    MenuItem {
        text: qsTr("About")
        onClicked: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
    }
    MenuItem {
        text: tv.linkUp ? qsTr("Disconnect") : qsTr("Connect")
        onClicked: tv.linkUp ? tv.disconnectTv() : tv.connectTv()
    }
}
