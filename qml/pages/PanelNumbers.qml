import QtQuick 2.0
import Sailfish.Silica 1.0

/* Zweite Karussellseite: Zahlenblock mit vierstelliger Kanalanzeige und den
   vier frei belegbaren Direktaufrufen. */
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
        // Zusaetzlich direkt senden - so reagiert der Fernseher sofort
        tv.button(d)
    }

    function pick(i) {
        pageStack.push(Qt.resolvedUrl("AppsPage.qml"),
                       { tv: panel.tv, window: panel.window, pickIndex: i })
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

            // Abbruch links, Bestaetigen unten rechts - dort sitzt auf jedem
            // Ziffernblock die Eingabetaste
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
        // Fuenf frei belegbare Kacheln (langer Druck belegt neu), die sechste
        // ist fest das Bildschirmfoto. Rasterbreite wie das Tastenfeld.

        Item { width: 1; height: Theme.itemSizeSmall }

        Grid {
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 3
            spacing: Theme.paddingLarge
            enabled: panel.tv.registered
            opacity: panel.tv.registered ? 1.0 : 0.3

            Repeater {
                model: panel.window.tiles

                MouseArea {
                    width: Theme.itemSizeLarge
                    height: Theme.itemSizeLarge

                    Rectangle {
                        anchors.fill: parent
                        radius: Theme.paddingMedium
                        color: parent.pressed ? Theme.rgba(Theme.highlightBackgroundColor, 0.5)
                                              : "transparent"
                        border.width: modelData.id.length > 0 ? 0 : 1
                        border.color: Theme.rgba(Theme.primaryColor, 0.22)
                    }

                    /* QML merkt sich einen gescheiterten Abruf und fragt fuer
                       dieselbe Quelle nicht noch einmal nach - deshalb cache:
                       false und ein eigener zweiter Anlauf. Sonst bleibt die
                       Kachel leer, bis die App neu startet. */
                    Image {
                        id: tileIcon
                        anchors.centerIn: parent
                        width: parent.width - 2 * Theme.paddingMedium
                        height: width
                        fillMode: Image.PreserveAspectFit
                        cache: false
                        asynchronous: true
                        source: modelData.img.length > 0
                                ? "../images/" + modelData.img
                                : modelData.icon.length > 0
                                  ? "image://tvicon/" + encodeURIComponent(modelData.icon) : ""
                        visible: status === Image.Ready

                        onStatusChanged: if (status === Image.Error && modelData.icon.length > 0)
                                             icons.prefetch(modelData.icon)

                        Connections {
                            target: icons
                            onIconReady: {
                                if (url !== modelData.icon) return
                                // Neu anstossen, jetzt liegt es auf der Platte
                                var s = tileIcon.source
                                tileIcon.source = ""
                                tileIcon.source = s
                            }
                        }
                    }

                    Label {
                        anchors.centerIn: parent
                        width: parent.width - Theme.paddingSmall
                        visible: !tileIcon.visible
                        horizontalAlignment: Text.AlignHCenter
                        text: modelData.id.length > 0 ? modelData.label : "+"
                        truncationMode: TruncationMode.Fade
                        font.pixelSize: modelData.id.length > 0 ? Theme.fontSizeExtraSmall
                                                                : Theme.fontSizeLarge
                        color: Theme.secondaryColor
                    }

                    onClicked: {
                        if (modelData.id.length === 0)
                            panel.pick(index)
                        else if (modelData.kind === "input")
                            panel.tv.switchInput(modelData.id)
                        else
                            panel.tv.launchApp(modelData.id)
                    }
                    onPressAndHold: panel.pick(index)
                }
            }

            // Feste sechste Kachel
            MouseArea {
                width: Theme.itemSizeLarge
                height: Theme.itemSizeLarge

                Rectangle {
                    anchors.fill: parent
                    radius: Theme.paddingMedium
                    color: parent.pressed ? Theme.rgba(Theme.highlightBackgroundColor, 0.5)
                                          : "transparent"
                }

                Image {
                    anchors.centerIn: parent
                    width: parent.width - 2 * Theme.paddingMedium
                    height: width
                    fillMode: Image.PreserveAspectFit
                    source: "../images/shutter.png"
                }

                onClicked: panel.tv.captureScreen()
            }
        }
    }
    }
}
