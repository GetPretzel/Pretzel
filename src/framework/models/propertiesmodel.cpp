#include "propertiesmodel.h"


using namespace Pretzel::Framework::Models;


PropertiesModel::PropertiesModel(QObject *parent) : QAbstractListModel(parent) {
    m_roleNames[NameRole] = "name";
    m_roleNames[TypeRole] = "type";
    m_roleNames[DisplayItemRole] = "displayItem";
}


PropertiesModel::~PropertiesModel() {
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


QVariant PropertiesModel::get(int index, int role) {
    // Role 0: name
    // Role 1: type
    // Role 2: display item
    const QVariantList &row_data = m_data[index];
    return row_data.at(role);
}


void PropertiesModel::set(int index, QVariant value, int role) {
    // Role 0: name
    // Role 1: type
    // Role 2: display item
    QVariantList &row_data = m_data[index];
    row_data[role] = value;
}


void PropertiesModel::append(const QVariantList& value) {
    insert(m_data.count(), value);
}


void PropertiesModel::insert(int index, const QVariantList& value) {
    if (index < 0 || index > m_data.count()) {
        return;
    }

    emit beginInsertRows(QModelIndex(), index, index);
    m_data.insert(index, value);
    emit endInsertRows();
    emit countChanged(m_data.count());
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