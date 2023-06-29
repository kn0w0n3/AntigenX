#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "maincontroller.h"
#include "database.h"
#include <QQmlContext>
#include <QApplication>

int main(int argc, char *argv[]){

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    //qmlRegisterType<MainController>("com.company.maincontroller",1,0,"Maincontroller");
    QQmlApplicationEngine engine;
    MainController mainController;
    Database database;
    engine.rootContext()->setContextProperty("mainController", &mainController);
    engine.rootContext()->setContextProperty("database", &database);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);
    app.setWindowIcon(QIcon(":/images/antigenx_icon.png"));
    return app.exec();
}
