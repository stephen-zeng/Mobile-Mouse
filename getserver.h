/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#ifndef GETSERVER_H
#define GETSERVER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QPermissions>
#include <QVariant>

#include "info.h"
#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
#include "mousemove.h"
#endif

class GetServer: public QObject {
    Q_OBJECT

public:
    Q_PROPERTY(bool msgbox READ getMsgbox WRITE setMsgbox NOTIFY updateMsgbox);
    Q_PROPERTY(QString msg READ getMsg WRITE setMsg NOTIFY updateMsg);
    Q_PROPERTY(bool agentstart READ getAgentstart WRITE setAgentstart NOTIFY updateAgentstart);
    Q_PROPERTY(QVariant serverlist READ getServerlist WRITE setServerlist NOTIFY updateServerlist);
    Q_PROPERTY(int serverconnect READ getServerconnect WRITE setServerconnect NOTIFY updateServerconnect);
    Q_PROPERTY(int data READ getData WRITE setData NOTIFY updateData);
    Q_PROPERTY(QString last READ getLast NOTIFY updateLast);
    Q_PROPERTY(bool haveLast READ getHavelast NOTIFY updateLast);

    Q_INVOKABLE void startGetServer();
    Q_INVOKABLE void stopGetServer();
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void startGetService(const QString&, const QString&);
    Q_INVOKABLE void retry();
    Q_INVOKABLE void disconnectServer();
    Q_INVOKABLE void checkController();
    Q_INVOKABLE void connectLast();

    explicit GetServer(QObject *parent = nullptr);
    ~GetServer();

private:
    bool m_msgbox = false;
    bool getMsgbox();
    void setMsgbox(const bool&);

    QString m_msg;
    QString getMsg();
    void setMsg(const QString&);

    bool m_agentstart = false;
    bool getAgentstart();
    void setAgentstart(const bool&);

    QList <ServerInfo *> serverList;
    QVariant getServerlist();
    void setServerlist(const QVariant&){};

    //0是连接中，1是已连接，2是未连接
    int m_serverconnect = 0;
    int getServerconnect();
    void setServerconnect(const int&){};

    int m_data = 0;
    int getData();
    void setData(const int&){};

    QString m_last = "无";
    QString m_addr;
    QString getLast();

    bool m_havelast = false;
    bool getHavelast(){return m_havelast;};

    QBluetoothDeviceDiscoveryAgent *agent;
    QLowEnergyController *controller = nullptr;
    QLowEnergyService *service = nullptr;
    QLowEnergyDescriptor notistatus;
    ServerInfo currentServer;
    ServerInfo lastServer;
    QString file;

#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
    MouseMove mouseMove;
#endif

private slots:
    void addServer(const QBluetoothDeviceInfo&);
    void scanServerFinished();
    void scanError(const QBluetoothDeviceDiscoveryAgent::Error&);
    void serverConnected();
    void serverDisconnected();
    void serverError(const QLowEnergyController::Error&);
    void scanServiceFinished();
    void checkService(const QBluetoothUuid&);
    void serviceStatusChanged(const QLowEnergyService::ServiceState&);
    void serviceDataChanged(const QLowEnergyCharacteristic&, const QByteArray&);
    void serverStatusChanged(const QLowEnergyDescriptor&, const QByteArray&);


signals:
    void updateMsgbox();
    void updateMsg();
    void updateAgentstart();
    void updateServerlist();
    void updateServerconnect();
    void updateData();
    void updateLast();
};

#endif // GETSERVER_H
