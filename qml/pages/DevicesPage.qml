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

    // Modell und Seriennummer nachfragen, sonst bleiben sie leer
    Component.onCompleted: if (tv.registered) tv.requestSystemInfo()

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

            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Edit")
                    onClicked: pageStack.push(Qt.resolvedUrl("DeviceEditPage.qml"),
                                              { window: page.window, index: index })
                }
                MenuItem {
                    text: qsTr("Remove")
                    enabled: page.window.devices.length > 1
                    onClicked: page.window.removeDevice(index)
                }
            }

            Column {
                id: zeilen
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter

                Label {
                    text: item.dev ? item.dev.name : ""
                    color: index === page.window.currentIndex ? Theme.highlightColor
                                                              : Theme.primaryColor
                    truncationMode: TruncationMode.Fade
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
                page.window.selectDevice(index)
                pageStack.pop()
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
