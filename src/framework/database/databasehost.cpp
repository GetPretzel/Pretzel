#include <QStandardPaths>

#include <stdio.h>
#include <stdexcept>

#include "databasehost.h"


using namespace Pretzel::Framework::Database;


void DatabaseHost::init() {
    QFile databaseFile(databaseLocation());
    bool exists = databaseFile.exists();

    try {
        databaseFile.open(stderr, QIODevice::ReadWrite);
    } catch(const std::exception& e) {
        std::runtime_error(e.what() + '\n');
    }

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databaseLocation());

    if (!database.open()) {
        std::runtime_error("[ERROR] DatabaseHost: Failed to connect to the database");
    }

    QSqlQuery query;

    if (!exists) {
        query.exec("create table if not exists profiles (id integer not null primary key autoincrement, name TEXT null, properties TEXT null)");
    }
}


void DatabaseHost::quit() {

}


QString DatabaseHost::databaseLocation() {
    // return QString(QStandardPaths::HomeLocation + "/.pretzel/data.db");
    return QString("data.db");
}


QSqlDatabase DatabaseHost::databaseInstance() {
    return QSqlDatabase::database();
}