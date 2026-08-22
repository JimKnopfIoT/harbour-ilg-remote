import QtQuick 2.0
import Sailfish.Silica 1.0

/* Die Kachel ist ein eigenes Fenster und sieht die Seite nicht - also eine
   Skizze, die den Zustand ueber die Farbe des Ein/Aus-Zeichens fuehrt. */
CoverBackground {
    id: cover

    property var tv

    readonly property color stateColor: tv && tv.registered ? "#4caf50"
                                      : tv && tv.linkUp ? "#ff9800" : "#e53935"

    Item {
        anchors.fill: parent
        opacity: 0.30

        // Ein/Aus oben links
        Rectangle {
            id: pw
            x: parent.width * 0.10
            y: parent.height * 0.07
            width: parent.width * 0.22
            height: width
            radius: width / 2
            color: "transparent"
            border.width: 2
            border.color: cover.stateColor

            Label {
                anchors.centerIn: parent
                text: "⏻"
                font.pixelSize: parent.width * 0.55
                color: cover.stateColor
            }
        }

        // Steuerkreuz
        Grid {
            anchors.horizontalCenter: parent.horizontalCenter
            y: parent.height * 0.32
            columns: 3
            spacing: parent.width * 0.05

            Repeater {
                model: 9
                Rectangle {
                    width: cover.width * 0.16
                    height: width
                    radius: index === 4 ? width / 2 : width * 0.2
                    visible: index % 2 === 1 || index === 4
                    color: Theme.rgba(Theme.primaryColor, index === 4 ? 0.35 : 0.2)
                }
            }
        }

        // Zwei Tastenreihen
        Repeater {
            model: 2
            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                y: cover.height * (0.62 + index * 0.13)
                spacing: cover.width * 0.05

                Repeater {
                    model: 3
                    Rectangle {
                        width: cover.width * 0.16
                        height: cover.height * 0.08
                        radius: width * 0.2
                        color: Theme.rgba(Theme.primaryColor, 0.18)
                    }
                }
            }
        }
    }

    // Deutlich lesbar bleibt nur, was zaehlt
    Label {
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: Theme.paddingLarge
        }
        text: tv && tv.registered
              ? (tv.volume >= 0 ? (tv.muted ? qsTr("muted") : "♪ " + tv.volume) : qsTr("connected"))
              : qsTr("disconnected")
        font.pixelSize: Theme.fontSizeSmall
        color: cover.stateColor
    }

    CoverActionList {
        enabled: tv && tv.registered
        CoverAction {
            iconSource: "image://theme/icon-cover-play"
            onTriggered: tv.volumeUp()
        }
        CoverAction {
            iconSource: "image://theme/icon-cover-pause"
            onTriggered: tv.volumeDown()
        }
    }
}
