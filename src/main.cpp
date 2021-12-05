#include <kddockwidgets/Config.h>
#include <kddockwidgets/DockWidgetQuick.h>
#include <kddockwidgets/private/DockRegistry_p.h>
#include <kddockwidgets/FrameworkWidgetFactory.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>
#include <QString>

#include "framework/actions/actioncontroller.h"

#include "ui/register/register.h"


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    KDDockWidgets::Config::self().setQmlEngine(&engine);

    QString actionControllerName("ActionController");
    Pretzel::Framework::ActionController *actionController = new Pretzel::Framework::ActionController();
    Pretzel::Ui::registerObject(actionControllerName, actionController);

    const QUrl url("qrc:/ui/main.qml");
    engine.load(url);

    return app.exec();
}

