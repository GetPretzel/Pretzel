#ifndef ITEMSMODEL_H
#define ITEMSMODEL_H

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
#include <QVariantList>

#include "profilesmodel.h"
#include "propertiesmodel.h"


namespace Pretzel::Framework::Models
{
    class ItemsModel;
} // namespace Pretzel::Framework::Models


class Pretzel::Framework::Models::ItemsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(QVariant profilesModel READ profilesModel WRITE setProfilesModel NOTIFY profilesModelChanged)
    Q_PROPERTY(int profileId READ profileId WRITE setProfileId NOTIFY profileIdChanged)
    QML_ELEMENT
private:
    QList<QVariantList> m_data;
    int m_dataIdNum;
    QHash<int, QByteArray> m_roleNames;
    QVariant m_profilesModel;
    int m_profileId;
public:
    enum RoleNames {
        ProfileRole = Qt::UserRole,
        PropertiesRole = Qt::UserRole + 2
    };

    explicit ItemsModel(QObject *parent = 0);
    ~ItemsModel();

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;

    int count();

    QVariant profilesModel();
    void setProfilesModel(QVariant model);

    int profileId();
    void setProfileId(int id);

    Q_INVOKABLE QVariantList getProfileData(int id);
    Q_INVOKABLE QVariant getPropertiesModel();

    // QML methods
    Q_INVOKABLE QVariant get(int index, int role);
    Q_INVOKABLE QVariant getEditable(int index, int role);
    Q_INVOKABLE void set(int index, QVariant value, int role);

    Q_INVOKABLE void append(QVariantList value);
    Q_INVOKABLE void insert(int index, QVariantList value);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
signals:
    void countChanged(int newCount);
    void profilesModelChanged(QVariant model);
    void profileIdChanged(int newProfileId);
};

#endif // ITEMSMODEL_H
