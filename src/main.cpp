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
#include <QVariantList>

#include "framework/actions/actioncontroller.h"
#include "framework/database/databasehost.h"
#include "framework/models/itemsmodel.h"
#include "framework/models/profilesmodel.h"
#include "framework/models/propertiesmodel.h"
#include "ui/register/register.h"


void printHello(QVariantList args) {
    if (args.length() > 0) {
        qDebug() << "Hello" << args.at(0).toInt();
    } else {
        qDebug() << "Hello";
    }
}


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    KDDockWidgets::Config::self().setQmlEngine(&engine);

    // Initialize the database
    Pretzel::Framework::Database::DatabaseHost databaseHost;
    databaseHost.init();

    // Register the types
    qRegisterMetaType<Pretzel::Framework::Action*>("Action*");
    qmlRegisterType<Pretzel::Framework::Models::ItemsModel>("Pretzel.Framework", 1, 0, "ItemsModel");
    qmlRegisterType<Pretzel::Framework::Models::ProfilesModel>("Pretzel.Framework", 1, 0, "ProfilesModel");
    qmlRegisterType<Pretzel::Framework::Models::PropertiesModel>("Pretzel.Framework", 1, 0, "PropertiesModel");

    Pretzel::Framework::ActionController *actionController = new Pretzel::Framework::ActionController();

    Pretzel::Framework::Action* printHelloAction = new Pretzel::Framework::Action();
    printHelloAction->setName("hello");
    QObject::connect(printHelloAction, &Pretzel::Framework::Action::triggered, printHelloAction, &printHello);
    actionController->addAction(printHelloAction);

    Pretzel::Ui::registerObject(engine.rootContext(), "ActionController", actionController);

    engine.addImportPath("qrc:/ui/components/qml");
    engine.addImportPath("qrc:/ui/delegates/qml");
    engine.addImportPath("qrc:/ui/docks/qml");

    const QUrl url("qrc:/ui/main.qml");
    engine.load(url);

    return app.exec();
}

