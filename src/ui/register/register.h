#ifndef REGISTER_H
#define REGISTER_H

#include <QObject>
#include <QQmlContext>
#include <QQmlEngine>
#include <QtQml>
#include <QQmlApplicationEngine>


// typedef signed int (*function_type)(signed int, char *);

// signed int foobar(function_type fn) {
//     signed int result = 0;

//     if (fn != NULL)
//         result = (*fn)(12, "barfoo");
// }

namespace Pretzel::Ui
{
    // void registerFunction(QQmlApplicationEngine engine, function_type func);
    void registerObject(QString &name, QObject *object);
} // namespace Pretzel

#endif // REGISTER_H
