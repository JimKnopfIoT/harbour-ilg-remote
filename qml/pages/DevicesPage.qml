import QtQuick 2.0
import Sailfish.Silica 1.0

/* Geraeteverwaltung: gespeicherte Fernseher auswaehlen, neue per Suche im
   Netz oder von Hand aufnehmen. */
Page {
    id: page

    property var tv
    property var window

    allowedOrientations: Orientation.Portrait

    ListModel { id: foundModel }

    /* Erreichbarkeit je Adresse: "" unbekannt, "an" nimmt Verbindungen an,
       "aus" antwortet nicht. Ein Fernseher im Bereitschaftsbetrieb steht
       weiter in der Liste - er ist ja nicht verschwunden, nur still. */
    property var reachable: ({})
    // Auskunft nach einem Tipp auf ein stilles Geraet
    property string hinweis: ""

    function refreshState() {
        hinweis = ""
        var m = {}
        for (var i = 0; i < window.devices.length; i++) {
            var h = window.devices[i].host
            if (!h || h.length === 0) continue
            m[h] = ""
            scanner.probe(h)
        }
        reachable = m
    }

    Connections {
        target: scanner
        onReachable: {
            var m = page.reachable
            m[host] = up ? "an" : "aus"
            page.reachable = m
        }
    }

    // Modell und Seriennummer nachfragen, sonst bleiben sie leer
    Component.onCompleted: {
        if (tv.registered) tv.requestSystemInfo()
        refreshState()
    }

    property bool searched: false

    Connections {
        target: discovery
        onFound: {
            // Schon gespeicherte Geraete nicht noch einmal anbieten
            for (var i = 0; i < page.window.devices.length; i++)
                if (page.window.devices[i].host === host) return
            for (var j = 0; j < foundModel.count; j++)
                if (foundModel.get(j).host === host) return
            foundModel.append({ "host": host, "name": name })
        }
    }

    SilicaListView {
        id: list
        anchors.fill: parent
        model: page.window.devices.length

        header: Column {
            width: list.width

            PageHeader { title: qsTr("Devices") }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("Tapping switches to the device. The pairing key is stored per device, so switching needs no new confirmation.")
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                visible: page.hinweis.length > 0
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryHighlightColor
                text: page.hinweis
            }

            Item { width: 1; height: Theme.paddingLarge }
        }

        PullDownMenu {
            // Von Hand trennen und verbinden braucht man selten
            MenuItem {
                text: page.tv.linkUp ? qsTr("Disconnect") : qsTr("Connect")
                onClicked: page.tv.linkUp ? page.tv.disconnectTv() : page.tv.connectTv()
            }
            MenuItem {
                text: discovery.running ? qsTr("Searching ...") : qsTr("Search the network")
                enabled: !discovery.running
                onClicked: { foundModel.clear(); page.searched = true; discovery.start() }
            }
            MenuItem {
                text: qsTr("Check availability")
                onClicked: page.refreshState()
            }
            MenuItem {
                text: qsTr("Add device manually")
                onClicked: pageStack.push(Qt.resolvedUrl("DeviceEditPage.qml"),
                                          { window: page.window, index: -1 })
            }
        }

        delegate: ListItem {
            id: item
            width: list.width
            contentHeight: Math.max(Theme.itemSizeMedium,
                                    zeilen.height + 2 * Theme.paddingMedium)

            property var dev: page.window.devices[index]
            // Modell und Seriennummer kennt nur der Fernseher, an dem wir haengen
            property bool aktiv: index === page.window.currentIndex && page.tv.registered

            /* Der Anschluss auf Port 3001 antwortet auch im Netzwerk-Standby.
               "erreichbar" ist deshalb nur die halbe Auskunft: an ist der
               Fernseher erst, wenn er es selbst sagt - und das sagt er nur dem,
               mit dem er verbunden ist. */
            property string erreichbar: (dev && dev.host && page.reachable[dev.host])
                                        ? page.reachable[dev.host] : ""
            /* Nennt der Fernseher seinen Zustand nicht, gilt wie beim
               Ein-/Aus-Knopf das alte Bild: verbunden heisst an. Lieber die
               gewohnte Auskunft als eine erfundene Bereitschaft. */
            property string zustand: erreichbar === "" ? ""
                                   : erreichbar === "aus" ? "aus"
                                   : !aktiv ? "erreichbar"
                                   : page.tv.powerUnknown ? "an"
                                   : page.tv.awake ? "an" : "standby"

            /* Der erste Eintrag ist leer und tut nichts: wer das Menue
               oeffnet und den Finger hebt, soll nicht versehentlich eine
               Kopplung loesen. */
            menu: ContextMenu {
                MenuItem { text: "" }
                MenuItem {
                    text: qsTr("Edit")
                    onClicked: pageStack.push(Qt.resolvedUrl("DeviceEditPage.qml"),
                                              { window: page.window, index: index })
                }
                MenuItem {
                    text: qsTr("Reset pairing")
                    enabled: item.dev && ((item.dev.key && item.dev.key.length > 0)
                                          || (item.dev.cert && item.dev.cert.length > 0))
                    onClicked: {
                        page.window.resetPairing(index)
                        page.hinweis = qsTr("Pairing released. Tapping the device connects again - the TV then asks once more.")
                    }
                }
                MenuItem {
                    text: qsTr("Forget device")
                    onClicked: remorseAction(qsTr("Forgetting"),
                                             function () { page.window.removeDevice(index) })
                }
            }

            Column {
                id: zeilen
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter

                Row {
                    spacing: Theme.paddingSmall

                    Rectangle {
                        anchors.verticalCenter: parent.verticalCenter
                        width: Theme.fontSizeSmall / 2
                        height: width
                        radius: width / 2
                        color: item.zustand === "an" ? "#4caf50"
                             : item.zustand === "aus" ? "#e53935"
                             : item.zustand === "" ? Theme.rgba(Theme.primaryColor, 0.3)
                                                   : "#ff9800"
                    }

                    Label {
                        id: nameLabel
                        text: item.dev ? item.dev.name : ""
                        color: index === page.window.currentIndex ? Theme.highlightColor
                                                                  : Theme.primaryColor
                        truncationMode: TruncationMode.Fade
                    }

                    Label {
                        anchors.baseline: nameLabel.baseline
                        text: item.zustand === "an" ? qsTr("on")
                            : item.zustand === "standby" ? qsTr("standby · reachable")
                            : item.zustand === "erreichbar" ? qsTr("reachable")
                            : item.zustand === "aus" ? qsTr("off") : ""
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: Theme.secondaryColor
                    }
                }
                Label {
                    visible: item.aktiv && page.tv.model.length > 0
                    text: item.aktiv ? page.tv.model
                          + (page.tv.serial.length > 0 ? "  ·  " + page.tv.serial : "") : ""
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.secondaryColor
                    truncationMode: TruncationMode.Fade
                }
                Label {
                    text: item.dev ? (item.dev.host
                          + (item.dev.mac && item.dev.mac.length > 0 ? "  ·  " + item.dev.mac : "")
                          + (item.dev.key && item.dev.key.length > 0 ? qsTr("  ·  paired") : "")) : ""
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.secondaryColor
                    truncationMode: TruncationMode.Fade
                }
            }

            onClicked: {
                /* Ausgewaehlt wird trotzdem - nur so zielt das Weckpaket auf
                   dieses Geraet. Aber wortlos auf die Fernbedienung springen,
                   wo dann nichts geht, waere die schlechtere Auskunft. */
                page.window.selectDevice(index)
                if (item.zustand === "aus") {
                    page.tv.note(qsTr("Not available, offline"))
                    page.hinweis = qsTr("%1 does not answer. It is disconnected from the mains or network standby is switched off - the power key on the first page sends the wake-up signal anyway.").arg(item.dev.name)
                    return
                }
                /* Tippen fuehrt zu den Systemdaten des Geraets, nicht zur
                   Fernbedienung: hier steht, woran man ist. Zur Fernbedienung
                   kommt man mit dem Zurueckwischen. */
                pageStack.push(Qt.resolvedUrl("SystemPage.qml"),
                               { tv: page.tv, window: page.window })
            }
        }

        footer: Column {
            width: list.width
            visible: page.searched || foundModel.count > 0

            SectionHeader { text: qsTr("Found on the network") }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                visible: page.searched && !discovery.running && foundModel.count === 0
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("Nothing found. A TV in standby does not answer - switch it on and search again, or add it manually.")
            }

            BusyIndicator {
                anchors.horizontalCenter: parent.horizontalCenter
                size: BusyIndicatorSize.Medium
                running: discovery.running
                visible: running
            }

            Repeater {
                model: foundModel
                ListItem {
                    width: list.width
                    contentHeight: Theme.itemSizeMedium

                    Column {
                        x: Theme.horizontalPageMargin
                        width: parent.width - 2 * Theme.horizontalPageMargin
                        anchors.verticalCenter: parent.verticalCenter

                        Label { text: model.name; truncationMode: TruncationMode.Fade }
                        Label {
                            text: model.host + qsTr("  ·  tap to add")
                            font.pixelSize: Theme.fontSizeExtraSmall
                            color: Theme.secondaryColor
                        }
                    }

                    onClicked: {
                        // MAC bleibt leer - sie laesst sich erst nach dem
                        // Verbinden beim Fernseher erfragen
                        var i = page.window.addDevice(model.name, model.host, "")
                        foundModel.remove(index)
                        page.window.selectDevice(i)
                        pageStack.pop()
                    }
                }
            }
        }

        ViewPlaceholder {
            enabled: page.window.devices.length === 0
            text: qsTr("No device")
            hintText: qsTr("Search from the menu or add one manually")
        }

        VerticalScrollDecorator { }
    }
}
