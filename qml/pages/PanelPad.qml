import QtQuick 2.0
import Sailfish.Silica 1.0

/* Dritte Karussellseite: die Flaeche als Mauszeiger, mit Rollbalken rechts
   und unten. Von unten hochwischen blendet die Tastatur ein. */
Item {
    id: panel

    property var tv
    property var window

    readonly property real strip: Theme.itemSizeSmall   // Breite der Rollbalken

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: height
        flickableDirection: Flickable.VerticalFlick

        MainMenu { tv: panel.tv; window: panel.window }

        PushUpMenu {
            MenuItem {
                text: qsTr("Show keyboard")
                onClicked: textField.forceActiveFocus()
            }
        }

        Column {
            anchors.fill: parent
            spacing: Theme.paddingMedium

            // Ohne diesen Streifen kaeme man von der Seite nicht mehr herunter
            Item {
                width: parent.width
                height: Theme.itemSizeSmall

                Label {
                    anchors.centerIn: parent
                    text: qsTr("◀   swipe here to change page   ▶")
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.rgba(Theme.secondaryColor, 0.7)
                }
            }

            Item {
                id: padArea
                width: parent.width
                height: parent.height - keyboardRow.height - Theme.itemSizeSmall
                        - 2 * Theme.paddingMedium

                // ---------- Zeigerfläche ----------

                Rectangle {
                    id: pad
                    anchors {
                        left: parent.left
                        top: parent.top
                        leftMargin: Theme.paddingMedium
                        topMargin: Theme.paddingMedium
                    }
                    width: parent.width - panel.strip - 2 * Theme.paddingMedium
                    height: parent.height - panel.strip - 2 * Theme.paddingMedium
                    radius: Theme.paddingLarge
                    color: Theme.rgba(Theme.primaryColor, 0.06)
                    border.width: 1
                    border.color: Theme.rgba(Theme.primaryColor, 0.18)

                    Column {
                        anchors.centerIn: parent
                        spacing: Theme.paddingSmall
                        visible: !panel.tv.pointerReady

                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: qsTr("not connected")
                            color: Theme.secondaryColor
                            font.pixelSize: Theme.fontSizeSmall
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        enabled: panel.tv.pointerReady
                        preventStealing: true

                        property real lastX: 0
                        property real lastY: 0
                        property bool dragged: false

                        onPressed: { lastX = mouse.x; lastY = mouse.y; dragged = false }

                        onPositionChanged: {
                            var dx = mouse.x - lastX
                            var dy = mouse.y - lastY
                            // Zittern beim Antippen nicht als Bewegung werten
                            if (Math.abs(dx) < 2 && Math.abs(dy) < 2) return
                            lastX = mouse.x
                            lastY = mouse.y
                            dragged = true
                            panel.tv.move(Math.round(dx), Math.round(dy))
                        }

                        onReleased: if (!dragged) panel.tv.click()
                    }
                }

                // ---------- Rollbalken rechts (senkrecht) ----------

                Rectangle {
                    id: vScroll
                    anchors {
                        left: pad.right
                        leftMargin: Theme.paddingMedium
                        top: pad.top
                        bottom: pad.bottom
                    }
                    width: panel.strip
                    radius: width / 2
                    color: Theme.rgba(Theme.primaryColor, 0.10)
                    border.width: 1
                    border.color: Theme.rgba(Theme.primaryColor, 0.18)

                    Label {
                        anchors.centerIn: parent
                        text: "⇕"
                        color: Theme.rgba(Theme.primaryColor, 0.35)
                        font.pixelSize: Theme.fontSizeLarge
                    }

                    MouseArea {
                        anchors.fill: parent
                        enabled: panel.tv.pointerReady
                        preventStealing: true
                        property real last: 0
                        // Erst ab einem Schwellwert rollen, sonst ist es zu nervoes
                        property real accum: 0

                        onPressed: { last = mouse.y; accum = 0 }
                        onPositionChanged: {
                            accum += mouse.y - last
                            last = mouse.y
                            while (Math.abs(accum) >= 20) {
                                panel.tv.scroll(0, accum > 0 ? -1 : 1)
                                accum += accum > 0 ? -20 : 20
                            }
                        }
                    }
                }

                // ---------- Rollbalken unten (waagerecht) ----------

                Rectangle {
                    anchors {
                        left: pad.left
                        right: vScroll.right
                        top: pad.bottom
                        topMargin: Theme.paddingMedium
                    }
                    height: panel.strip
                    radius: height / 2
                    color: Theme.rgba(Theme.primaryColor, 0.10)
                    border.width: 1
                    border.color: Theme.rgba(Theme.primaryColor, 0.18)

                    Label {
                        anchors.centerIn: parent
                        text: "◀    ▶"
                        color: Theme.rgba(Theme.primaryColor, 0.35)
                        font.pixelSize: Theme.fontSizeSmall
                    }

                    /* Kein Rollbefehl: webOS verwirft beim Rollen die
                       waagerechte Achse. Also Links/Rechts als Tastendruck. */
                    MouseArea {
                        anchors.fill: parent
                        enabled: panel.tv.pointerReady
                        preventStealing: true
                        property real last: 0
                        property real accum: 0

                        onPressed: { last = mouse.x; accum = 0 }
                        onPositionChanged: {
                            accum += mouse.x - last
                            last = mouse.x
                            // Groesserer Schwellwert: ein Tastendruck springt
                            // eine ganze Auswahl weiter
                            while (Math.abs(accum) >= 90) {
                                panel.tv.button(accum > 0 ? "RIGHT" : "LEFT")
                                accum += accum > 0 ? -90 : 90
                            }
                        }
                    }
                }
            }

            // ---------- Texteingabe ----------

            Row {
                id: keyboardRow
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                spacing: Theme.paddingSmall

                property real keySize: Theme.itemSizeExtraSmall

                /* Die Bildschirmtastatur schliesst sich von selbst, und nur
                   offen nimmt der TV Text an - deshalb gemerkt statt gesperrt. */
                property bool waiting: false

                function send() {
                    if (textField.text.length === 0) return
                    if (panel.tv.textInputReady) {
                        panel.tv.insertText(textField.text)
                        textField.text = ""
                        textField.focus = false
                        waiting = false
                        return
                    }
                    // ENTER oeffnet die Tastatur am Cursor; danach geht der
                    // Text von selbst raus
                    waiting = true
                    panel.tv.button("ENTER")
                }

                Connections {
                    target: panel.tv
                    onTextInputChanged: {
                        if (keyboardRow.waiting && panel.tv.textInputReady
                            && textField.text.length > 0) {
                            panel.tv.insertText(textField.text)
                            textField.text = ""
                            keyboardRow.waiting = false
                        }
                    }
                }

                TextField {
                    id: textField
                    width: parent.width - 3 * (keyboardRow.keySize + Theme.paddingSmall)
                    enabled: panel.tv.registered
                    placeholderText: panel.tv.youtubeAhead
                                     ? qsTr("search on YouTube")
                                     : keyboardRow.waiting
                                       ? qsTr("opening keyboard on the TV ...")
                                       : qsTr("text to the TV")
                    EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                    EnterKey.onClicked: keyboardRow.send()

                    // Beim ersten Zeichen nachfragen; das Abo meldet nur das
                    // Verschwinden zuverlaessig
                    onTextChanged: if (text.length === 1) panel.tv.refreshYouTubeState()
                }

                /* Eine Taste, zwei Wege - das Symbol verraet, welcher gilt:
                   Suchbegriff als Startparameter oder Text ins Feld. */
                IconKey {
                    anchors.verticalCenter: textField.verticalCenter
                    icon: panel.tv.youtubeAhead ? "icon-m-search" : "icon-m-accept"
                    size: keyboardRow.keySize
                    enabled: panel.tv.registered && textField.text.length > 0
                    opacity: enabled ? 1.0 : 0.3
                    onPressed: {
                        if (panel.tv.youtubeAhead) {
                            panel.tv.searchYouTube(textField.text)
                            textField.text = ""
                            textField.focus = false
                            keyboardRow.waiting = false
                        } else {
                            keyboardRow.send()
                        }
                    }
                }

                IconKey {
                    anchors.verticalCenter: textField.verticalCenter
                    icon: "icon-m-back"
                    size: keyboardRow.keySize
                    enabled: panel.tv.pointerReady
                    opacity: enabled ? 1.0 : 0.3
                    onPressed: panel.tv.button("BACK")
                }

                IconKey {
                    anchors.verticalCenter: textField.verticalCenter
                    icon: "icon-m-clear"
                    size: keyboardRow.keySize
                    onPressed: { textField.text = ""; textField.focus = false }
                }
            }

            Item { width: 1; height: Theme.paddingMedium }
        }
    }
}
