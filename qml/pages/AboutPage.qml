import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    allowedOrientations: Orientation.Portrait

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: col.height + Theme.paddingLarge

        Column {
            id: col
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { title: qsTr("About") }

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                source: "image://theme/icon-launcher-default"
                sourceSize.width: Theme.iconSizeLarge
                sourceSize.height: Theme.iconSizeLarge
                visible: status === Image.Ready
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("LG remote")
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Version %1").arg("1.1.6")
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.secondaryColor
            }

            Item { width: 1; height: Theme.paddingLarge }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Glossary")
                onClicked: pageStack.push(Qt.resolvedUrl("GlossaryPage.qml"))
            }

            /* Der Zaehler steht im Knopf: so sieht man, ob es etwas zu lesen
               gibt, ohne die Seite zu oeffnen. Leer ist der Normalfall. */
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: errorLog.count > 0 ? qsTr("Error log (%1)").arg(errorLog.count)
                                         : qsTr("Error log - empty")
                onClicked: pageStack.push(Qt.resolvedUrl("ErrorLogPage.qml"))
            }

            Item { width: 1; height: Theme.paddingMedium }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("Controls LG televisions running webOS over the network - no infrared, no line of sight. It speaks LG's own SSAP protocol, the same one the official remote app uses.")
            }

            SectionHeader { text: qsTr("Technical notes") }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("The connection uses <b>wss on port 3001</b>. The unencrypted port 3000 that older remote apps use is refused by current firmware.\n\nThe TV identifies itself with a self-signed certificate; its fingerprint is remembered on the first connection and checked from then on. The TLS version is left to the library; the TV takes 1.2 as well as 1.3, but now and then it drops a handshake without answering - the app simply tries again.\n\nThe keys run over a second channel whose address the TV only hands out on request. Powering on works via Wake-on-LAN and needs the MAC address.")
                textFormat: Text.StyledText
            }

            SectionHeader { text: qsTr("Origin") }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("Written from scratch. The idea for the touchpad and text entry comes from harbour-lgremote-webos by CODeRUS and Mazhoon (WTFPL); its code could not be reused because it relies on port 3000 and the QML WebSocket component.")
            }

            Item { width: 1; height: Theme.paddingLarge }
        }

        VerticalScrollDecorator { }
    }
}
