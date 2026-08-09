import QtQuick 2.0
import Sailfish.Silica 1.0

/*
 * Drei Seiten als Karussell: Fernbedienung, Zahlenblock, Zeigerflaeche.
 * PathView statt ListView, weil nur der einen Ringschluss beherrscht - nach
 * der dritten Seite kommt wieder die erste.
 */
Page {
    id: page

    property var tv
    property var window

    allowedOrientations: Orientation.All

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

        /* Der Abstand zweier Seiten ist Bahnlaenge geteilt durch
           pathItemCount. Damit genau eine Seite das Bild fuellt, muss die
           Bahn also Bildbreite mal Seitenzahl lang sein - sonst schaut die
           Nachbarseite herein. Mittelpunkt der Bahn auf die Bildmitte legen. */
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
        Component { id: padPanel;    PanelPad     { tv: page.tv; window: page.window } }
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

            /* Reine Anzeige, nicht bedienbar: die Punkte liegen unter dem
               Textfeld der Zeigerseite, und ein Fehlgriff dorthin wuerde
               ungewollt die Seite wechseln. Zum Blaettern gibt es den
               Wischstreifen. */
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
