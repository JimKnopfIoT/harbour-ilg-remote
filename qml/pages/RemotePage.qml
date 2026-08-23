import QtQuick 2.0
import Sailfish.Silica 1.0

/* Drei Seiten als Karussell. PathView statt ListView, weil nur der einen
   Ringschluss beherrscht. */
Page {
    id: page

    property var tv
    property var window

    allowedOrientations: Orientation.Portrait

    /* Die PathView baut ihre Bahn neu auf, sobald die Seite verdeckt und
       wieder freigegeben wird - und steht dann wieder auf der ersten Seite.
       Wer von der Kachelseite aus eine App auswaehlt, will aber dorthin
       zurueck, wo er hergekommen ist. Also selbst merken. */
    property int gemerkteSeite: 0

    onStatusChanged: {
        if (status === PageStatus.Deactivating)
            gemerkteSeite = carousel.currentIndex
        else if ((status === PageStatus.Activating || status === PageStatus.Active)
                 && carousel.currentIndex !== gemerkteSeite)
            carousel.positionViewAtIndex(gemerkteSeite, PathView.Center)
    }

    PathView {
        id: carousel
        anchors.fill: parent

        model: 3
        pathItemCount: 3
        snapMode: PathView.SnapOneItem
        highlightRangeMode: PathView.StrictlyEnforceRange
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        // Wischen soll seitenweise umschalten, nicht durchrutschen
        flickDeceleration: 5000
        maximumFlickVelocity: width * 4

        // Beim Wechsel auf den Ziffernblock den laufenden Kanal nachfragen
        onCurrentIndexChanged: if (currentIndex === 1 && page.tv.registered)
                                   page.tv.refreshChannel()

        /* Seitenabstand = Bahnlaenge / pathItemCount. Fuer genau eine Seite
           je Bild muss die Bahn Bildbreite mal Seitenzahl lang sein. */
        path: Path {
            startX: carousel.width / 2 - carousel.width * carousel.count / 2
            startY: carousel.height / 2
            PathLine {
                x: carousel.width / 2 + carousel.width * carousel.count / 2
                y: carousel.height / 2
            }
        }

        delegate: Loader {
            width: carousel.width
            height: carousel.height
            sourceComponent: index === 0 ? mainPanel
                           : index === 1 ? numberPanel
                                         : padPanel
        }

        Component { id: mainPanel;   PanelMain    { tv: page.tv; window: page.window } }
        Component { id: numberPanel; PanelNumbers { tv: page.tv; window: page.window } }
        Component { id: padPanel;    PanelPad     { tv: page.tv; window: page.window
                                                  current: carousel.currentIndex === 2 } }
    }

    // Seitenanzeige, damit erkennbar ist, wo man sich befindet
    Row {
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: Theme.paddingMedium
        }
        spacing: Theme.paddingSmall

        Repeater {
            model: 3

            /* Reine Anzeige: die Punkte liegen unter dem Textfeld der
               Zeigerseite, ein Fehlgriff wuerde die Seite wechseln. */
            Rectangle {
                width: Theme.paddingSmall
                height: width
                radius: width / 2
                color: carousel.currentIndex === index ? Theme.highlightColor
                                                       : Theme.rgba(Theme.primaryColor, 0.25)
            }
        }
    }

}
