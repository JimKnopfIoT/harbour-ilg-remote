import QtQuick 2.0
import Sailfish.Silica 1.0

/* Systemdaten des Fernsehers. Aufruf ueber das Menue, nicht als
   Karussellseite - dort stoerte sie beim Durchblaettern. */
Page {
    id: panel

    property var tv
    property var window

    allowedOrientations: Orientation.All

    ListModel { id: rows }

    function addSection(title) { rows.append({ "kind": "section", "k": title, "v": "" }) }
    function addRow(k, v)      { rows.append({ "kind": "row", "k": k, "v": String(v) }) }
    function addMap(map) {
        for (var key in map) addRow(key, map[key])
    }

    function reload() {
        rows.clear()
        busy.running = true

        addSection("Gerät")
        addRow("Adresse", panel.tv.host)

        if (!panel.tv.registered) {
            addRow("Zustand", "nicht verbunden")
            busy.running = false
            return
        }

        panel.tv.requestSystemInfo()
        panel.tv.requestSoftwareInfo()
        panel.tv.requestNetworkInfo()
        panel.tv.requestAudioStatus()
        panel.tv.requestInputs()
        scanner.scan(panel.tv.host)
    }

    Connections {
        target: tv
        onSystemInfoReceived: panel.addMap(info)
        onSoftwareInfoReceived: panel.addMap(info)
        onNetworkInfoReceived: {
            panel.addSection("Netzwerk")
            panel.addMap(info)
        }
        onAudioStatusReceived: {
            panel.addSection("Ton und ARC")
            panel.addMap(info)
        }
        onInputsReceived: {
            panel.addSection("Eingänge")
            for (var i = 0; i < inputs.length; i++)
                panel.addRow(inputs[i].label, inputs[i].ident)
        }
    }

    Connections {
        target: scanner
        onResult: {
            if (!portsHeaderDone) { panel.addSection("Offene Ports"); portsHeaderDone = true }
            if (open) panel.addRow(port + "  " + service, "offen")
        }
        onFinished: busy.running = false
    }

    property bool portsHeaderDone: false
    Component.onCompleted: reload()

    SilicaListView {
        id: list
        anchors.fill: parent
        model: rows
        flickableDirection: Flickable.VerticalFlick

        header: PageHeader { title: "Systemdaten" }

        PullDownMenu {
            MenuItem {
                text: "Neu einlesen"
                onClicked: { panel.portsHeaderDone = false; panel.reload() }
            }
        }

        delegate: Item {
            width: list.width
            height: model.kind === "section" ? sectionLabel.height + Theme.paddingLarge
                                             : Math.max(keyLabel.height, valueLabel.height)
                                               + Theme.paddingMedium

            Label {
                id: sectionLabel
                visible: model.kind === "section"
                x: Theme.horizontalPageMargin
                anchors.bottom: parent.bottom
                anchors.bottomMargin: Theme.paddingSmall
                text: model.k
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.highlightColor
            }

            Label {
                id: keyLabel
                visible: model.kind === "row"
                x: Theme.horizontalPageMargin
                width: parent.width * 0.45 - Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                text: model.k
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
            }

            Label {
                id: valueLabel
                visible: model.kind === "row"
                x: parent.width * 0.45
                width: parent.width * 0.55 - Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                text: model.v
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.primaryColor
            }
        }

        VerticalScrollDecorator { }
    }

    BusyIndicator {
        id: busy
        anchors.centerIn: parent
        size: BusyIndicatorSize.Medium
        running: false
    }
}
