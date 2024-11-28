#ifndef SERVERMODEL_H
#define SERVERMODEL_H

#include <QAbstractListModel>
#include <QObject>

struct SERVER_INFO {
    QString qsName;
    QString qsAddr;
};

class ServerModel: public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ServerModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QHash <int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE QAbstractItemModel* model();

public:
    enum SERVER_INFO {
        Name = Qt::UserRole + 1,
        Addr,
    };

private:
    QList <SERVER_INFO> m_serverList;
    QHash <int, QByteArray> m_roleName;
};

#endif // SERVERMODEL_H
