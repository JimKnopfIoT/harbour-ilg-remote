import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    property var tv

    allowedOrientations: Orientation.All

    ListModel { id: entries }

    // Der C++-Teil antwortet ueber Signale, nicht ueber Rueckrufe
    Connections {
        target: tv
        onInputsReceived: {
            for (var i = 0; i < inputs.length; i++) {
                entries.append({
                    "kind": "input",
                    "ident": inputs[i].ident,
                    "label": inputs[i].label,
                    "group": "Eingänge"
                })
            }
            tv.requestApps()
        }
        onAppsReceived: {
            for (var j = 0; j < apps.length; j++) {
                entries.append({
                    "kind": "app",
                    "ident": apps[j].ident,
                    "label": apps[j].label,
                    "group": "Apps"
                })
            }
            busy.running = false
        }
    }

    function reload() {
        entries.clear()
        busy.running = true
        tv.requestInputs()   // Apps folgen, sobald die Eingaenge da sind
    }

    Component.onCompleted: reload()

    SilicaListView {
        anchors.fill: parent
        model: entries
        header: PageHeader { title: "Apps und Eingänge" }

        PullDownMenu {
            MenuItem { text: "Neu einlesen"; onClicked: page.reload() }
        }

        section {
            property: "group"
            delegate: SectionHeader { text: section }
        }

        delegate: ListItem {
            width: parent.width
            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                text: model.label
                truncationMode: TruncationMode.Fade
            }
            onClicked: {
                if (model.kind === "input") tv.switchInput(model.ident)
                else tv.launchApp(model.ident)
                pageStack.pop()
            }
        }

        ViewPlaceholder {
            enabled: entries.count === 0 && !busy.running
            text: "Nichts gefunden"
            hintText: "Ist der Fernseher verbunden?"
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
