import QtQuick 2.0
import Sailfish.Silica 1.0

/* Zweite Karussellseite: Zahlenblock mit vierstelliger Kanalanzeige. */
Item {
    id: panel

    property var tv
    property var window
    property string entry: ""

    Connections {
        target: tv
        onStateChanged: if (tv.registered) tv.refreshChannel()
    }

    Component.onCompleted: if (tv.registered) tv.refreshChannel()

    function push(d) {
        if (entry.length < 4) entry += d
        // Die Ziffer zusaetzlich direkt senden - so reagiert der Fernseher
        // sofort, wie bei der Originalfernbedienung
        tv.button(d)
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: height
        flickableDirection: Flickable.VerticalFlick

        MainMenu { tv: panel.tv; window: panel.window }

    Column {
        anchors.centerIn: parent
        spacing: Theme.paddingLarge

        // ---------- Anzeige ----------

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            width: Theme.itemSizeLarge * 3 + Theme.paddingLarge * 2
            horizontalAlignment: Text.AlignHCenter
            text: panel.tv.channel.length > 0 ? panel.tv.channel : " "
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.secondaryHighlightColor
        }

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            width: Theme.itemSizeLarge * 3 + Theme.paddingLarge * 2
            height: Theme.itemSizeLarge
            radius: Theme.paddingMedium
            color: Theme.rgba(Theme.primaryColor, 0.08)
            border.width: 1
            border.color: Theme.rgba(Theme.primaryColor, 0.22)

            Row {
                anchors.centerIn: parent
                spacing: Theme.paddingMedium
                Repeater {
                    model: 4
                    Label {
                        text: index < panel.entry.length ? panel.entry.charAt(index) : "–"
                        font.pixelSize: Theme.fontSizeHuge
                        font.family: "monospace"
                        color: index < panel.entry.length ? Theme.highlightColor
                                                          : Theme.rgba(Theme.primaryColor, 0.25)
                    }
                }
            }
        }

        // ---------- Zahlenblock ----------

        Grid {
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 3
            spacing: Theme.paddingLarge
            enabled: panel.tv.pointerReady
            opacity: panel.tv.pointerReady ? 1.0 : 0.3

            Repeater {
                model: ["1","2","3","4","5","6","7","8","9"]
                RemoteKey { text: modelData; onPressed: panel.push(modelData) }
            }

            // Abbruch links, Bestätigen unten rechts – dort sitzt auf jedem
            // Ziffernblock die Eingabetaste, dorthin geht der Finger von selbst
            IconKey {
                icon: "icon-m-clear"
                onPressed: panel.entry = ""
            }

            RemoteKey { text: "0"; onPressed: panel.push("0") }

            IconKey {
                icon: "icon-m-accept"
                onPressed: {
                    if (panel.entry.length > 0) {
                        panel.tv.openChannel(panel.entry)
                        panel.entry = ""
                    } else {
                        panel.tv.button("ENTER")
                    }
                }
            }
        }

        // ---------- Direktaufrufe ----------
        // Deutlich abgesetzt vom Ziffernblock, mit den Symbolen, die der
        // Fernseher selbst fuer diese Apps fuehrt.

        Item { width: 1; height: Theme.itemSizeSmall }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: Theme.paddingLarge
            enabled: panel.tv.registered
            opacity: panel.tv.registered ? 1.0 : 0.3

            Repeater {
                /* webOS application ids. These are examples - edit them to
                   match the apps installed on your own TV. */
                model: [
                    { "img": "tv.png",       "id": "com.webos.app.livetv",   "t": "TV" },
                    { "img": "youtube.png",  "id": "youtube.leanback.v4",    "t": "YouTube" },
                    { "img": "jellyfin.png", "id": "org.jellyfin.webos",     "t": "Jellyfin" },
                    { "img": "balkon.png",   "id": "com.example.dashboard",  "t": "Dashboard" }
                ]

                MouseArea {
                    width: Theme.itemSizeMedium
                    height: Theme.itemSizeMedium

                    Rectangle {
                        width: parent.width
                        height: parent.width
                        radius: Theme.paddingMedium
                        color: parent.pressed ? Theme.rgba(Theme.highlightBackgroundColor, 0.5)
                                              : "transparent"
                    }

                    Image {
                        anchors.centerIn: parent
                        width: parent.width - 2 * Theme.paddingSmall
                        height: width
                        fillMode: Image.PreserveAspectFit
                        source: "../images/" + modelData.img
                    }

                    onPressed: panel.tv.launchApp(modelData.id)
                }
            }
        }
    }
    }
}
