#include <kddockwidgets/Config.h>
#include <kddockwidgets/DockWidgetQuick.h>
#include <kddockwidgets/private/DockRegistry_p.h>
#include <kddockwidgets/FrameworkWidgetFactory.h>

#include <QAction>
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QString>
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
    
    Pretzel::Framework::ActionController *actionController = new Pretzel::Framework::ActionController();
    
    QString printHelloName("hello");
    QAction printHelloQAction(printHelloName);
    // connect(printHelloQAction, &QAction::triggered, this, &printHello);
    Pretzel::Framework::Action printHelloAction = {printHelloName, &printHelloQAction};
    actionController->addAction(&printHelloAction);

    QString actionControllerName("ActionController");
    Pretzel::Ui::registerObject(engine.rootContext(), actionControllerName, actionController);

    const QUrl url("qrc:/ui/main.qml");
    engine.load(url);

    return app.exec();
}

