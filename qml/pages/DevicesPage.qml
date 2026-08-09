import QtQuick 2.0
import Sailfish.Silica 1.0

/* Geraeteverwaltung: gespeicherte Fernseher auswaehlen, neue per Suche im
   Netz oder von Hand aufnehmen. */
Page {
    id: page

    property var tv
    property var window

    allowedOrientations: Orientation.All

    ListModel { id: foundModel }

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

            PageHeader { title: "Geräte" }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: "Antippen wechselt zum Gerät. Der Kopplungsschlüssel wird je " +
                      "Gerät gespeichert – ein Wechsel verlangt also keine neue Bestätigung."
            }

            Item { width: 1; height: Theme.paddingLarge }
        }

        PullDownMenu {
            MenuItem {
                text: discovery.running ? "Suche läuft ..." : "Fernseher im Netz suchen"
                enabled: !discovery.running
                onClicked: { foundModel.clear(); discovery.start() }
            }
            MenuItem {
                text: "Gerät von Hand hinzufügen"
                onClicked: pageStack.push(Qt.resolvedUrl("DeviceEditPage.qml"),
                                          { window: page.window, index: -1 })
            }
        }

        delegate: ListItem {
            id: item
            width: list.width
            contentHeight: Theme.itemSizeMedium

            property var dev: page.window.devices[index]

            menu: ContextMenu {
                MenuItem {
                    text: "Bearbeiten"
                    onClicked: pageStack.push(Qt.resolvedUrl("DeviceEditPage.qml"),
                                              { window: page.window, index: index })
                }
                MenuItem {
                    text: "Entfernen"
                    enabled: page.window.devices.length > 1
                    onClicked: page.window.removeDevice(index)
                }
            }

            Column {
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
                    text: item.dev ? (item.dev.host
                          + (item.dev.key && item.dev.key.length > 0 ? "  ·  gekoppelt" : "")) : ""
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.secondaryColor
                }
            }

            onClicked: {
                page.window.selectDevice(index)
                pageStack.pop()
            }
        }

        footer: Column {
            width: list.width
            visible: foundModel.count > 0 || discovery.running

            SectionHeader { text: "Im Netz gefunden" }

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
                            text: model.host + "  ·  antippen zum Übernehmen"
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
            text: "Kein Gerät"
            hintText: "Über das Menü suchen oder von Hand hinzufügen"
        }

        VerticalScrollDecorator { }
    }
}
