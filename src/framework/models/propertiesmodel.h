#ifndef PROPERTIESMODEL_H
#define PROPERTIESMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QList>
#include <QMetaType>
#include <QModelIndex>
#include <QObject>
#include <QtQml>
#include <Qt>
#include <QString>
#include <QVariant>


namespace Pretzel::Framework::Models
{
    class PropertiesModel;
} // namespace Pretzel::Framework::Models


class Pretzel::Framework::Models::PropertiesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    QML_ELEMENT
private:
    QList<QVariantList> m_data;
    QHash<int, QByteArray> m_roleNames;
    int m_profileId;
    int m_dataIdNum;
public:
    enum RoleNames {
        NameRole = Qt::UserRole,
        TypeRole = Qt::UserRole + 2,
        DisplayItemRole = Qt::UserRole + 3
    };

    explicit PropertiesModel(QObject *parent = 0, int profileId = -1);
    ~PropertiesModel();

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    int count();

    // QML methods
    Q_INVOKABLE QVariant get(int index, int role);
    Q_INVOKABLE void set(int index, QVariant value, int role);

    Q_INVOKABLE void append();
    Q_INVOKABLE void append(const QVariantList& value);
    Q_INVOKABLE void insert(int index);
    Q_INVOKABLE void insert(int index, const QVariantList& value);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
signals:
    void countChanged(int newCount);
};

#endif // PROPERTIESMODEL_H
