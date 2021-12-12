#include <QUrl>
#include <QtQml>
#include <QDebug>

#include "actioncontroller.h"

using namespace Pretzel::Framework;


// Action::Action() {
//     createActionComponent();
// }


// Action::Action(const Action &other) {
//     createActionComponent();
// }


// Action & Action::operator=(const Action &other) {
//     createActionComponent();
//     return *this;
// }


// void Action::createActionComponent() {
//     QQmlEngine *engine = qmlEngine(this);
//     // QQmlEngine *engine = QQmlEngine::contextForObject(this)->engine();
//     // QQmlComponent component(engine, QUrl::fromLocalFile("qrc:/framework/QMLAction.qml"));
//     QQmlComponent component(engine, QUrl::fromLocalFile("qml/Pretzel/Framework/QMLAction.qml"));
//     QObject *action = component.create();
// }


// Pretzel::Framework::Action::~Action() {
    // delete action;
// }


QString Action::name() const {
    return m_name;
}


void Action::setName(const QString &name) {
    m_name = name;
}


void Action::trigger() {
    emit triggered();
}


void ActionController::addAction(Pretzel::Framework::Action *action) {
    m_actionsList.push_back(*action);
}


Action ActionController::getActionFromName(const QString &name) const {
    for (int i = 0; i < m_actionsList.size(); i++) {
        if (m_actionsList.at(i).name() == name) {
            // TODO: Should a pointer be returned?
            return m_actionsList.at(i);
        }
    }
}
