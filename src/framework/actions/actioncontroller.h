#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <QObject>
#include <QMetaType>
#include <QString>
#include <QVariant>
#include <QVariantList>
#include <QtQml>
#include <QList>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQmlApplicationEngine>

#include <optional>


namespace Pretzel::Framework
{
    class Action;
    class ActionController;
} // namespace Pretzel::Framework


class Pretzel::Framework::Action : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
private:
    QString m_name;
public:
    Action(QObject *parent = 0) {};
    Action(const Action &other) {};
    Action &operator=(const Action&) {return *this;};
    ~Action() {};

    void connect(void* method);

    QString name() const;
    void setName(const QString &name);

    Q_INVOKABLE void trigger(QVariantList args);
signals:
    void triggered(QVariantList args);
};

Q_DECLARE_METATYPE(Pretzel::Framework::Action*);


class Pretzel::Framework::ActionController : public QObject
{
    Q_OBJECT
private:
    QList<Action*> m_actionsList;
public:
    // TODO: Add an ``instance()`` method
    void addAction(Pretzel::Framework::Action *action);
    Q_INVOKABLE Action* getActionFromName(const QString &name) const;
};

#endif // ACTIONCONTROLLER_H
