import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    allowedOrientations: Orientation.All

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: col.height + Theme.paddingLarge

        Column {
            id: col
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { title: "Über" }

            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                source: "image://theme/icon-launcher-default"
                sourceSize.width: Theme.iconSizeLarge
                sourceSize.height: Theme.iconSizeLarge
                visible: status === Image.Ready
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "LG Fernbedienung"
                font.pixelSize: Theme.fontSizeLarge
                color: Theme.highlightColor
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Version 1.0.0"
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.secondaryColor
            }

            Item { width: 1; height: Theme.paddingLarge }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
                text: "Steuert LG-Fernseher mit webOS über das Netzwerk – ohne Infrarot, " +
                      "ohne Sichtverbindung. Verwendet wird LGs eigenes SSAP-Protokoll, " +
                      "dasselbe, das auch die offizielle Fernbedienungs-App spricht."
            }

            SectionHeader { text: "Technische Hinweise" }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: "Die Verbindung läuft über <b>wss auf Port 3001</b>. Das " +
                      "unverschlüsselte Port 3000, das ältere Fernbedienungs-Apps " +
                      "verwenden, wird von aktueller Firmware abgewiesen.\n\n" +
                      "Der Fernseher weist sich mit einem selbstsignierten Zertifikat " +
                      "aus, und die Protokollversion wird fest auf TLS 1.2 gesetzt – " +
                      "der Fernseher bevorzugt TLS 1.3, das Qt 5.6 noch nicht kennt.\n\n" +
                      "Die Tasten laufen über einen zweiten Kanal, dessen Adresse der " +
                      "Fernseher erst auf Anfrage herausgibt. Einschalten geschieht per " +
                      "Wake-on-LAN, dafür wird die MAC-Adresse benötigt."
                textFormat: Text.StyledText
            }

            SectionHeader { text: "Herkunft" }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: "Eigenentwicklung. Die Idee zu Touchpad und Texteingabe stammt " +
                      "aus harbour-lgremote-webos von CODeRUS und Mazhoon (WTFPL); " +
                      "dessen Code selbst ließ sich nicht verwenden, weil er auf " +
                      "Port 3000 und die QML-WebSocket-Komponente setzt."
            }

            Item { width: 1; height: Theme.paddingLarge }
        }

        VerticalScrollDecorator { }
    }
}
