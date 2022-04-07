#include <QSqlDatabase>
#include <QSqlQuery>

#include "itemsmodel.h"
#include "stockmodel.h"
#include "../database/databasehost.h"


using namespace Pretzel::Framework::Database;
using namespace Pretzel::Framework::Models;


StockModel::StockModel(QObject *parent) : QAbstractListModel(parent) {
    m_roleNames[ItemIdRole] = "itemid";
    m_roleNames[QuantityRole] = "quantity";
    m_roleNames[UnitRole] = "unit";
    m_roleNames[CostRole] = "cost";

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery itemsIdQuery("SELECT id FROM items");

    while (itemsIdQuery.next()) {
        QVariantList stockData;
        int itemsId = itemsIdQuery.value(0).toInt();
        stockData.append(itemsId);

        QString stockQueryString = QString("SELECT * FROM item_%1_stock").arg(itemsId);
        QSqlQuery stockQuery(stockQueryString);

        int quantityIndex = stockQuery.record().indexOf("quantity");
        int unitIndex = stockQuery.record().indexOf("unit");
        int costIndex = stockQuery.record().indexOf("cost");

        while (stockQuery.next()) {
            int quantity = stockQuery.value(quantityIndex).toInt();
            stockData.append(quantity);

            QString unit = stockQuery.value(unitIndex).toString();
            stockData.append(unit);

            int cost = stockQuery.value(costIndex).toInt();
            stockData.append(cost);
        }

        m_data.append(stockData);
    }
}


StockModel::~StockModel() {
}


int StockModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_data.count();
}


QVariant StockModel::data(const QModelIndex &index, int role) const {
    int row = index.row();

    if (row < 0 || row >= m_data.count()) {
        return QVariant();
    }

    const QVariantList &row_data = m_data.at(row);

    switch (role) {
        case ItemIdRole:
            // The item id
            return row_data.at(0);
        case QuantityRole:
            // The quantity role
            return row_data.at(1);
        case UnitRole:
            // The unit role
            return row_data.at(2);
        case CostRole:
            // The cost role
            return row_data.at(3);
        default:
            return QVariant();
    }
}


QHash<int, QByteArray> StockModel::roleNames() const {
    return m_roleNames;
}


int StockModel::count() {
    return m_data.count();
}


QVariant StockModel::itemsModel() {
    return m_itemsModel;
}


void StockModel::setItemsModel(QVariant model) {
    m_itemsModel = model;
    emit itemsModelChanged(model);
}


QVariant StockModel::get(int index, int role) {
    // Role 0: item id
    // Role 1: quantity
    // Role 2: unit
    // Role 3: cost
    const QVariantList &row_data = m_data[index];
    return row_data.at(role);
}


QVariant StockModel::getEditable(int index, int role) {
    // Role 0: item id
    // Role 1: quantity
    // Role 2: unit
    // Role 3: cost
    QVariantList &row_data = m_data[index];
    return row_data[role];
}


void StockModel::set(int index, QVariant value, int role) {
    // Role 0: item id
    // Role 1: quantity
    // Role 2: unit
    // Role 3: cost
    if (role == 0) {
        // The item id can not be changed
        return;
    }

    ItemsModel *itemsModel = m_itemsModel.value<ItemsModel*>();

    QVariantList &row_data = m_data[index];
    row_data[role] = value;

    int itemId = itemsModel->get(index, 2).toInt();
    // TODO: Should I use the "stock" table instead?
    QString tableName = QString("item_%1_stock").arg(itemId);
    // QString tableName = QString("stock");

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;
    QString queryString;

    switch (role)
    {
    case 1:
        // The quantity
        // TODO: Why doesn't "limit 1" work?
        queryString = QString("update " + tableName + " set quantity = " + value.toString());// + " limit 1");
        break;
    case 2:
        // The unit
        // TODO: Why doesn't "limit 1" work?
        queryString = QString("update " + tableName + " set unit = '" + value.toString() + "'");// + " limit 1");
        break;
    case 3:
        // The cost
        // TODO: Why doesn't "limit 1" work?
        queryString = QString("update " + tableName + " set cost = " + value.toString());// + " limit 1");
        break;
    default:
        return;
    }

    query.exec(queryString);
}


void StockModel::append(QVariantList value) {
    insert(m_data.count(), value);
}


void StockModel::insert(int index, QVariantList values) {
    if (index < 0 || index > m_data.count()) {
        return;
    }


    emit beginInsertRows(QModelIndex(), index, index);

    ItemsModel *itemsModel = m_itemsModel.value<ItemsModel*>();
    int itemId = itemsModel->get(index, 2).toInt();

    QSqlDatabase database = DatabaseHost::databaseInstance();
    QSqlQuery query;

    QString tableName = QString("item_%1_stock").arg(itemId);//values.at(0).toString());
    // QString tableName = QString("stock");//values.at(0).toString());
    query.prepare("insert into " + tableName + " (quantity, unit, cost) values (:quantity, :unit, :cost)");
    query.bindValue(":quantity", values.at(1));
    query.bindValue(":unit", values.at(2));
    query.bindValue(":cost", values.at(3));
    query.exec();
    
    m_data.insert(index, values);
    emit endInsertRows();
    emit countChanged(m_data.count());
}


void StockModel::remove(int index) {
    if (index < 0 || index >= m_data.count()) {
        return;
    }

    // emit beginRemoveRows(QModelIndex(), index, index);

    // ItemsModel *itemsModel = m_itemsModel.value<ItemsModel*>();
    // QString tableName = QString("item_%1_stock").arg(itemsModel->get(index, 2).toInt());

    // QSqlDatabase database = DatabaseHost::databaseInstance();
    // QSqlQuery query("DROP TABLE " + tableName);
    // query.exec();

    // m_data.removeAt(index);

    // emit endRemoveRows();
    // emit countChanged(m_data.count());
}


void StockModel::clear() {
    for (int i = 0; i < m_data.count(); i++) {
        remove(i);
    }

    // TODO: Add the database code

    emit countChanged(m_data.count());
}

