#include <QtQuick>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QScopedPointer>
#include <sailfishapp.h>

#include "discovery.h"
#include "errorlog.h"
#include "lgtv.h"
#include "portscan.h"
#include "tvicons.h"
#include "wol.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));

    qmlRegisterType<LgTv>("harbour.lgremote", 1, 0, "LgTv");

    QScopedPointer<QQuickView> view(SailfishApp::createView());

    /* Das Fehlerprotokoll steht ueberall zur Verfuegung und ist im Normalfall
       leer - jeder Eintrag ist eine Zusage, die nicht eingehalten wurde. */
    view->rootContext()->setContextProperty(QStringLiteral("errorLog"), ErrorLog::instance());

    // Die Engine uebernimmt den Anbieter, die Zeigerkopie bleibt fuer QML
    TvIcons *icons = new TvIcons;
    view->engine()->addImageProvider(QStringLiteral("tvicon"), icons);
    view->rootContext()->setContextProperty(QStringLiteral("icons"), icons);

    Wol wol;
    view->rootContext()->setContextProperty(QStringLiteral("Wol"), &wol);

    PortScan scanner;
    view->rootContext()->setContextProperty(QStringLiteral("scanner"), &scanner);

    Discovery discovery;
    view->rootContext()->setContextProperty(QStringLiteral("discovery"), &discovery);

    view->setSource(SailfishApp::pathToMainQml());
    view->show();

    return app->exec();
}
