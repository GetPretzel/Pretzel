#include "actioncontroller.h"

using namespace Pretzel::Framework;


void ActionController::addAction(Pretzel::Framework::Action *action) {
    m_actionsList.push_back(*action);
}


QAction* ActionController::getActionFromName(QString &name) {
    for (int i = 0; i < m_actionsList.size(); i++) {
        if (m_actionsList.at(i).name == name) {
            return m_actionsList.at(i).action;
        }
    }
}
