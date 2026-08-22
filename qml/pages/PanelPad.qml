import QtQuick 2.0
import Sailfish.Silica 1.0

/* Dritte Karussellseite: die Flaeche als Mauszeiger, mit Rollbalken rechts
   und unten. Die Tastatur bleibt offen, solange die Seite vorn liegt. */
Item {
    id: panel

    property var tv
    property var window
    // Liegt diese Seite im Karussell vorn?
    property bool current: true

    onCurrentChanged: {
        if (current) textField.forceActiveFocus()
        else textField.focus = false
    }
    Component.onCompleted: {
        console.log("PanelPad angelegt, current =", current)
        if (current) textField.forceActiveFocus()
    }

    // Kleinste je gesehene Hoehe: die mit Tastatur. Danach richtet sich der
    // Aufbau dauerhaft, sonst waechst die Zeigerflaeche wieder
    property real festeHoehe: 0
    onHeightChanged: if (height > 0 && (festeHoehe === 0 || height < festeHoehe))
                         festeHoehe = height

    // Fokus zurueckholen, egal wer ihn genommen hat
    Timer {
        id: fokusZurueck
        interval: 400
        // Waehrend des Tippens dazwischenzufunken loescht die Eingabe
        onTriggered: if (panel.current && !textField.activeFocus
                         && pageStack.depth === 1)
                         textField.forceActiveFocus()
    }

    Connections {
        target: textField
        onActiveFocusChanged: if (!textField.activeFocus && panel.current)
                                  fokusZurueck.restart()
    }

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

        // Keine eigene Rechnerei mit der Tastaturhoehe - Silica kuerzt die
        // Seite bereits selbst
        Item {
            id: bereich
            anchors { left: parent.left; right: parent.right; top: parent.top }
            height: panel.festeHoehe > 0 ? panel.festeHoehe : parent.height

            // Ohne diesen Streifen kaeme man von der Seite nicht mehr herunter
            Item {
                id: streifen
                anchors { left: parent.left; right: parent.right; top: parent.top }
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
                anchors {
                    left: parent.left
                    right: parent.right
                    top: streifen.bottom
                    bottom: keyboardRow.top
                    bottomMargin: Theme.paddingMedium
                }

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

                        onPressed: {
                            lastX = mouse.x; lastY = mouse.y; dragged = false
                        }

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

                        onPressed: { last = mouse.y; accum = 0
                                     if (panel.current) textField.forceActiveFocus() }
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

                        onPressed: { last = mouse.x; accum = 0
                                     if (panel.current) textField.forceActiveFocus() }
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
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                    leftMargin: Theme.horizontalPageMargin
                    rightMargin: Theme.horizontalPageMargin
                    bottomMargin: Theme.paddingMedium
                }
                spacing: Theme.paddingSmall

                property real keySize: Theme.itemSizeExtraSmall

                // Die Tastatur des TV schliesst sich von selbst - gemerkt
                // statt gesperrt
                property bool waiting: false

                // Zwei getrennte Knoepfe statt eines geratenen: nach dem
                // Vordergrund fragen geht nicht mehr (403)
                function send() {
                    if (textField.text.length === 0) return
                    if (panel.tv.textInputReady) {
                        panel.tv.insertText(textField.text)
                        textField.text = ""
                        textField.forceActiveFocus()
                        waiting = false
                        return
                    }
                    /* Kein gemeldetes Feld heisst: die App im Vordergrund malt
                       ihre eigene Tastatur, wie YouTube. Dorthin kommt kein
                       Text, und ENTER druecke nur die markierte Taste. */
                    if (panel.tv.textInputType.length === 0) {
                        waiting = false
                        panel.tv.note(qsTr("no text field on the TV - use the magnifier for YouTube"))
                        return
                    }
                    // Feld da, Tastatur zu: ENTER oeffnet sie am Cursor
                    waiting = true
                    panel.tv.button("ENTER")
                }

                function search() {
                    if (textField.text.length === 0) return
                    panel.tv.searchYouTube(textField.text)
                    textField.text = ""
                    textField.focus = false
                    waiting = false
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
                    width: keyboardRow.width - 4 * (keyboardRow.keySize + Theme.paddingSmall)
                    enabled: panel.tv.registered
                    placeholderText: keyboardRow.waiting
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
                // Text in das Feld am Fernseher
                IconKey {
                    anchors.verticalCenter: textField.verticalCenter
                    icon: "icon-m-accept"
                    size: keyboardRow.keySize
                    enabled: panel.tv.registered && textField.text.length > 0
                    opacity: enabled ? 1.0 : 0.3
                    onPressed: keyboardRow.send()
                }

                // Suchbegriff als Startparameter an YouTube, ohne Tastatur
                IconKey {
                    anchors.verticalCenter: textField.verticalCenter
                    icon: "icon-m-search"
                    size: keyboardRow.keySize
                    enabled: panel.tv.registered && textField.text.length > 0
                    opacity: enabled ? 1.0 : 0.3
                    onPressed: keyboardRow.search()
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
                    onPressed: { textField.text = ""; textField.forceActiveFocus() }
                }
            }

            Item { width: 1; height: Theme.paddingMedium }
        }
    }
}
