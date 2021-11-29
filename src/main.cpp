#include <kddockwidgets/Config.h>
#include <kddockwidgets/DockWidgetQuick.h>
#include <kddockwidgets/private/DockRegistry_p.h>
#include <kddockwidgets/FrameworkWidgetFactory.h>

#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    KDDockWidgets::Config::self().setQmlEngine(&engine);

    const QUrl url("qrc:/ui/main.qml");
    engine.load(url);

    return app.exec();
}

