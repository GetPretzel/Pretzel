#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <QObject>
#include <QMetaType>
#include <QString>
#include <QVariant>
#include <QVariantList>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQmlApplicationEngine>


namespace Pretzel::Framework
{
    class Action;
    class ActionController;
} // namespace Pretzel


class Pretzel::Framework::Action : public QObject
{
    Q_OBJECT
public:
    Action();
    Action(const Action &other);
    Action &operator=(const Action &other);
    ~Action();

    void createActionComponent();

    QString name;
    QObject *action;
};


class Pretzel::Framework::ActionController : public QObject
{
    Q_OBJECT
private:
    QList<Pretzel::Framework::Action> m_actionsList;
public:
    void addAction(Pretzel::Framework::Action *action);
    Q_INVOKABLE QObject* getActionFromName(QString &name);
};

#endif // ACTIONCONTROLLER_H
