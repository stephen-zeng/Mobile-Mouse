/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#include "info.h"
#include <QDebug>

#ifdef Q_OS_DARWIN
# include <QBluetoothUuid>
# else
# include <QBluetoothAddress>
#endif

ServerInfo::ServerInfo(const QBluetoothDeviceInfo& newServer) {
    server = newServer;
}

QString ServerInfo::getAddress() const {
#ifdef Q_OS_DARWIN
    return server.deviceUuid().toString();
#else
    return server.address().toString();
#endif
}

QString ServerInfo::getName() const {
    return server.name();
}

void ServerInfo::setServer(const QBluetoothDeviceInfo& selectedServer) {
    server = selectedServer;
}

QBluetoothDeviceInfo ServerInfo::getServer() {
    return server;
}

