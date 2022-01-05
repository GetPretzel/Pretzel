#ifndef PAPPLICATION_H
#define PAPPLICATION_H

#include <QDebug>
#include <QEvent>
#include <QGuiApplication>
#include <QObject>


namespace Pretzel::Framework::Application
{
    class PApplication;
} // namespace Pretzel::Framework::Applicatio


class Pretzel::Framework::Application::PApplication : public QGuiApplication {
    Q_OBJECT
public:
    // PApplication();
    PApplication(int &argc, char **argv);
    ~PApplication();
    bool event(QEvent *e) override;
};


#endif // PAPPLICATION_H
