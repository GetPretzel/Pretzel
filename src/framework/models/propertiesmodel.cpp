#include <QSqlDatabase>
#include <QSqlQuery>

#include "propertiesmodel.h"
#include "../database/databasehost.h"


using namespace Pretzel::Framework::Database;
using namespace Pretzel::Framework::Models;


PropertiesModel::PropertiesModel(QObject *parent) : QAbstractListModel(parent) {//, int profileId) : QAbstractListModel(parent), m_profileId(profileId) {
    m_roleNames[NameRole] = "name";
    m_roleNames[TypeRole] = "type";
    m_roleNames[DisplayItemRole] = "displayItem";

    // Load properties model here

    m_dataIdNum = 1;
}


PropertiesModel::~PropertiesModel() {
    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString tableName = QString("item_%1_properties").arg(m_profileId);
    query.prepare("DROP TABLE " + tableName);
    query.exec();
}


QHash<int, QByteArray> PropertiesModel::roleNames() const {
    return m_roleNames;
}


int PropertiesModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_data.count();
}


QVariant PropertiesModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    
    if (row < 0 || row >= m_data.count()) {
        return QVariant();
    }

    const QVariantList &row_data = m_data.at(row);

    switch (role) {
        case NameRole:
            // The name
            return row_data.at(0);
        case TypeRole:
            // The type
            return row_data.at(1);
        case DisplayItemRole:
            // The display item (widget)
            return row_data.at(2);
        default:
            return QVariant();
    }
}


int PropertiesModel::count() {
    return m_data.count();
}


int PropertiesModel::profileId() {
    return m_profileId;
}


void PropertiesModel::setProfileId(int newId) {
    m_profileId = newId;
    emit profileIdChanged(newId);
}


QVariant PropertiesModel::get(int index, int role) {
    // Role 0: name
    // Role 1: type
    // Role 2: display item
    // Role 3: id
    const QVariantList &row_data = m_data[index];
    return row_data.at(role);
}


void PropertiesModel::set(int index, QVariant value, int role) {
    // Role 0: name
    // Role 1: type
    // Role 2: display item
    // Role 3: id (the last index)
    if (role == m_data.at(index).count() - 1) {
        // The ID can not be overriden
        return;
    }
    
    QVariantList &row_data = m_data[index];
    row_data[role] = value;

    // Update the database
    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString tableName = QString("profile_%1_properties").arg(m_profileId);

    switch (role) {
        // TODO: ID's should probably be used instead of names to get/set items in the database
        case 0:
            query.prepare("update " + tableName + " set name = :name where id = :id");
            query.bindValue(":name", value);
            query.bindValue(":id", get(index, 3));
            break;
        case 1:
            query.prepare("update " + tableName + " set type = :type where id = :id");
            query.bindValue(":type", value);
            query.bindValue(":id", get(index, 3));
            break;
        case 2:
            query.prepare("update " + tableName + " set display_item = :display_item where id = :id");
            query.bindValue(":display_item", value);
            query.bindValue(":id", get(index, 3));
            break;
        default:
            return;
    }

    query.exec();
}


void PropertiesModel::append() {
    insert(m_data.count());
}


void PropertiesModel::append(const QVariantList& value) {
    insert(m_data.count(), value);
}


void PropertiesModel::insert(int index) {
    if (index < 0 || index > m_data.count()) {
        return;
    }

    QVariantList properties_vals;
    properties_vals.append("New property");
    // TODO: Use PDropDown.currentValue to input the actual SQLite 3 types (which will save a switch statement later)
    properties_vals.append("String");
    properties_vals.append("PLineEdit");
    properties_vals.append(m_dataIdNum);

    emit beginInsertRows(QModelIndex(), index, index);
    m_data.insert(index, properties_vals);
    emit endInsertRows();
    emit countChanged(m_data.count());

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString query_string = QString("INSERT INTO profile_%1_properties (name, type, display_item) VALUES (?, ?, ?)").arg(m_profileId);
    query.prepare(query_string);
    query.bindValue(0, properties_vals[0]);
    query.bindValue(1, properties_vals[1]);
    query.bindValue(2, properties_vals[2]);
    query.exec();

    m_dataIdNum += 1;
}


void PropertiesModel::insert(int index, const QVariantList& value) {
    if (index < 0 || index > m_data.count()) {
        return;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    m_data.insert(index, value);
    emit endInsertRows();
    emit countChanged(m_data.count());

    // Don't do anything with the database here (or loading the properties doesn't work)
    // QSqlDatabase database = DatabaseHost::databaseInstance();
    // QSqlQuery query;

    // QString query_string = QString("INSERT INTO profile_%1_properties (name, type, display_item) VALUES (?, ?, ?)").arg(m_profileId);
    // query.prepare(query_string);
    // query.bindValue(0, value[0]);
    // query.bindValue(1, value[1]);
    // query.bindValue(2, value[2]);
    // query.exec();

    m_dataIdNum += 1;
}


void PropertiesModel::remove(int index) {
    if (index < 0 || index >= m_data.count()) {
        return;
    }

    emit beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    emit endRemoveRows();
    emit countChanged(m_data.count());
}


void PropertiesModel::clear() {
    for (int i = 0; i < m_data.count(); i++) {
        remove(i);
    }
    emit countChanged(m_data.count());
}
