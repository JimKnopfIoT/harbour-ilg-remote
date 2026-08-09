import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    property var tv
    property var window

    allowedOrientations: Orientation.All

    RemorsePopup { id: remorse }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: col.height

        Column {
            id: col
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { title: "Einstellungen" }

            // ---------- Service-Menüs des Fernsehers ----------
            // Eingeklappt und mit Rückfrage: hier lassen sich Geräte-
            // einstellungen verstellen, die im normalen Menü nicht auftauchen.

            ExpandingSectionGroup {
                currentIndex: -1

                ExpandingSection {
                    title: "Service-Menüs des Fernsehers"

                    content.sourceComponent: Column {
                        width: parent.width
                        spacing: Theme.paddingMedium

                        Label {
                            x: Theme.horizontalPageMargin
                            width: parent.width - 2 * Theme.horizontalPageMargin
                            wrapMode: Text.Wrap
                            font.pixelSize: Theme.fontSizeExtraSmall
                            color: Theme.errorColor
                            text: "Achtung: Diese Menüs sind für den Kundendienst gedacht. " +
                                  "Dort lassen sich Bild-, Ton- und Geräteparameter verstellen, " +
                                  "die im normalen Menü nicht erreichbar sind. Änderungen " +
                                  "können den Fernseher unbrauchbar machen und sind teils nicht " +
                                  "zurücknehmbar. Nur öffnen, wenn du weißt, was du tust – und " +
                                  "nichts verstellen, was du nicht wiederherstellen kannst."
                        }

                        Repeater {
                            model: [
                                { "name": "EZ_ADJUST",       "text": "EZ Adjust" },
                                { "name": "IN_START",        "text": "In Start" },
                                { "name": "ADVANCE_SETTING", "text": "Advanced Setting" }
                            ]

                            Button {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: modelData.text
                                enabled: tv.pointerReady
                                onClicked: {
                                    var n = modelData.name
                                    remorse.execute(modelData.text + " wird geöffnet",
                                                    function () { tv.sendRaw(n) })
                                }
                            }
                        }

                        Label {
                            x: Theme.horizontalPageMargin
                            width: parent.width - 2 * Theme.horizontalPageMargin
                            wrapMode: Text.Wrap
                            font.pixelSize: Theme.fontSizeTiny
                            color: Theme.secondaryColor
                            text: "Herauskommen: Zurück-Taste, notfalls den Fernseher aus- und " +
                                  "wieder einschalten."
                        }
                    }
                }
            }

            // ---------- Aktuelles Gerät ----------

            SectionHeader { text: "Gerät" }

            DetailItem { label: "Name";    value: page.window.deviceName }
            DetailItem { label: "Adresse"; value: page.window.host }
            DetailItem { label: "MAC";     value: page.window.mac.length > 0
                                                  ? page.window.mac : "nicht hinterlegt" }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Geräte verwalten"
                onClicked: pageStack.push(Qt.resolvedUrl("DevicesPage.qml"),
                                          { tv: page.tv, window: page.window })
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: "Wake-on-LAN muss am Fernseher aktiviert sein: Einstellungen → " +
                      "Allgemein → Externe Geräte → Über Mobilgerät einschalten."
            }

            // ---------- Lautstärke abgleichen ----------

            SectionHeader { text: "Lautstärke abgleichen" }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: "Hängt der Ton über ARC an einem externen Gerät, führt der Fernseher " +
                      "einen eigenen Zähler, der mit dem echten Pegel nichts zu tun hat – " +
                      "die Anlage meldet ihren Stand nie zurück, das ist am CEC-Bus " +
                      "nachgemessen. Trag hier ein, was am Gerät steht, dann zieht die " +
                      "Anzeige nach und bleibt im Gleichschritt."
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                spacing: Theme.paddingMedium

                TextField {
                    id: volField
                    width: parent.width - volSet.width - Theme.paddingMedium
                    label: "Pegel am Tongerät"
                    placeholderText: String(tv.volume >= 0 ? tv.volume : 0)
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator { bottom: 0; top: 100 }
                    EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                    EnterKey.onClicked: volSet.apply()
                }

                Button {
                    id: volSet
                    anchors.verticalCenter: volField.verticalCenter
                    text: "Setzen"
                    enabled: tv.registered && volField.text.length > 0
                    onClicked: apply()

                    function apply() {
                        if (volField.text.length === 0) return
                        tv.setVolume(parseInt(volField.text))
                        volField.text = ""
                        volField.focus = false
                    }
                }
            }

            // ---------- Kopplung ----------

            SectionHeader { text: "Kopplung" }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.secondaryHighlightColor
                text: tv.clientKey.length > 0
                      ? "Gekoppelt. Der Fernseher fragt nicht mehr nach."
                      : "Noch nicht gekoppelt. Beim Verbinden erscheint eine Abfrage am Fernseher."
            }

            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Kopplung zurücksetzen"
                enabled: tv.clientKey.length > 0
                onClicked: {
                    tv.clientKey = ""
                    tv.disconnectTv()
                }
            }

            // ---------- Tastencode ----------

            SectionHeader { text: "Tastencode ausprobieren" }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: "Der Fernseher nimmt rund 450 Tastennamen entgegen; ungültige " +
                      "verwirft er stumm. Hier lässt sich einer ausprobieren, ohne die " +
                      "App neu zu bauen – etwa QMENU, MYAPPS, RECENT, LIST, SIMPLINK, " +
                      "GUIDE oder SCREEN_REMOTE."
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                spacing: Theme.paddingMedium

                TextField {
                    id: rawField
                    width: parent.width - rawSend.width - Theme.paddingMedium
                    placeholderText: "z. B. INPUT"
                    label: "Tastenname"
                    enabled: tv.pointerReady
                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
                    EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                    EnterKey.onClicked: rawSend.fire()
                }

                Button {
                    id: rawSend
                    anchors.verticalCenter: rawField.verticalCenter
                    text: "Senden"
                    enabled: tv.pointerReady && rawField.text.length > 0
                    onClicked: fire()

                    function fire() {
                        if (rawField.text.length === 0) return
                        tv.sendRaw(rawField.text.trim().toUpperCase())
                    }
                }
            }

            // ---------- Zustand ----------

            SectionHeader { text: "Zustand" }

            DetailItem { label: "Verbindung";  value: tv.linkUp ? "offen" : "getrennt" }
            DetailItem { label: "Gekoppelt";   value: tv.registered ? "ja" : "nein" }
            DetailItem { label: "Tastenkanal"; value: tv.pointerReady ? "bereit" : "nicht bereit" }
            DetailItem { label: "Meldung";     value: tv.statusText }
            DetailItem { label: "Textfeld am TV"
                         value: tv.textInputReady
                                ? "bereit (" + tv.textInputType + ", "
                                  + tv.textInputLength + " Zeichen)"
                                : "kein Feld offen" }

            SectionHeader { text: "Diagnose" }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                font.family: "monospace"
                color: Theme.secondaryColor
                text: tv.diagnostics
            }

            Item { width: 1; height: Theme.paddingLarge }
        }

        VerticalScrollDecorator { }
    }
}
