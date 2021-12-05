#include "register.h"


using namespace Pretzel::Ui;


// void registerFunction(QQmlApplicationEngine engine, function_type func) {
//     qmlRegisterSingletonType("Pretzel.test", 1, 0, "Functions", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> function_type {
//         Q_UNUSED(engine)
//         Q_UNUSED(scriptEngine);
//         return *func;
//     });
// }

void Pretzel::Ui::registerObject(QQmlContext *context, QString &name, QObject *object) {
    // qmlRegisterSingletonType<object>("Pretzel.Ui", 1, 0, "Test", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
    //     Q_UNUSED(engine)
    //     Q_UNUSED(scriptEngine)
    //     return object;
    // });
    context->setContextProperty(name, object);
}
