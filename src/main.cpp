#include <kddockwidgets/Config.h>
#include <kddockwidgets/DockWidgetQuick.h>
#include <kddockwidgets/private/DockRegistry_p.h>
#include <kddockwidgets/FrameworkWidgetFactory.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "ui/register/register.h"


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    KDDockWidgets::Config::self().setQmlEngine(&engine);

    // Create a test object
    QObject *test_obj;
    QString test_obj_name = QString::fromStdString("Test");

    Pretzel::Ui::registerObject(test_obj_name, test_obj);

    const QUrl url("qrc:/ui/main.qml");
    engine.load(url);

    return app.exec();
}

