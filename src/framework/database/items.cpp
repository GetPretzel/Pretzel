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
