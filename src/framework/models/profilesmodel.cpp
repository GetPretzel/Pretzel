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

    // TODO: Load the data saved to the database

    // WARNING: This *will* produce errors in future (when loading data from the database when rows have been removed)
    m_dataIdNum = 1;
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
    // Role 2: id
    const QVariantList &row_data = m_data[index];
    return row_data.at(role);
}


QVariant ProfilesModel::getEditable(int index, int role) {
    // Returns a editable value (as oppose to get() which is read-only)
    // Role 0: name
    // Role 1: properties
    // Role 2: id
    QVariantList &row_data = m_data[index];
    return row_data[role];
}


QVariantList ProfilesModel::getProfileFromId(int id) {
    qDebug() << m_data;
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

    PropertiesModel* props_model = new PropertiesModel(0, m_dataIdNum);
    QVariant props_variant_model = QVariant::fromValue(props_model);
    
    QVariantList profile_vals;
    profile_vals.append("New profile");
    profile_vals.append(props_variant_model);
    profile_vals.append(m_dataIdNum);

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    query.prepare("insert into profiles (name) values (:name)");
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
