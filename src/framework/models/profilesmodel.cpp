#include "profilesmodel.h"


using namespace Pretzel::Framework::Models;


ProfilesModel::ProfilesModel(QObject *parent) : QAbstractListModel(parent) {
    m_roleNames[NameRole] = "name";
    m_roleNames[PropertiesRole] = "properties";
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


QVariantList ProfilesModel::get(int index) {
    return m_data.at(index);
}


void ProfilesModel::append(const QVariantList& value) {
    insert(m_data.count(), value);
}


void ProfilesModel::insert(int index, const QVariantList& value) {
    if (index < 0 || index > m_data.count()) {
        return;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    m_data.insert(index, value);
    emit endInsertRows();
    emit countChanged(m_data.count());
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
