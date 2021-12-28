#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "itemsmodel.h"
#include "profilesmodel.h"
#include "propertiesmodel.h"
#include "../database/databasehost.h"


using namespace Pretzel::Framework::Database;
using namespace Pretzel::Framework::Models;


ItemsModel::ItemsModel(QObject *parent) : QAbstractListModel(parent) {
    // ProfileRole = the profile id
    m_roleNames[ProfileRole] = "profile";
    m_roleNames[PropertiesRole] = "properties";

    // TODO: Load the data saved to the database

    // WARNING: This *will* produce errors in future (when loading data from the database when rows have been removed)
    m_dataIdNum = 1;
}


ItemsModel::~ItemsModel() {
}


QHash<int, QByteArray> ItemsModel::roleNames() const {
    return m_roleNames;
}


int ItemsModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}


QVariant ItemsModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    
    if (row < 0 || row >= m_data.count()) {
        return QVariant();
    }

    const QVariantList &row_data = m_data.at(row);

    switch (role) {
        case ProfileRole:
            // The name
            return row_data.at(0);
        case PropertiesRole:
            // The properties model
            return row_data.at(1);
        default:
            return QVariant();
    }
}


int ItemsModel::count() {
    return m_data.count();
}


QVariant ItemsModel::profilesModel() {
    return m_profilesModel;
}


void ItemsModel::setProfilesModel(QVariant model) {
    m_profilesModel = model;
    emit profilesModelChanged(model);
}


int ItemsModel::profileId() {
    return m_profileId;
}


void ItemsModel::setProfileId(int id) {
    m_profileId = id;
    emit profileIdChanged(id);
}


QVariantList ItemsModel::getProfileData(int id) {
    ProfilesModel *model = m_profilesModel.value<ProfilesModel*>();
    QVariantList data = model->getProfileFromId(id);
    return data;
}


QVariant ItemsModel::getPropertiesModel() {
    QVariant variant;
    return variant;
}


QVariant ItemsModel::get(int index, int role) {
    // Role 0: profile id
    // Role 1: item id
    const QVariantList &row_data = m_data[index];
    return row_data.at(role);
}


QVariant ItemsModel::getEditable(int index, int role) {
    // Returns a editable value (as oppose to get() which is read-only)
    // Role 0: profile id
    // Role 1: item id
    QVariantList &row_data = m_data[index];
    return row_data[role];
}


void ItemsModel::set(int index, QVariant value, int role) {
    // Role 0: profile id
    // Role 1: item id
    if (role == m_data.at(index).count() - 1) {
        // The ID can not be overriden
        return;
    }

    QVariantList &row_data = m_data[index];
    row_data[role] = value;

    // Update the database
    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    // No need for a switch statement as the profiles model only updates the name
    query.prepare("update items set profile_id = :profile_id where id = :item_id");
    query.bindValue(":profile_id", value);
    query.bindValue(":item_id", row_data.at(1));
    query.exec();
}


void ItemsModel::append(QVariantList value) {
    insert(m_data.count(), value);
}


void ItemsModel::insert(int index, QVariantList value) {
    if (index < 0 || index > m_data.count()) {
        return;
    }

    value.append(m_dataIdNum);

    QVariantList itemVals;
    // The profile id
    itemVals.append(1);
    // The item id
    itemVals.append(m_dataIdNum);

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    query.prepare("insert into items (profile_id) values (:profile_id)");
    query.bindValue(":profile_id", itemVals[0]);
    query.exec();

    // Use a QString for the query (see https://forum.qt.io/topic/132903/sqlite-create-table-does-not-work-when-inserting-variable-into-query/2)
    // QString query_string = QString("create table if not exists profile_%1_properties (name TEXT, type TEXT, display_item TEXT)").arg(value.at(2).toString());
    
    // TODO: Get the profile properties and dynamically adjust the item properties
    // QString query_string = QString("create table if not exists item_%1_properties (id integer not null primary key autoincrement, name TEXT, type TEXT, display_item TEXT)").arg(itemVals.at(2).toString());
    // query.exec(query_string);

    emit beginInsertRows(QModelIndex(), index, index);
    m_data.insert(index, itemVals);
    emit endInsertRows();
    emit countChanged(m_data.count());

    // PropertiesModel* props_model = new PropertiesModel();
    // QVariant props_variant_model = QVariant::fromValue(props_model);
    
    // QVariantList profile_vals;
    // profile_vals.append("New profile");
    // profile_vals.append(props_variant_model);
    // profile_vals.append(m_dataIdNum);

    // emit beginInsertRows(QModelIndex(), index, index);
    // m_data.insert(index, profile_vals);
    // emit endInsertRows();
    // emit countChanged(m_data.count());

    m_dataIdNum += 1;
}


void ItemsModel::remove(int index) {
    if (index < 0 || index >= m_data.count()) {
        return;
    }

    emit beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    emit endRemoveRows();
    emit countChanged(m_data.count());
}


void ItemsModel::clear() {
    for (int i = 0; i < m_data.count(); i++) {
        remove(i);
    }
    emit countChanged(m_data.count());
}
