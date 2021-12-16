#include <QDebug>
#include <QFile>

#include "profilesmodel.h"
#include "propertiesmodel.h"
#include "../database/databasehost.h"


using namespace Pretzel::Framework::Models;


ProfilesModel::ProfilesModel(QObject *parent) : QAbstractListModel(parent) {
    m_roleNames[NameRole] = "name";
    m_roleNames[PropertiesRole] = "properties";

    // TODO: Load the data saved to the database

    m_dataIdNum = m_data.count();
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

    const QVariantList &row_data = m_data.at(row);

    switch (role) {
        case NameRole:
            // The name
            return row_data.at(0);
        case PropertiesRole:
            // The properties model
            return row_data.at(1);
        default:
            return QVariant();
    }
}


int ProfilesModel::count() {
    return m_data.count();
}


QVariant ProfilesModel::get(int index, int role) {
    // Role 0: name
    // Role 1: properties
    const QVariantList &row_data = m_data[index];
    return row_data.at(role);
}


QVariant ProfilesModel::getEditable(int index, int role) {
    // Returns a editable value (as oppose to get() which is read-only)
    // Role 0: name
    // Role 1: properties
    QVariantList &row_data = m_data[index];
    return row_data[role];
}


QVariant ProfilesModel::getProfileIdFromName(const QString &name) {
    qWarning() << "[WARNING] ProfilesModel::getProfileIdFromName() does not work. Use ProfilesModel::get(<index>, 2) to get the id instead";
    for (int i = 0; i < m_data.count(); i++) {
        const QVariantList &row_data = m_data.at(i);
        if (row_data.at(0).toString() == name) {
            // The id is the last index
            return row_data.last();
        }
    }

    return -1;
}


void ProfilesModel::set(int index, QVariant value, int role) {
    // Role 0: name
    // Role 1: properties
    QVariantList &row_data = m_data[index];
    row_data[role] = value;
}


void ProfilesModel::append(QVariantList value) {
    insert(m_data.count(), value);
}


void ProfilesModel::insert(int index, QVariantList value) {
    if (index < 0 || index > m_data.count()) {
        return;
    }

    value.append(m_dataIdNum);

    emit beginInsertRows(QModelIndex(), index, index);
    m_data.insert(index, value);
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


void ProfilesModel::remove(int index) {
    if (index < 0 || index >= m_data.count()) {
        return;
    }

    emit beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    emit endRemoveRows();
    emit countChanged(m_data.count());
}


void ProfilesModel::clear() {
    for (int i = 0; i < m_data.count(); i++) {
        remove(i);
    }
    emit countChanged(m_data.count());
}
