#ifndef PROFILESMODEL_H
#define PROFILESMODEL_H

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QList>
#include <QModelIndex>
#include <QObject>
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
private:
    QList<QVariantList> m_data;
    QHash<int, QByteArray> m_roleNames;
public:
    enum RoleNames {
        NameRole = Qt::UserRole,
        PropertiesRole = Qt::UserRole + 2
    };

    explicit ProfilesModel(QObject *parent = 0);
    ~ProfilesModel();

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;
};

#endif // PROFILESMODEL_H
