#ifndef ITEMPROPERTIESMODEL_H
#define ITEMPROPERTIESMODEL_H

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
    class ItemPropertiesModel;
} // namespace Pretzel::Framework::Model


class Pretzel::Framework::Models::ItemPropertiesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(int itemId READ itemId WRITE setItemId NOTIFY itemIdChanged)
    QML_ELEMENT
private:
    QList<QVariantList> m_data;
    int m_dataIdNum;
    QHash<int, QByteArray> m_roleNames;
    int m_itemId = -1;
public:
    enum RoleNames {
        PropertyIdRole = Qt::UserRole,
        ValueRole = Qt::UserRole + 2
    };

    explicit ItemPropertiesModel(QObject *parent = 0);
    ~ItemPropertiesModel();

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    int count();

    int itemId();
    void setItemId(int newId);

    Q_INVOKABLE QVariant get(int index, int role);
    Q_INVOKABLE QVariant getEditable(int index, int role);
    Q_INVOKABLE void set(int index, QVariant value, int role);

    Q_INVOKABLE void append(QVariantList value);
    Q_INVOKABLE void insert(int index, QVariantList values);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
signals:
    void countChanged(int newCount);
    void itemIdChanged(int newItemId);
};


#endif // ITEMPROPERTIESMODEL_H
