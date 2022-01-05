#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "databasehost.h"
#include "items.h"
#include "../models/itemsmodel.h"
#include "../models/propertiesmodel.h"


// using namespace Pretzel::Actions;
using namespace Pretzel::Framework::Database;
using namespace Pretzel::Framework::Models;


void Pretzel::Actions::resetItemProperties(QVariantList args) {
    // Resets an item's properties
    
    const int id = args.at(0).toInt();

    QVariant profileDataVariant = args.at(1);
    QVariantList profileData = profileDataVariant.value<QVariantList>();
    PropertiesModel *propertiesModel = profileData[1].value<PropertiesModel*>();

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString queryString = QString("DROP TABLE item_%1_properties").arg(id);
    query.exec(queryString);

    QString tableName = QString("item_%1_properties").arg(id);
    queryString = QString("CREATE TABLE IF NOT EXISTS " + tableName + " (property_id INTEGER, value TEXT)");
    query.exec(queryString);
}


void Pretzel::Actions::addItemProperty(QVariantList args) {
    const int id = args.at(0).toInt();
    const int propertyId = args.at(1).toInt();
    const QVariant value = args.at(2).toString();

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString tableName = QString("item_%1_properties").arg(id);
    QString queryString = QString("INSERT INTO " + tableName + " (property_id, value) VALUES (:property_id, :value)");
    query.prepare(queryString);
    query.bindValue(":property_id", propertyId);
    query.bindValue(":value", value);
    query.exec();
}


void Pretzel::Actions::updateItemProperty(QVariantList args) {
    const int id = args.at(0).toInt();
    const int propertyId = args.at(1).toInt();
    const QVariant value = args.at(2).toString();

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString tableName = QString("item_%1_properties").arg(id);
    QString queryString = QString("UPDATE " + tableName + " SET value = :value WHERE property_id = :property_id");
    query.prepare(queryString);
    query.bindValue(":property_id", propertyId);
    query.bindValue(":value", value);
    query.exec();
}
