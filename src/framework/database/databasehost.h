#ifndef DATABASEHOST_H
#define DATABASEHOST_H

#include <QMetaType>
#include <QObject>
#include <QtQml>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QtSql>


namespace Pretzel::Framework::Database
{
    // TODO: Is ``DatabaseManager`` a better name?
    class DatabaseHost;
} // namespace Pretzel::Framework::Database


class Pretzel::Framework::Database::DatabaseHost : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void init();
    Q_INVOKABLE void quit();

    Q_INVOKABLE QSqlDatabase databaseInstance();
    Q_INVOKABLE QString databaseLocation();
};

#endif // DATABASEHOST_H
