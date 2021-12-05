#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <QObject>
#include <QMetaType>
#include <QAction>
#include <QString>
#include <QVariant>
#include <QVariantList>


namespace Pretzel::Framework
{
    class ActionController;
    struct Action {
        QString name;
        QAction *action;
    };
} // namespace Pretzel


class Pretzel::Framework::ActionController : public QObject
{
    Q_OBJECT
private:
    QList<Pretzel::Framework::Action> m_actionsList;
public:
    void addAction(Pretzel::Framework::Action *action);
    Q_INVOKABLE QAction* getActionFromName(QString &name);
};

#endif // ACTIONCONTROLLER_H
