#ifndef STOCKMODEL_H
#define STOCKMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QList>
#include <QModelIndex>
#include <QObject>
#include <QMetaType>
#include <QtQml>
#include <Qt>
#include <QString>
#include <QVariant>
#include <QVariantList>


namespace Pretzel::Framework::Models
{
    class StockModel;
} // namespace Pretzel::Framework::Models


class Pretzel::Framework::Models::StockModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QVariant itemsModel READ itemsModel WRITE setItemsModel NOTIFY itemsModelChanged)
    QML_ELEMENT
private:
    QList<QVariantList> m_data;
    int m_dataIdNum;
    QHash<int, QByteArray> m_roleNames;
    QVariant m_itemsModel;
public:
    enum RoleNames {
        ItemIdRole = Qt::UserRole,
        QuantityRole = Qt::UserRole + 2,
        UnitRole = Qt::UserRole + 3,
        CostRole = Qt::UserRole + 4
    };

    explicit StockModel(QObject *parent = 0);
    ~StockModel();

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    int count();

    QVariant itemsModel();
    void setItemsModel(QVariant model);

    Q_INVOKABLE QVariant get(int index, int role);
    Q_INVOKABLE QVariant getEditable(int index, int role);
    Q_INVOKABLE void set(int index, QVariant value, int role);

    Q_INVOKABLE void append(QVariantList value);
    Q_INVOKABLE void insert(int index, QVariantList values);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
signals:
    void countChanged(int newCount);
    void itemsModelChanged(QVariant model);
};

#endif // STOCKMODEL_H
