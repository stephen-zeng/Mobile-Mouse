/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#include "servermodel.h"

ServerModel::ServerModel(QObject *parent)
    : QAbstractItemModel(parent) {
    m_roleName.insert(Name, "serverName"); // serverName是在QML中使用的
    m_roleName.insert(Addr, "serverAddr");
}

QHash <int, QByteArray> ServerModel::roleNames() const {
    return m_roleName;
}

int ServerModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;

    return m_serverList.size();
}

QVariant ServerModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Name: return m_serverList.value(index.row()).qsName;
    case Addr: return m_serverList.value(index.row()).qsAddr;
    default: break;
    }
}
