import QtQuick 2.0
import Sailfish.Silica 1.0

// Taste der Fernbedienung; blank=true ist eine Luecke im Raster
MouseArea {
    id: key

    property string text: ""
    property string icon: ""
    property bool blank: false
    property bool wide: false
    property real size: Theme.itemSizeLarge
    property real fontSize: Theme.fontSizeExtraLarge
    property bool round: false

    /* repeatable: langes Halten loest wiederholt aus. Die Lautstaerke
       braucht dabei mehr Abstand, weil CEC langsamer ist. */
    property bool repeatable: false
    property int repeatInterval: 300
    signal activated()

    width: wide ? size * 1.7 : size
    height: size
    enabled: !blank

    onPressed: if (repeatable) { key.activated(); repeatDelay.restart() }
    onReleased: { repeatDelay.stop(); repeatTimer.stop() }
    onCanceled: { repeatDelay.stop(); repeatTimer.stop() }

    // Erst nach einer kurzen Pause wiederholen, sonst feuert jeder Tipper zweimal
    Timer {
        id: repeatDelay
        interval: 500
        onTriggered: repeatTimer.start()
    }

    Timer {
        id: repeatTimer
        interval: key.repeatInterval
        repeat: true
        onTriggered: key.activated()
    }

    Rectangle {
        anchors.fill: parent
        visible: !key.blank
        radius: key.round ? width / 2 : Theme.paddingMedium
        color: key.pressed ? Theme.rgba(Theme.highlightBackgroundColor, 0.55)
                           : Theme.rgba(Theme.primaryColor, 0.10)
        border.width: 1
        border.color: Theme.rgba(Theme.primaryColor, 0.22)
    }

    // Bild in der Groesse einer Textzeile, sitzt wie ein Zeichen
    HighlightImage {
        anchors.centerIn: parent
        visible: !key.blank && key.icon !== ""
        width: key.fontSize
        height: width * 1.257
        sourceSize.width: width
        sourceSize.height: height
        source: key.icon
        color: Theme.primaryColor
        highlighted: key.pressed
    }

    Label {
        anchors.centerIn: parent
        visible: !key.blank && key.icon === ""
        text: key.text
        font.pixelSize: key.wide ? Theme.fontSizeSmall : key.fontSize
        color: key.pressed ? Theme.highlightColor : Theme.primaryColor
    }
}
