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
