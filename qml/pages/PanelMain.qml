import QtQuick 2.0
import Sailfish.Silica 1.0

/* Erste Karussellseite: Ein/Aus, Steuerkreuz, Funktionstasten, Ton und Kanal. */
Item {
    id: panel

    property var tv
    property var window

    /* Kurzanzeige zwischen den Kanaltasten: nach einer Aenderung zwei
       Sekunden lang der neue Wert. */
    QtObject {
        id: flash
        property string text: ""
    }

    Timer {
        id: flashTimer
        interval: 2000
    }

    Connections {
        target: tv
        onVolumeChanged: {
            if (!tv.registered) return
            /* Bei externem Ton ist die Zahl nur der TV-Zaehler und hat mit
               dem Pegel am Geraet nichts zu tun - dann lieber sagen, wo der
               Ton herauskommt, als eine falsche Zahl zeigen. */
            flash.text = tv.muted ? "stumm"
                       : tv.volumeReliable ? String(tv.volume) : "ARC"
            flashTimer.restart()
        }
        onChannelChanged: {
            if (tv.channel.length === 0) return
            flash.text = tv.channel
            flashTimer.restart()
        }
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: col.height + Theme.paddingLarge
        // Waagerechtes Wischen gehoert dem Karussell, nicht dieser Liste
        flickableDirection: Flickable.VerticalFlick

        MainMenu { tv: panel.tv; window: panel.window }

        Column {
            id: col
            width: parent.width
            spacing: Theme.paddingLarge

            // ---------- Kopf: Ein/Aus links, Zustand rechts ----------

            Item {
                width: parent.width
                height: power.height + Theme.horizontalPageMargin + Theme.paddingMedium

                Item {
                    id: power
                    x: Theme.horizontalPageMargin
                    y: Theme.horizontalPageMargin
                    width: Theme.itemSizeHuge
                    height: Theme.itemSizeHuge

                    property bool longPressed: false

                    /* Der Zustand steckt in der Farbe des Zeichens, nicht in
                       einem Text: gruen verbunden, rot getrennt, orange
                       blinkend waehrend Verbindungsaufbau oder Suche. */
                    property bool searching: !panel.tv.registered
                                             && (panel.tv.linkUp || reconnect.running)
                    property color stateColor: panel.tv.registered ? "#4caf50"
                                             : searching ? "#ff9800" : "#e53935"

                    Rectangle {
                        anchors.fill: parent
                        radius: width / 2
                        color: hold.running ? Theme.rgba(Theme.errorColor, 0.25)
                                            : Theme.rgba(Theme.primaryColor, 0.10)
                        border.width: 2
                        border.color: Theme.rgba(power.stateColor, 0.5)
                        Behavior on color { ColorAnimation { duration: 200 } }
                    }

                    // Waechst waehrend des Haltens - zeigt an, wann Ausschalten greift
                    Rectangle {
                        anchors.centerIn: parent
                        width: parent.width * fill.progress
                        height: width
                        radius: width / 2
                        color: Theme.rgba(Theme.errorColor, 0.35)
                    }

                    QtObject {
                        id: fill
                        property real progress: 0
                    }

                    NumberAnimation {
                        id: fillAnim
                        target: fill; property: "progress"
                        from: 0; to: 1; duration: 2000
                    }

                    Label {
                        id: powerGlyph
                        anchors.centerIn: parent
                        text: "⏻"
                        font.pixelSize: parent.width * 0.42
                        color: power.stateColor
                        Behavior on color { ColorAnimation { duration: 300 } }

                        SequentialAnimation on opacity {
                            running: power.searching
                            loops: Animation.Infinite
                            alwaysRunToEnd: true
                            NumberAnimation { to: 0.25; duration: 500 }
                            NumberAnimation { to: 1.0;  duration: 500 }
                            onStopped: powerGlyph.opacity = 1.0
                        }
                    }

                    Timer {
                        id: hold
                        interval: 2000
                        onTriggered: {
                            power.longPressed = true
                            panel.tv.turnOff()
                            panel.tv.note("ausgeschaltet")
                        }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onPressed: {
                            power.longPressed = false
                            hold.start()
                            fillAnim.start()
                        }
                        onReleased: {
                            hold.stop(); fillAnim.stop(); fill.progress = 0
                            if (!power.longPressed) {
                                // Kurz tippen weckt den Fernseher
                                var ok = Wol.wake(panel.window.mac, panel.window.host)
                                panel.tv.note(ok ? "Einschaltsignal gesendet"
                                                 : "MAC-Adresse ungültig")
                                if (ok) reconnect.start()
                            }
                        }
                        onCanceled: { hold.stop(); fillAnim.stop(); fill.progress = 0 }
                    }
                }

            }

            // ---------- Steuerkreuz ----------

            Grid {
                anchors.horizontalCenter: parent.horizontalCenter
                columns: 3
                spacing: Theme.paddingLarge
                enabled: panel.tv.pointerReady
                opacity: panel.tv.pointerReady ? 1.0 : 0.3

                RemoteKey { blank: true }
                RemoteKey { text: "▲"; onPressed: panel.tv.button("UP") }
                RemoteKey { blank: true }

                RemoteKey { text: "◀"; onPressed: panel.tv.button("LEFT") }
                RemoteKey { text: "OK"; round: true; fontSize: Theme.fontSizeLarge
                            onPressed: panel.tv.button("ENTER") }
                RemoteKey { text: "▶"; onPressed: panel.tv.button("RIGHT") }

                RemoteKey { blank: true }
                RemoteKey { text: "▼"; onPressed: panel.tv.button("DOWN") }
                RemoteKey { blank: true }
            }

            // ---------- Zurück, Home, Info ----------

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingLarge
                enabled: panel.tv.pointerReady
                opacity: panel.tv.pointerReady ? 1.0 : 0.3

                IconKey { icon: "icon-m-back";  label: "Zurück"
                          onPressed: panel.tv.button("BACK") }
                IconKey { icon: "icon-m-home";  label: "Home"
                          onPressed: panel.tv.button("HOME") }
                IconKey { icon: "icon-m-about"; label: "Info"
                          onPressed: panel.tv.button("INFO") }
            }

            // ---------- Guide, Geräte, Einstellungen ----------

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.paddingLarge
                enabled: panel.tv.registered
                opacity: panel.tv.registered ? 1.0 : 0.3

                IconKey { icon: "icon-m-events"; label: "Guide"
                          onPressed: panel.tv.button("GUIDE") }
                /* TV_VIDEO bildet die Eingangstaste der Originalfernbedienung
                   genau nach: erster Druck blendet die Leiste ein, jeder
                   weitere schaltet zum naechsten Geraet weiter. Der Name
                   gehoert zu Keycode 241, in den Linux-Headern KEY_VIDEO_NEXT,
                   "drive next video source". Langer Druck oeffnet stattdessen
                   die Liste in der App. */
                IconKey {
                    icon: "icon-m-device"; label: "Input"
                    onPressed: panel.tv.button("TV_VIDEO")
                    onPressAndHold: pageStack.push(Qt.resolvedUrl("AppsPage.qml"),
                                                   { tv: panel.tv })
                }
                // Es gibt keine startbare Einstellungs-App; die Zahnradtaste
                // der Fernbedienung heisst im Protokoll MENU
                IconKey { icon: "icon-m-setting"; label: "Einstellungen"
                          onPressed: panel.tv.button("MENU") }
            }

            // ---------- Ton und Kanal ----------

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: Theme.itemSizeSmall
                enabled: panel.tv.registered
                opacity: panel.tv.registered ? 1.0 : 0.3

                Column {
                    spacing: Theme.paddingLarge
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Ton"
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: Theme.secondaryColor
                    }
                    RemoteKey { text: "+"; repeatable: true; repeatInterval: 200
                                onActivated: panel.tv.volumeUp() }
                    RemoteKey { text: panel.tv.muted ? "🔇" : "🔊"
                                fontSize: Theme.fontSizeLarge
                                onPressed: panel.tv.setMute(!panel.tv.muted) }
                    RemoteKey { text: "−"; repeatable: true; repeatInterval: 200
                                onActivated: panel.tv.volumeDown() }
                }

                Column {
                    spacing: Theme.paddingLarge
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: "Kanal"
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: Theme.secondaryColor
                    }
                    RemoteKey { text: "▲"; repeatable: true; onActivated: panel.tv.channelUp() }

                    /* Zeigt nach einer Aenderung zwei Sekunden lang an, was
                       sich geaendert hat - Lautstaerke oder Kanal. Sonst leer,
                       damit die Flaeche ruhig bleibt. */
                    /* Breiter als eine Taste, damit auch ein Sendername
                       hineinpasst. Nach links und rechts ueber die Spalte
                       hinaus, aber mittig darueber. */
                    Item {
                        // Breite wie eine Taste, damit die Spalte ihre alte
                        // Position behaelt; die Beschriftung darf ueberstehen
                        width: Theme.itemSizeLarge
                        height: Theme.itemSizeLarge
                        clip: false

                        Label {
                            anchors.centerIn: parent
                            width: Theme.itemSizeLarge * 2.8
                            horizontalAlignment: Text.AlignHCenter
                            text: flash.text
                            visible: flashTimer.running
                            wrapMode: Text.Wrap
                            maximumLineCount: 2
                            elide: Text.ElideRight
                            font.pixelSize: flash.text.length > 6 ? Theme.fontSizeSmall
                                          : flash.text.length > 3 ? Theme.fontSizeMedium
                                                                  : Theme.fontSizeLarge
                            color: Theme.highlightColor
                        }
                    }

                    RemoteKey { text: "▼"; repeatable: true; onActivated: panel.tv.channelDown() }
                }
            }

            Item { width: 1; height: Theme.paddingLarge }
        }

        VerticalScrollDecorator { }
    }

    // Nach dem Aufwecken braucht der Fernseher etwa 15 s, bis er Verbindungen annimmt
    Timer {
        id: reconnect
        interval: 6000
        repeat: true
        property int tries: 0
        onTriggered: {
            if (panel.tv.registered || tries >= 5) { stop(); tries = 0; return }
            tries++
            panel.tv.connectTv()
        }
    }
}
