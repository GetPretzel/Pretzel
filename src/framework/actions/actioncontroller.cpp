#include "actioncontroller.h"

#include <QDebug>

using namespace Pretzel::Framework;


QAction* ActionController::getActionFromName(QString &name) {
    for (int i = 0; i < m_actionsList.size(); i++) {
        if (m_actionsList.at(i).name == name) {
            return m_actionsList.at(i).action;
        }
    }
}
