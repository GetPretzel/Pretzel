#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <QObject>
#include <QMetaType>
#include <QAction>
#include <QString>
#include <QVariant>
#include <QVariantList>

struct Action {
    QString name;
    QAction *action;
};

namespace Pretzel::Framework
{
    class ActionController;
} // namespace Pretzel


class Pretzel::Framework::ActionController : public QObject
{
    Q_OBJECT
private:
    QList<Action> m_actionsList;
public:
    Q_INVOKABLE QAction* getActionFromName(QString &name);
};

#endif // ACTIONCONTROLLER_H
