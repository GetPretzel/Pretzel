#ifndef PROFILESMODEL_H
#define PROFILESMODEL_H

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
    class ProfilesModel;
} // namespace Pretzel::Framework::Models


class Pretzel::Framework::Models::ProfilesModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    QML_ELEMENT
private:
    QList<QVariantList> m_data;
    int m_dataIdNum;
    QHash<int, QByteArray> m_roleNames;
public:
    enum RoleNames {
        NameRole = Qt::UserRole,
        PropertiesRole = Qt::UserRole + 2,
        IndexRole = Qt::UserRole + 3
    };

    explicit ProfilesModel(QObject *parent = 0);
    ~ProfilesModel();

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    int count();

    // QML methods
    Q_INVOKABLE QVariant get(int index, int role);
    Q_INVOKABLE QVariant getEditable(int index, int role);
    // TODO: Does this method need to be a static method?
    Q_INVOKABLE QVariantList getProfileFromId(int id);
    Q_INVOKABLE void set(int index, QVariant value, int role);

    Q_INVOKABLE void append(QVariantList value);
    Q_INVOKABLE void insert(int index, QVariantList value);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
signals:
    void countChanged(int newCount);
};

#endif // PROFILESMODEL_H
