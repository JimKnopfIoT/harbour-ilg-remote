import QtQuick 2.0
import Sailfish.Silica 1.0

/* Apps und Eingaenge des Fernsehers. pickIndex >= 0: die Auswahl belegt die
   Kachel mit diesem Index, statt sie zu starten. */
Page {
    id: page

    property var tv
    property var window
    property int pickIndex: -1

    readonly property bool picking: pickIndex >= 0

    allowedOrientations: Orientation.Portrait

    ListModel { id: entries }

    Connections {
        target: tv
        onInputsReceived: {
            for (var i = 0; i < inputs.length; i++)
                entries.append({ "kind": "input", "ident": inputs[i].ident,
                                 "label": inputs[i].label, "icon": inputs[i].icon,
                                 "group": qsTr("Inputs") })
            busy.running = false
        }
        onAppsReceived: {
            for (var j = 0; j < apps.length; j++)
                entries.append({ "kind": "app", "ident": apps[j].ident,
                                 "label": apps[j].label, "icon": apps[j].icon,
                                 "group": qsTr("Apps") })
            busy.running = false
        }
    }

    // Beide Abfragen unabhaengig: lehnt der Fernseher eine ab, kommt die andere
    // trotzdem an
    function reload() {
        entries.clear()
        busy.running = true
        tv.requestInputs()
        tv.requestApps()
    }

    Component.onCompleted: reload()

    SilicaListView {
        anchors.fill: parent
        model: entries

        header: PageHeader {
            title: page.picking ? qsTr("Assign tile") : qsTr("Apps and inputs")
        }

        PullDownMenu {
            MenuItem {
                visible: page.picking
                text: qsTr("Restore the default tiles")
                onClicked: {
                    page.window.resetTiles()
                    pageStack.pop()
                }
            }
            MenuItem {
                visible: page.picking
                text: qsTr("Clear tile")
                onClicked: {
                    page.window.setTile(page.pickIndex, "app", "", "", "")
                    pageStack.pop()
                }
            }
            MenuItem { text: qsTr("Reload"); onClicked: page.reload() }
        }

        section {
            property: "group"
            delegate: SectionHeader { text: section }
        }

        delegate: ListItem {
            width: parent.width

            Image {
                id: icon
                x: Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                width: Theme.iconSizeSmall
                height: width
                fillMode: Image.PreserveAspectFit
                // Der Fernseher gibt die Symbole nur ueber https heraus
                source: model.icon.length > 0
                        ? "image://tvicon/" + encodeURIComponent(model.icon) : ""
                visible: status === Image.Ready
            }

            Label {
                x: icon.visible ? icon.x + icon.width + Theme.paddingMedium
                                : Theme.horizontalPageMargin
                width: parent.width - x - Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                text: model.label
                truncationMode: TruncationMode.Fade
            }

            onClicked: {
                if (page.picking)
                    page.window.setTile(page.pickIndex, model.kind, model.ident,
                                        model.label, model.icon)
                else if (model.kind === "input")
                    tv.switchInput(model.ident)
                else
                    tv.launchApp(model.ident)
                pageStack.pop()
            }
        }

        ViewPlaceholder {
            enabled: entries.count === 0 && !busy.running
            text: qsTr("Nothing found")
            hintText: qsTr("Is the television connected?")
        }

        VerticalScrollDecorator { }
    }

    BusyIndicator {
        id: busy
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: false
    }
}
