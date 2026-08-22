import QtQuick 2.0
import Sailfish.Silica 1.0

/* Systemdaten des Fernsehers. Aufruf ueber das Menue, nicht als
   Karussellseite - dort stoerte sie beim Durchblaettern. */
Page {
    id: panel

    property var tv
    property var window

    allowedOrientations: Orientation.Portrait

    ListModel { id: rows }

    // Die Antworten treffen in beliebiger Reihenfolge ein, die Gliederung
    // steht fest - jede Zeile wird in ihren Abschnitt einsortiert
    readonly property var sections: [qsTr("Device"), qsTr("Network"),
                                     qsTr("Open ports"), qsTr("Sound and ARC"),
                                     qsTr("Inputs")]

    function sectionAt(title) {
        for (var i = 0; i < rows.count; i++)
            if (rows.get(i).kind === "section" && rows.get(i).k === title)
                return i
        var rang = sections.indexOf(title)
        for (var j = 0; j < rows.count; j++) {
            var r = rows.get(j)
            if (r.kind === "section" && sections.indexOf(r.k) > rang) {
                rows.insert(j, { "kind": "section", "k": title, "v": "" })
                return j
            }
        }
        rows.append({ "kind": "section", "k": title, "v": "" })
        return rows.count - 1
    }

    // Zeile an den Anfang ihres Abschnitts, egal wann sie eintrifft
    function addRowTop(section, k, v) {
        rows.insert(sectionAt(section) + 1, { "kind": "row", "k": k, "v": String(v) })
    }

    function addRow(section, k, v) {
        var ende = sectionAt(section) + 1
        while (ende < rows.count && rows.get(ende).kind !== "section")
            ende++
        rows.insert(ende, { "kind": "row", "k": k, "v": String(v) })
    }

    function addMap(section, map) {
        for (var key in map) addRow(section, key, map[key])
    }

    function reload() {
        rows.clear()
        busy.running = true

        // Die Adresse gehoert zum Netz, nicht zum Geraet
        addRow(qsTr("Network"), qsTr("Address"), panel.tv.host)

        if (!panel.tv.registered) {
            addRow(qsTr("Device"), qsTr("State"), qsTr("not connected"))
            busy.running = false
            return
        }

        panel.tv.requestTlsInfo()
        panel.tv.requestSystemInfo()
        panel.tv.requestSoftwareInfo()
        panel.tv.requestNetworkInfo()
        panel.tv.requestAudioStatus()
        panel.tv.requestInputs()
        scanner.scan(panel.tv.host)
    }

    Connections {
        target: tv
        // Modell, Seriennummer, Tuner und die Firmware beschreiben das Geraet
        onSystemInfoReceived: panel.addMap(qsTr("Device"), info)
        onTunerReceived: panel.addRowTop(qsTr("Inputs"), qsTr("Tuner"), type)
        onSoftwareInfoReceived: panel.addMap(qsTr("Device"), info)
        onNetworkInfoReceived: panel.addMap(qsTr("Network"), info)
        onAudioStatusReceived: panel.addMap(qsTr("Sound and ARC"), info)
        // Kommt zuletzt und steht damit unten im Abschnitt Netzwerk
        onTlsInfoChanged: panel.addRow(qsTr("Network"), qsTr("Encryption"),
                                       panel.tv.tlsVersion)
        onInputsReceived: {
            for (var i = 0; i < inputs.length; i++)
                panel.addRow(qsTr("Inputs"), inputs[i].label, inputs[i].ident)
        }
    }

    Connections {
        target: scanner
        onResult: if (open) panel.addRow(qsTr("Open ports"), port + "  " + service,
                                         qsTr("open"))
        onFinished: busy.running = false
    }
    Component.onCompleted: reload()

    SilicaListView {
        id: list
        anchors.fill: parent
        model: rows
        flickableDirection: Flickable.VerticalFlick

        header: PageHeader { title: qsTr("System data") }

        PullDownMenu {
            MenuItem {
                text: qsTr("Reload")
                onClicked: panel.reload()
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
