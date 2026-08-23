import QtQuick 2.0
import Sailfish.Silica 1.0

/* Fehlerprotokoll. Leer ist der Normalfall - jeder Eintrag steht fuer eine
   Zusage, die die App nicht eingehalten hat. Wer meldet "es geht nicht", kann
   hier nachsehen, statt zu raten. */
Page {
    id: page

    allowedOrientations: Orientation.Portrait

    SilicaListView {
        id: list
        anchors.fill: parent
        model: errorLog

        header: Column {
            width: list.width

            PageHeader { title: qsTr("Error log") }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("Everything the app promised and could not deliver ends up here: a wake-up signal without a MAC address, a key without a key channel, an icon the TV would not hand out. Newest first. The log lives in memory only and is gone when the app closes.")
            }

            Item { width: 1; height: Theme.paddingLarge }
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("Copy to clipboard")
                enabled: errorLog.count > 0
                onClicked: Clipboard.text = errorLog.asText()
            }
            MenuItem {
                text: qsTr("Clear")
                enabled: errorLog.count > 0
                onClicked: errorLog.clear()
            }
        }

        delegate: Item {
            width: list.width
            height: zeilen.height + Theme.paddingMedium

            Column {
                id: zeilen
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                y: Theme.paddingSmall

                Label {
                    width: parent.width
                    text: model.area + (model.repeat > 1 ? "  ·  " + model.repeat + "×" : "")
                          + "  ·  " + model.when
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.highlightColor
                    truncationMode: TruncationMode.Fade
                }

                Label {
                    width: parent.width
                    text: model.text
                    wrapMode: Text.Wrap
                    font.pixelSize: Theme.fontSizeSmall
                }

                Label {
                    width: parent.width
                    visible: model.detail.length > 0
                    text: model.detail
                    wrapMode: Text.Wrap
                    font.pixelSize: Theme.fontSizeExtraSmall
                    color: Theme.secondaryColor
                }
            }
        }

        ViewPlaceholder {
            enabled: errorLog.count === 0
            text: qsTr("Nothing to report")
            hintText: qsTr("That is the normal case: everything the app started, it finished.")
        }

        VerticalScrollDecorator { }
    }
}
