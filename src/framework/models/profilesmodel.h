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
    Q_PROPERTY(int count READ count NOTIFY countChanged)
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

    int count();

    // QML methods
    Q_INVOKABLE QVariant get(int index, int role);
    Q_INVOKABLE void set(int index, QVariant value, int role);

    Q_INVOKABLE void append(const QVariantList& value);
    Q_INVOKABLE void insert(int index, const QVariantList& value);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();
signals:
    void countChanged(int newCount);
};

#endif // PROFILESMODEL_H
