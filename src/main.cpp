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
#include <QMetaType>
#include <QDebug>

#include "framework/actions/actioncontroller.h"

#include "ui/register/register.h"


void printHello() {
    qDebug() << "Hello";
}


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    KDDockWidgets::Config::self().setQmlEngine(&engine);

    qRegisterMetaType<Pretzel::Framework::Action*>("Action*");

    Pretzel::Framework::ActionController *actionController = new Pretzel::Framework::ActionController();

    Pretzel::Framework::Action* printHelloAction = new Pretzel::Framework::Action();
    printHelloAction->setName("hello");
    QObject::connect(printHelloAction, &Pretzel::Framework::Action::triggered, printHelloAction, &printHello);
    actionController->addAction(printHelloAction);

    QString actionControllerName("ActionController");
    Pretzel::Ui::registerObject(engine.rootContext(), actionControllerName, actionController);

    engine.addImportPath("qrc:/ui/components/qml");

    const QUrl url("qrc:/ui/main.qml");
    engine.load(url);

    return app.exec();
}

