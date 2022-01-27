#include <QSqlDatabase>
#include <QSqlQuery>

#include "itempropertiesmodel.h"
#include "../database/databasehost.h"


using namespace Pretzel::Framework::Database;
using namespace Pretzel::Framework::Models;


ItemPropertiesModel::ItemPropertiesModel(QObject *parent) : QAbstractListModel(parent) {
    m_roleNames[PropertyIdRole] = "propertyId";
    m_roleNames[ValueRole] = "value";
}


ItemPropertiesModel::~ItemPropertiesModel() {

}


int ItemPropertiesModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_data.count();
}


QVariant ItemPropertiesModel::data(const QModelIndex &index, int role) const {
    int row = index.row();

    if (row < 0 || row >= m_data.count()) {
        return QVariant();
    }

    const QVariantList &row_data = m_data.at(row);

    switch (role) {
        case PropertyIdRole:
            return row_data.at(0);
        case ValueRole:
            return row_data.at(1);
        default:
            return QVariant();
    }
}


QHash<int, QByteArray> ItemPropertiesModel::roleNames() const {
    return m_roleNames;
}


int ItemPropertiesModel::count() {
    return m_data.count();
}


int ItemPropertiesModel::itemId() {
    return m_itemId;
}


void ItemPropertiesModel::setItemId(int newId) {
    m_itemId = newId;
}


QVariant ItemPropertiesModel::get(int index, int role) {
    // Role 0: property id
    // Role 1: value
    const QVariantList &row_data = m_data[index];
    return row_data.at(role);
}


QVariant ItemPropertiesModel::getEditable(int index, int role) {
    // Role 0: property id
    // Role 1: value
    QVariantList &row_data = m_data[index];
    return row_data[role];
}


void ItemPropertiesModel::set(int itemPropertyId, QVariant value) {
    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString queryString = QString("update item_%1_properties set value = :value where property_id = :property_id").arg(m_itemId);

    query.prepare(queryString);
    query.bindValue(":property_id", itemPropertyId);
    query.bindValue(":value", value);
    query.exec();
}


void ItemPropertiesModel::set(int index, QVariant value, int role) {
    // Role 0: property id
    // Role 1: value
    if (role == 0) {
        // The ID can not be overriden
        return;
    }

    QVariantList &row_data = m_data[index];
    row_data[role] = value;

    // Update the database
    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString queryString = QString("update item_%1_properties set value = :value where property_id = :property_id").arg(m_itemId);

    query.prepare(queryString);
    query.bindValue(":property_id", row_data.at(0));
    query.bindValue(":value", value);
    query.exec();
}


void ItemPropertiesModel::append(QVariantList value) {
    insert(m_data.count(), value);
}


void ItemPropertiesModel::append(QVariantList value, bool updateDatabase) {
    insert(m_data.count(), value, updateDatabase);
}


void ItemPropertiesModel::insert(int index, QVariantList values) {
    if (index < 0 || index > m_data.count()) {
        return;
    }


    emit beginInsertRows(QModelIndex(), index, index);

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString tableName = QString("item_%1_properties").arg(m_itemId);
    query.prepare("insert into " + tableName + " (property_id, value) values (:property_id, :value)");
    query.bindValue(":property_id", values.at(0));
    query.bindValue(":value", values.at(1));
    query.exec();
    
    m_data.insert(index, values);
    emit endInsertRows();
    emit countChanged(m_data.count());
}


void ItemPropertiesModel::insert(int index, QVariantList values, bool updateDatabase) {
    if (index < 0 || index > m_data.count()) {
        return;
    }


    emit beginInsertRows(QModelIndex(), index, index);

    if (updateDatabase) {
        QSqlDatabase database = DatabaseHost::databaseInstance();
        QSqlQuery query;

        QString tableName = QString("item_%1_properties").arg(m_itemId);
        query.prepare("insert into " + tableName + " (property_id, value) values (:property_id, :value)");
        query.bindValue(":property_id", values.at(0));
        query.bindValue(":value", values.at(1));
        query.exec();
    }
    
    m_data.insert(index, values);
    emit endInsertRows();
    emit countChanged(m_data.count());
}


void ItemPropertiesModel::remove(int index) {
    if (index < 0 || index >= m_data.count()) {
        return;
    }

    emit beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    emit endRemoveRows();
    emit countChanged(m_data.count());
}


void ItemPropertiesModel::clear() {
    for (int i = 0; i < m_data.count(); i++) {
        remove(i);
    }

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString tableName = QString("item_%1_properties").arg(m_itemId);
    query.prepare("delete from " + tableName);
    query.exec();

    emit countChanged(m_data.count());
}
