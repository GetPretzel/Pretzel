#include "papplication.h"

using namespace Pretzel::Framework::Application;


bool PApplication::event(QEvent* e) {
    if (e->type() == QEvent::Show) {
            qDebug() << "Showed window";
            QGuiApplication::event(e);
            return true;
        }

    return QGuiApplication::event(e);
}
