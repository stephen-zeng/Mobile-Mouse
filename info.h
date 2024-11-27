/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#ifndef INFO_H
#define INFO_H

#include <QBluetoothDeviceInfo>

#include <QList>
#include <QAbstractListModel>
#include <QObject>
#include <QQmlEngine>

class ServerInfo: public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name READ getName);
    Q_PROPERTY(QString addr READ getAddress);

public:
    ServerInfo(){};
    ServerInfo(const QBluetoothDeviceInfo&);
    QString getAddress() const;
    QString getName() const;
    void setServer(const QBluetoothDeviceInfo&);
    QBluetoothDeviceInfo getServer();

private:
    QBluetoothDeviceInfo server;
};


#endif // INFO_H
