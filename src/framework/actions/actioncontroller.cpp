#include <QUrl>
#include <QtQml>
#include <QDebug>


#include "actioncontroller.h"

using namespace Pretzel::Framework;


void Action::connect(void* method) {
    // TODO: Pass in any method/function (with/without return type) as a parameter to this method
    // QObject::connect(this, &Action::triggered, this, method);
}


QString Action::name() const {
    return m_name;
}


void Action::setName(const QString &name) {
    m_name = name;
}


void Action::trigger(QVariantList args) {
    emit triggered(args);
}


void ActionController::addAction(Pretzel::Framework::Action *action) {
    m_actionsList.push_back(action);
}


Action* ActionController::getActionFromName(const QString &name) const {
    for (int i = 0; i < m_actionsList.size(); i++) {
        if (m_actionsList.at(i)->name() == name) {
            return m_actionsList.at(i);
        }
    }
}
