import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    property var tv
    property var window

    allowedOrientations: Orientation.Portrait

    RemorsePopup { id: remorse }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: col.height

        Column {
            id: col
            width: parent.width
            spacing: Theme.paddingMedium

            PageHeader { title: qsTr("Settings") }

            // ---------- Service-Menues ----------
            // Eingeklappt und mit Rueckfrage: hier stehen Geraeteparameter,
            // die das normale Menue nicht zeigt.

            ExpandingSectionGroup {
                currentIndex: -1

                ExpandingSection {
                    title: qsTr("Service menus of the TV")

                    content.sourceComponent: Column {
                        width: parent.width
                        spacing: Theme.paddingMedium

                        Label {
                            x: Theme.horizontalPageMargin
                            width: parent.width - 2 * Theme.horizontalPageMargin
                            wrapMode: Text.Wrap
                            font.pixelSize: Theme.fontSizeExtraSmall
                            color: Theme.errorColor
                            text: qsTr("Warning: these menus are meant for service technicians. They expose picture, sound and device parameters that the normal menu does not reach. Changes can render the TV unusable and are partly irreversible. Only open them if you know what you are doing.")
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
                                    remorse.execute(qsTr("Opening %1").arg(modelData.text),
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
                            text: qsTr("Way out: the back key, or switch the TV off and on again.")
                        }
                    }
                }
            }

            // ---------- Aktuelles Geraet ----------

            SectionHeader { text: qsTr("Device") }

            DetailItem { label: qsTr("Name");    value: page.window.deviceName }
            DetailItem { label: qsTr("Address"); value: page.window.host }
            DetailItem { label: qsTr("MAC");     value: page.window.mac.length > 0
                                                        ? page.window.mac : qsTr("not stored") }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("Wake-on-LAN has to be enabled on the TV: Settings → General → External devices → Turn on via mobile device.")
            }

            // ---------- Lautstaerke abgleichen ----------

            SectionHeader { text: qsTr("Match the volume") }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("With the sound on an external device over ARC, the TV keeps a counter of its own that has nothing to do with the real level - the amplifier never reports back. Enter what the device shows and the display follows along.")
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                spacing: Theme.paddingMedium

                TextField {
                    id: volField
                    width: parent.width - volSet.width - Theme.paddingMedium
                    label: qsTr("Level on the audio device")
                    placeholderText: String(tv.volume >= 0 ? tv.volume : 0)
                    inputMethodHints: Qt.ImhDigitsOnly
                    validator: IntValidator { bottom: 0; top: 100 }
                    EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                    EnterKey.onClicked: volSet.apply()
                }

                Button {
                    id: volSet
                    anchors.verticalCenter: volField.verticalCenter
                    text: qsTr("Set")
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

            SectionHeader { text: qsTr("Pairing") }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.secondaryHighlightColor
                text: tv.clientKey.length > 0
                      ? qsTr("Paired. The TV no longer asks.")
                      : qsTr("Not paired yet. Connecting brings up a prompt on the TV.")
            }

            DetailItem {
                label: qsTr("Certificate")
                // Die ersten Bytes reichen zum Vergleichen
                value: tv.certFingerprint.length > 0
                       ? tv.certFingerprint.substring(0, 16) : qsTr("not stored")
            }

            /* Der Schluessel gehoert zum Geraet, nicht zur App - deshalb
               steht das Loesen dort, wo die Geraete stehen. */
            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("A pairing belongs to one television. Releasing it is therefore done in the device list: hold the entry, then Reset pairing.")
            }

            // ---------- Tastencode ----------

            SectionHeader { text: qsTr("Try a key code") }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("The TV accepts about 450 key names and silently drops invalid ones. Try one here without rebuilding the app - QMENU, MYAPPS, RECENT, LIST, SIMPLINK, GUIDE or SCREEN_REMOTE for instance.")
            }

            Row {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                spacing: Theme.paddingMedium

                TextField {
                    id: rawField
                    width: parent.width - rawSend.width - Theme.paddingMedium
                    placeholderText: qsTr("e.g. INPUT")
                    label: qsTr("Key name")
                    enabled: tv.pointerReady
                    inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
                    EnterKey.iconSource: "image://theme/icon-m-enter-accept"
                    EnterKey.onClicked: rawSend.fire()
                }

                Button {
                    id: rawSend
                    anchors.verticalCenter: rawField.verticalCenter
                    text: qsTr("Send")
                    enabled: tv.pointerReady && rawField.text.length > 0
                    onClicked: fire()

                    function fire() {
                        if (rawField.text.length === 0) return
                        tv.sendRaw(rawField.text.trim().toUpperCase())
                    }
                }
            }

            // ---------- Zustand ----------

            SectionHeader { text: qsTr("State") }

            DetailItem { label: qsTr("Connection"); value: tv.linkUp ? qsTr("open") : qsTr("closed") }
            DetailItem { label: qsTr("Paired");     value: tv.registered ? qsTr("yes") : qsTr("no") }
            DetailItem { label: qsTr("Key channel"); value: tv.pointerReady ? qsTr("ready")
                                                                            : qsTr("not ready") }
            DetailItem { label: qsTr("Message");    value: tv.statusText }
            DetailItem { label: qsTr("Text field on the TV")
                         value: tv.textInputReady
                                ? qsTr("ready (%1, %2 characters)").arg(tv.textInputType)
                                                                   .arg(tv.textInputLength)
                                : qsTr("no field open") }

            SectionHeader { text: qsTr("Diagnostics") }

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
