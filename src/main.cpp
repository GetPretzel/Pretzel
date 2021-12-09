#include <kddockwidgets/Config.h>
#include <kddockwidgets/DockWidgetQuick.h>
#include <kddockwidgets/private/DockRegistry_p.h>
#include <kddockwidgets/FrameworkWidgetFactory.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QString>
#include <QObject>
#include <QDebug>

#include "framework/actions/actioncontroller.h"

#include "ui/register/register.h"


void printHello() {
    qDebug() << "Hello";
}


int main(int argc, char *argv[]) {
    // QApplication app(argc, argv);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    KDDockWidgets::Config::self().setQmlEngine(&engine);

    qmlRegisterType<Pretzel::Framework::Action>("Pretzel.Framework", 1, 0, "Action");

    Pretzel::Framework::ActionController *actionController = new Pretzel::Framework::ActionController();
    
    QString printHelloName("hello");
    Pretzel::Framework::Action printHelloAction;
    QObject scrapObj;
    QObject::connect(&printHelloAction, &Pretzel::Framework::Action::triggered, &scrapObj, &printHello);
    actionController->addAction(&printHelloAction);

    QString actionControllerName("ActionController");
    Pretzel::Ui::registerObject(engine.rootContext(), actionControllerName, actionController);

    const QUrl url("qrc:/ui/main.qml");
    engine.load(url);

    return app.exec();
}

