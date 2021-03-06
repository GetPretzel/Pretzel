#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>


#include "profilesmodel.h"
#include "propertiesmodel.h"
#include "../database/databasehost.h"


using namespace Pretzel::Framework::Database;
using namespace Pretzel::Framework::Models;


ProfilesModel::ProfilesModel(QObject *parent) : QAbstractListModel(parent) {
    m_roleNames[NameRole] = "name";
    m_roleNames[PropertiesRole] = "properties";

    // WARNING: This *will* produce errors in future (when loading data from the database when rows have been removed)
    m_dataIdNum = 1;

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query("SELECT * FROM profiles");

    int idIndex = query.record().indexOf("id");
    int nameIndex = query.record().indexOf("name");

    bool dataLoaded = false;

    while (query.next()) {
        dataLoaded = true;
        int id = query.value(idIndex).toInt();
        if (id > m_dataIdNum) {
            m_dataIdNum = id;
        }

        QVariantList row_data;

        QString name = query.value(nameIndex).toString();
        row_data << name;

        PropertiesModel *propertiesModel = new PropertiesModel();//0, id);
        propertiesModel->setProfileId(id);
        QString propertiesQueryString = QString("SELECT * FROM profile_%1_properties").arg(id);
        QSqlQuery propertiesQuery(propertiesQueryString);

        int propertyIdIndex = propertiesQuery.record().indexOf("id");
        int propertyNameIndex = propertiesQuery.record().indexOf("name");
        int propertyTypeIndex = propertiesQuery.record().indexOf("type");
        int propertyDisplayItemIndex = propertiesQuery.record().indexOf("display_item");

        while (propertiesQuery.next()) {
            QVariantList propertiesRowData;

            QString propertyName = propertiesQuery.value(propertyNameIndex).toString();
            propertiesRowData.append(propertyName);

            QString propertyType = propertiesQuery.value(propertyTypeIndex).toString();
            propertiesRowData.append(propertyType);

            QString propertyDisplayItem = propertiesQuery.value(propertyDisplayItemIndex).toString();
            propertiesRowData.append(propertyDisplayItem);

            int propertyId = propertiesQuery.value(propertyIdIndex).toInt();
            propertiesRowData.append(propertyId);

            propertiesModel->append(propertiesRowData);
        }

        QVariant propertiesModelVariant = QVariant::fromValue(propertiesModel);
        row_data.append(propertiesModelVariant);

        row_data << id;

        m_data.append(row_data);
    }

    if (dataLoaded) {
        m_dataIdNum += 1;
    }
}


ProfilesModel::~ProfilesModel() {
}


QHash<int, QByteArray> ProfilesModel::roleNames() const {
    return m_roleNames;
}


int ProfilesModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}


QVariant ProfilesModel::data(const QModelIndex &index, int role) const {
    int row = index.row();

    if (row < 0 || row >= m_data.count()) {
        return QVariant();
    }

    if (role < 256) {
        switch (role) {
            case 0:
                role = RoleNames::NameRole;
                break;
            case 1:
                role = RoleNames::PropertiesRole;
                break;
            case 2:
                role = RoleNames::IndexRole;
                break;
        }
    }

    // const QVariantList &row_data = m_data.at(row);
    QVariantList row_data = m_data.at(row);

    switch (role) {
        case NameRole:
            // The name
            return row_data[0];
        case PropertiesRole:
            // The properties model
            return row_data[1];
        case IndexRole:
            // The index role
            return row_data.at(2);
        default:
            return QVariant();
    }
}


int ProfilesModel::count() {
    return m_data.count();
}


// TODO: Look at SortFilterProxyModel for a better example of a get method
// QQmlSortFilterProxyModel::get(int row, const QString& roleName) const
QVariant ProfilesModel::get(int row, int role) {
    // Role 0: name
    // Role 1: properties
    // Role 2: id
    // if (index < 0 || index >= m_data.count()) {
    //     return QVariant();
    // }

    // const QVariantList &row_data = m_data[index];
    // return row_data.at(role);
    return data(index(row, 0), role);
}


QVariant ProfilesModel::getEditable(int row, int role) {
    // Returns a editable value (as oppose to get() which is read-only)
    // Role 0: name
    // Role 1: properties
    // Role 2: id
    // QVariantList &row_data = m_data[index];
    // return row_data[role];
    return data(index(row, 0), role);
}


QVariantList ProfilesModel::getProfileFromId(int id) {
    for (int i = 0; i < m_data.count(); i++) {
        // TODO: Does this need to be editable?
        const QVariantList &row_data = m_data.at(i);
        if (row_data.at(row_data.count() - 1).toInt() == id) {
            return row_data;
        }
    }

    return QVariantList();
}


void ProfilesModel::set(int index, QVariant value, int role) {
    // Role 0: name
    // Role 1: properties
    // Role 2: id (the last index)
    if (role == m_data.at(index).count() - 1) {
        // The ID can not be overriden
        return;
    }

    // TODO: For all functions, update it to the API found to work with the get() method
    QVariantList &row_data = m_data[index];
    row_data[role] = value;

    // Update the database
    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    // No need for a switch statement as the profiles model only updates the name
    query.prepare("update profiles set name = :name where id = :id");
    query.bindValue(":name", value);
    query.bindValue(":id", row_data[2]);
    query.exec();
}


void ProfilesModel::append(QVariantList value) {
    insert(m_data.count(), value);
}


void ProfilesModel::insert(int index, QVariantList value) {
    if (index < 0 || index > m_data.count()) {
        return;
    }

    value.append(m_dataIdNum);

    PropertiesModel* props_model = new PropertiesModel();//0, m_dataIdNum);
    props_model->setProfileId(m_dataIdNum);
    QVariant props_variant_model = QVariant::fromValue(props_model);
    
    QVariantList profile_vals;
    profile_vals.append("New profile");
    profile_vals.append(props_variant_model);
    profile_vals.append(m_dataIdNum);

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    query.prepare("insert into profiles (id, name) values (:id, :name)");
    query.bindValue(":id", profile_vals[2]);
    query.bindValue(":name", profile_vals[0]);
    query.exec();

    // Use a QString for the query (see https://forum.qt.io/topic/132903/sqlite-create-table-does-not-work-when-inserting-variable-into-query/2)
    QString query_string = QString("create table if not exists profile_%1_properties (id integer not null primary key autoincrement, name TEXT, type TEXT, display_item TEXT)").arg(profile_vals.at(2).toString());
    query.exec(query_string);

    emit beginInsertRows(QModelIndex(), index, index);
    m_data.insert(index, profile_vals);
    emit endInsertRows();
    emit countChanged(m_data.count());

    m_dataIdNum += 1;
}


void ProfilesModel::remove(int row) {
    if (row < 0 || row >= m_data.count()) {
        return;
    }

    emit beginRemoveRows(QModelIndex(), row, row);
    
    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query("DELETE FROM profiles WHERE id = ?");
    query.bindValue(0, get(row, RoleNames::IndexRole));
    query.exec();

    delete get(row, RoleNames::PropertiesRole).value<PropertiesModel*>();

    m_data.removeAt(row);

    emit endRemoveRows();
    emit countChanged(m_data.count());
    
}


void ProfilesModel::clear() {
    for (int i = 0; i < m_data.count(); i++) {
        remove(i);
    }
    emit countChanged(m_data.count());
}
