#include <QtQuick>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QScopedPointer>
#include <sailfishapp.h>

#include "discovery.h"
#include "lgtv.h"
#include "portscan.h"
#include "wol.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));

    qmlRegisterType<LgTv>("harbour.lgremote", 1, 0, "LgTv");

    QScopedPointer<QQuickView> view(SailfishApp::createView());

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
