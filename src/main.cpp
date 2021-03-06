#include <kddockwidgets/Config.h>
#include <kddockwidgets/DockWidgetQuick.h>
#include <kddockwidgets/private/DockRegistry_p.h>
#include <kddockwidgets/FrameworkWidgetFactory.h>

#include <QEvent>
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QString>
#include <QObject>
#include <QMetaType>
#include <QDebug>
#include <QVariantList>

#include "framework/actions/actioncontroller.h"
// #include "framework/actions/papplication.h"
#include "framework/database/databasehost.h"
#include "framework/models/itemsmodel.h"
#include "framework/models/itempropertiesmodel.h"
#include "framework/models/profilesmodel.h"
#include "framework/models/propertiesmodel.h"
#include "framework/models/stockmodel.h"
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
    // TODO: Add a custom application class based on QGuiApplication
    // Pretzel::Framework::Application::PApplication app(argc, argv);
    // TODO: Why does the white on the icon render as brown when using SVG here?
    // TODO: Does ICO render on all platforms?
    app.setWindowIcon(QIcon(":/assets/icon.ico"));

    QQmlApplicationEngine engine;
    auto &config = KDDockWidgets::Config::self();
    config.setFlags(KDDockWidgets::Config::Flag_Default | KDDockWidgets::Config::Flag_AllowReorderTabs);
    config.setQmlEngine(&engine);

    // Initialize the database
    Pretzel::Framework::Database::DatabaseHost databaseHost;
    databaseHost.init();

    // Register the types
    qRegisterMetaType<Pretzel::Framework::Action*>("Action*");
    qmlRegisterType<Pretzel::Framework::Models::ItemsModel>("Pretzel.Framework", 1, 0, "ItemsModel");
    qmlRegisterType<Pretzel::Framework::Models::ItemPropertiesModel>("Pretzel.Framework", 1, 0, "ItemPropertiesModel");
    qmlRegisterType<Pretzel::Framework::Models::ProfilesModel>("Pretzel.Framework", 1, 0, "ProfilesModel");
    qmlRegisterType<Pretzel::Framework::Models::PropertiesModel>("Pretzel.Framework", 1, 0, "PropertiesModel");
    qmlRegisterType<Pretzel::Framework::Models::StockModel>("Pretzel.Framework", 1, 0, "StockModel");

    Pretzel::Framework::ActionController *actionController = new Pretzel::Framework::ActionController();

    Pretzel::Framework::Action* printHelloAction = new Pretzel::Framework::Action();
    printHelloAction->setName("hello");
    // printHelloAction->connect(&printHello);
    QObject::connect(printHelloAction, &Pretzel::Framework::Action::triggered, printHelloAction, &printHello);
    actionController->addAction(printHelloAction);

    Pretzel::Ui::registerObject(engine.rootContext(), "ActionController", actionController);
    Pretzel::Ui::registerObject(engine.rootContext(), "DatabaseHost", &databaseHost);

    engine.addImportPath("qrc:/ui/components/qml");
    engine.addImportPath("qrc:/ui/delegates/qml");
    engine.addImportPath("qrc:/ui/docks/qml");

    const QUrl url("qrc:/ui/main.qml");
    engine.load(url);

    return app.exec();
}

