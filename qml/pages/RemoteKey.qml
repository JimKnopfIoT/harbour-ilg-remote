import QtQuick 2.0
import Sailfish.Silica 1.0

/* Eine Taste der Fernbedienung. blank=true erzeugt eine unsichtbare
   Luecke, damit sich das Steuerkreuz sauber im Raster anordnen laesst. */
MouseArea {
    id: key

    property string text: ""
    property bool blank: false
    property bool wide: false
    property real size: Theme.itemSizeLarge
    property real fontSize: Theme.fontSizeExtraLarge
    property bool round: false

    /* Bei repeatable loest langes Halten wiederholt aus - fuer Lautstaerke
       und Kanal, wo man selten nur einen Schritt will. Die Lautstaerke braucht
       einen groesseren Abstand, weil der Fernseher jeden Schritt per CEC an
       das Tongeraet weiterreicht und das langsamer ist. */
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

    Label {
        anchors.centerIn: parent
        visible: !key.blank
        text: key.text
        font.pixelSize: key.wide ? Theme.fontSizeSmall : key.fontSize
        color: key.pressed ? Theme.highlightColor : Theme.primaryColor
    }
}
