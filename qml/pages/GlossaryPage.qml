import QtQuick 2.0
import Sailfish.Silica 1.0

/* Glossar: was die Zeichen auf den Seiten bedeuten. Ein Symbol, das erklaert
   werden muss, ist streng genommen schon ein halber Fehler - bis es besser
   gezeichnet ist, steht die Erklaerung wenigstens hier. */
Page {
    id: page

    allowedOrientations: Orientation.Portrait

    /* kind: "theme" = Symbol der Oberflaeche, "image" = eigenes Bild,
       "glyph" = Zeichen, "dot" = farbiger Punkt. */
    readonly property var eintraege: [
        { "group": qsTr("Keys"),
          "kind": "image", "src": "../images/power.png", "color": "#4caf50",
          "title": qsTr("Power"),
          "text": qsTr("Short tap sends the wake-up signal over the network (Wake-on-LAN); holding it for two seconds switches the TV off. The colour is the state of the TV, not of the connection: green running, steady orange in standby, blinking orange while connecting, red no connection.") },

        { "kind": "theme", "src": "icon-m-back", "title": qsTr("Back"),
          "text": qsTr("The back key of the remote. Goes over the key channel, like the arrow keys.") },
        { "kind": "theme", "src": "icon-m-home", "title": qsTr("Home"),
          "text": qsTr("Opens the home screen of the TV.") },
        { "kind": "theme", "src": "icon-m-about", "title": qsTr("Info"),
          "text": qsTr("Shows the programme information of the current channel.") },
        { "kind": "theme", "src": "icon-m-events", "title": qsTr("Guide"),
          "text": qsTr("Opens the programme guide.") },
        { "kind": "theme", "src": "icon-m-device", "title": qsTr("Input"),
          "text": qsTr("A short tap steps through the inputs like the input key of the original remote. Hold it to get the list of all inputs and apps and switch directly.") },
        { "kind": "theme", "src": "icon-m-setting", "title": qsTr("Settings of the TV"),
          "text": qsTr("The gear sends the MENU key and opens the settings on the TV. It is greyed out while the key channel is closed - the app's own settings are in the pull-down menu.") },

        { "group": qsTr("Text row"),
          "kind": "theme", "src": "icon-m-accept", "title": qsTr("Send text"),
          "text": qsTr("Puts the typed text into the input field open on the TV. Without a field the TV discards the text - the error log says so when that happens.") },
        { "kind": "theme", "src": "icon-m-search", "title": qsTr("Search on YouTube"),
          "text": qsTr("Hands the term to YouTube as a launch parameter. No on-screen keyboard is involved, which is why this way works even where the app draws its own keyboard.") },
        { "kind": "theme", "src": "icon-m-clear", "title": qsTr("Clear the field"),
          "text": qsTr("Empties the text field in the app - not on the TV.") },

        { "group": qsTr("Tiles"),
          "kind": "image", "src": "../images/shutter.png", "title": qsTr("Screenshot"),
          "text": qsTr("Four corners around a lens: the TV takes a picture of its own screen and the app saves it to the gallery under LG Remote. The TV refuses this while copy protection is active - a film from a streaming app usually comes out black.") },
        { "kind": "glyph", "src": "+", "title": qsTr("Free tile"),
          "text": qsTr("An empty tile. Tap it to pick an app or an input; a long press on any tile reassigns it.") },

        { "group": qsTr("Devices"),
          "kind": "dot", "src": "#4caf50", "title": qsTr("green - on"),
          "text": qsTr("The TV says so itself: it is running and can be operated. Only the TV the app is connected to can say this.") },
        { "kind": "dot", "src": "#ff9800", "title": qsTr("orange - standby or reachable"),
          "text": qsTr("The TV answers on port 3001, but it is not running: network standby. Answering is not the same as being awake, which is why this is not green. For a TV the app is not connected to, the state cannot be told apart - it then only says reachable.") },
        { "kind": "dot", "src": "#e53935", "title": qsTr("red - off"),
          "text": qsTr("No answer at all: disconnected from the mains, or network standby switched off in the TV settings. It stays in the list - the power key sends the wake-up signal, which needs the MAC address.") },
        { "kind": "glyph", "src": "⋯", "title": qsTr("tap and hold"),
          "text": qsTr("A tap switches to the device and opens its system data - there you can see what state it is in. Holding the entry opens the menu: edit, release the pairing, forget the device. Its first line is deliberately empty so that letting go does nothing.") },
        { "kind": "glyph", "src": "·", "title": qsTr("paired"),
          "text": qsTr("A pairing key for this TV is stored. Switching devices then needs no new confirmation on the screen.") },

        { "group": qsTr("Words"),
          "kind": "glyph", "src": "ARC", "title": qsTr("ARC"),
          "text": qsTr("The sound runs over the HDMI return channel to an external device. The TV then only counts steps and never learns the real volume - that is why a number would be misleading and ARC is shown instead.") },
        { "kind": "glyph", "src": "SSAP", "title": qsTr("SSAP"),
          "text": qsTr("LG's own protocol on port 3001, the same one the official remote app uses. Encrypted, with the self-signed certificate of the TV.") },
        { "kind": "glyph", "src": "WOL", "title": qsTr("Wake-on-LAN"),
          "text": qsTr("A broadcast packet that wakes the TV. It is addressed by MAC, not by IP - without the MAC address there is no switching on. The TV only names it while connected; it can also be typed in under Devices.") }
    ]

    SilicaListView {
        id: list
        anchors.fill: parent
        model: page.eintraege

        header: Column {
            width: list.width

            PageHeader { title: qsTr("Glossary") }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeExtraSmall
                color: Theme.secondaryColor
                text: qsTr("What the symbols on the pages mean.")
            }

            Item { width: 1; height: Theme.paddingLarge }
        }

        delegate: Column {
            width: list.width

            SectionHeader {
                visible: modelData.group !== undefined
                text: modelData.group !== undefined ? modelData.group : ""
            }

            Item {
                width: parent.width
                height: Math.max(zeichen.height, texte.height) + Theme.paddingMedium

                Item {
                    id: zeichen
                    x: Theme.horizontalPageMargin
                    y: Theme.paddingSmall
                    width: Theme.iconSizeMedium
                    height: Theme.iconSizeMedium

                    Image {
                        anchors.centerIn: parent
                        visible: (modelData.kind === "theme" || modelData.kind === "image")
                                 && modelData.color === undefined
                        source: modelData.kind === "theme"
                                ? "image://theme/" + modelData.src
                                : modelData.kind === "image" ? modelData.src : ""
                        width: Theme.iconSizeMedium * 0.8
                        height: width
                        fillMode: Image.PreserveAspectFit
                    }

                    HighlightImage {
                        anchors.centerIn: parent
                        visible: modelData.kind === "image" && modelData.color !== undefined
                        source: visible ? modelData.src : ""
                        width: Theme.iconSizeMedium * 0.8
                        height: width
                        sourceSize.width: width
                        sourceSize.height: height
                        fillMode: Image.PreserveAspectFit
                        color: visible ? modelData.color : Theme.primaryColor
                    }

                    Label {
                        anchors.centerIn: parent
                        visible: modelData.kind === "glyph"
                        text: modelData.kind === "glyph" ? modelData.src : ""
                        font.pixelSize: modelData.src !== undefined && modelData.src.length > 2
                                        ? Theme.fontSizeExtraSmall : Theme.fontSizeLarge
                        color: modelData.color !== undefined ? modelData.color
                                                             : Theme.highlightColor
                    }

                    Rectangle {
                        anchors.centerIn: parent
                        visible: modelData.kind === "dot"
                        width: Theme.fontSizeSmall / 2
                        height: width
                        radius: width / 2
                        color: modelData.kind === "dot" ? modelData.src : "transparent"
                    }
                }

                Column {
                    id: texte
                    x: zeichen.x + zeichen.width + Theme.paddingMedium
                    y: Theme.paddingSmall
                    width: parent.width - x - Theme.horizontalPageMargin

                    Label {
                        width: parent.width
                        text: modelData.title
                        truncationMode: TruncationMode.Fade
                    }

                    Label {
                        width: parent.width
                        text: modelData.text
                        wrapMode: Text.Wrap
                        font.pixelSize: Theme.fontSizeExtraSmall
                        color: Theme.secondaryColor
                    }
                }
            }
        }

        VerticalScrollDecorator { }
    }
}
