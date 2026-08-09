import QtQuick 2.0
import Sailfish.Silica 1.0

/* Taste mit Symbol statt Beschriftung. */
MouseArea {
    id: key

    property string icon: ""
    property string label: ""
    property real size: Theme.itemSizeLarge

    width: size
    height: size

    Rectangle {
        anchors.fill: parent
        radius: Theme.paddingMedium
        color: key.pressed ? Theme.rgba(Theme.highlightBackgroundColor, 0.55)
                           : Theme.rgba(Theme.primaryColor, 0.10)
        border.width: 1
        border.color: Theme.rgba(Theme.primaryColor, 0.22)
    }

    Column {
        anchors.centerIn: parent
        spacing: 0

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            source: key.icon ? "image://theme/" + key.icon
                               + (key.pressed ? "?" + Theme.highlightColor : "") : ""
            fillMode: Image.PreserveAspectFit
            width: key.size * 0.45
            height: width
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            visible: key.label.length > 0
            text: key.label
            font.pixelSize: Theme.fontSizeTiny
            color: Theme.secondaryColor
        }
    }
}
