#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include "colormaker.h"

int main(int argc,char *argv[])
{
    QGuiApplication app(argc,argv);
    qmlRegisterType<colorMaker>("an.qt.colorMaker",1,0,"ColorMaker");

    QQuickView viewer;
    QObject::connect(viewer.engine(), SIGNAL(quit()), &app,SLOT(quit()));

    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl(":/main.qml"));
    viewer.show();
    return app.exec();
}
