#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2>
#include "maincontroller.h"
#include <QQmlContext>
#include <QApplication>

int main(int argc, char *argv[]){

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    //This had to be changed from qguiaap to qapp
    QApplication app(argc, argv);

    //qmlRegisterType<MainController>("com.company.maincontroller",1,0,"Maincontroller");
    QQmlApplicationEngine engine;  
    MainController mainController;
    engine.rootContext()->setContextProperty("maincontroller", &mainController);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    return app.exec();
}
