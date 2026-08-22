import QtQuick 2.0
import Sailfish.Silica 1.0

/* Ein Geraet anlegen oder aendern. index = -1 legt ein neues an. */
Page {
    id: page

    property var window
    property int index: -1

    readonly property var dev: (index >= 0 && index < window.devices.length)
                               ? window.devices[index] : null

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: col.height

        Column {
            id: col
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { title: page.dev ? qsTr("Edit device") : qsTr("New device") }

            TextField {
                id: nameField
                width: parent.width
                label: qsTr("Name")
                placeholderText: qsTr("Living room")
                text: page.dev ? page.dev.name : ""
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: hostField.focus = true
            }

            TextField {
                id: hostField
                width: parent.width
                label: qsTr("Address")
                placeholderText: "192.168.1.100"
                text: page.dev ? page.dev.host : ""
                inputMethodHints: Qt.ImhUrlCharactersOnly | Qt.ImhNoAutoUppercase
                EnterKey.iconSource: "image://theme/icon-m-enter-next"
                EnterKey.onClicked: macField.focus = true
            }

            TextField {
                id: macField
                width: parent.width
                label: qsTr("MAC address (for Wake-on-LAN)")
                placeholderText: "AA:BB:CC:DD:EE:FF"
                text: page.dev ? page.dev.mac : ""
                inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
                EnterKey.iconSource: "image://theme/icon-m-enter-close"
                EnterKey.onClicked: focus = false
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("The MAC address is shown on the TV under Settings → General → About this TV. Without it everything works except powering on.")
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: page.dev ? qsTr("Apply") : qsTr("Add and switch")
                enabled: hostField.text.trim().length > 0
                onClicked: {
                    var name = nameField.text.trim().length > 0
                               ? nameField.text.trim() : hostField.text.trim()
                    if (page.dev) {
                        page.window.updateDevice(page.index, name,
                                                 hostField.text.trim(), macField.text.trim())
                    } else {
                        var i = page.window.addDevice(name, hostField.text.trim(),
                                                      macField.text.trim())
                        page.window.selectDevice(i)
                    }
                    pageStack.pop()
                }
            }
        }

        VerticalScrollDecorator { }
    }
}
