/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#include "getserver.h"
#include <QDebug>

using namespace std;

GetServer::GetServer(QObject *parent)
    : QObject(parent) {
    agent = new QBluetoothDeviceDiscoveryAgent(this);
    agent->setLowEnergyDiscoveryTimeout(10000);
    connect(agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &GetServer::addServer);
    connect(agent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &GetServer::scanServerFinished);
    connect(agent, &QBluetoothDeviceDiscoveryAgent::canceled,
            this, &GetServer::scanServerFinished);
    connect(agent, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
            this, &GetServer::scanError);
}

GetServer::~GetServer() {
    serverList.clear();
    delete agent;
    delete controller;
    delete service;
}

void GetServer::startGetServer() {
    agent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    m_agentstart = true;
}

void GetServer::refresh() {
    stopGetServer();
    serverList.clear();
    startGetServer();
}

void GetServer::stopGetServer() {
    if (agent->isActive())
        agent->stop();
    m_agentstart = false;
    emit updateAgentstart();
}

void GetServer::addServer(const QBluetoothDeviceInfo& newServer) {
    if (newServer.coreConfigurations() &
        QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        auto newInfo = new ServerInfo(newServer);
        auto tmp = find_if(serverList.begin(), serverList.end(),
                           [newInfo](ServerInfo *serv) {
                               return newInfo->getAddress() == serv->getAddress();
        });
        if (tmp == serverList.end()) {
            if (!newInfo->getName().isEmpty()) {
                qDebug()<<newInfo->getName();
                serverList.append(newInfo);
            }

        }
        else {
            auto del = *tmp;
            *tmp = newInfo;
            delete del;
            //新建一个指针用于删除，防止内存出现错误
        }
    }
    // qDebug()<<"From C++, new server";
    emit updateServerlist();
}

void GetServer::scanServerFinished() {
    if (serverList.isEmpty())
        setMsg(QString::fromStdString("未发现设备"));
    else
        setMsg(QString::fromStdString("扫描结束"));
    m_agentstart = false;
}

void GetServer::scanError(const QBluetoothDeviceDiscoveryAgent::Error& errorInfo) {
    switch (errorInfo) {
    case QBluetoothDeviceDiscoveryAgent::PoweredOffError: setMsg(QString::fromStdString("蓝牙适配器未开启"));
    case QBluetoothDeviceDiscoveryAgent::InputOutputError: setMsg(QString::fromStdString("蓝牙设备读写错误"));
    default: setMsg(QString::fromStdString("发生未知错误"));
    }
    m_agentstart = false;
    emit updateAgentstart();
}

void GetServer::startGetService(const QString& address) {

    for (auto tmp: as_const(serverList))
        if (auto server = qobject_cast<ServerInfo*>(tmp))
            if (server->getAddress() == address) {
                currentServer.setServer(server->getServer());
                break;
            }

    if (!currentServer.getServer().isValid()) {
        setMsg(QString::fromStdString("设备无效"));
        return;
    }

    if (controller &&
        currentServer.getAddress() != lastServer.getAddress()) {
        controller->disconnectFromDevice();
        delete controller;
        controller = nullptr;
    }

    qDebug()<<"Start getting service from "<<currentServer.getName();

    if (!controller) {
        qDebug()<<"Controller Initiated";
        controller = QLowEnergyController::createCentral(currentServer.getServer(), this);
        controller->setRemoteAddressType(QLowEnergyController::PublicAddress);

        connect(controller, &QLowEnergyController::connected,
                this, &GetServer::serverConnected);
        connect(controller, &QLowEnergyController::disconnected,
                this, &GetServer::serverDisconnected);
        connect(controller, &QLowEnergyController::errorOccurred,
                this, &GetServer::serverError);
        connect(controller, &QLowEnergyController::serviceDiscovered,
                this, &GetServer::checkService);
        connect(controller, &QLowEnergyController::discoveryFinished,
                this, &GetServer::scanServiceFinished);
        controller->connectToDevice();

        qDebug()<<"Controller working";
    }

    qDebug()<<"Controlller is"<<controller;
    lastServer.setServer(currentServer.getServer());
}

void GetServer::retry() {
    if (controller) {
        if (controller->state() != QLowEnergyController::UnconnectedState)
            controller->disconnectFromDevice();
        delete controller;
        controller = nullptr;
    }
    m_serverconnect = 0;
    emit updateServerconnect();
    startGetService(currentServer.getAddress());
}

void GetServer::disconnectServer() {
    delete controller;
    controller = nullptr;
    m_serverconnect = 4;
    emit updateServerconnect();
}

void GetServer::checkController() {
    if (controller)
        qDebug()<<controller->state();
}

void GetServer::checkService(const QBluetoothUuid& newService) {
    qDebug()<<"Get new service "<<newService.toString();
    if (newService ==
        QBluetoothUuid(QBluetoothUuid::ServiceClassUuid::HeartRate))
        m_serverconnect = -1;
}

void GetServer::serverConnected() {
    qDebug()<<"Server Connected";
    controller->discoverServices();
    m_serverconnect = 1;
    emit updateServerconnect();
}

void GetServer::serverDisconnected() {
    qDebug()<<"Server Disconnected";
    setMsg(QString::fromStdString("连接断开"));
    m_serverconnect = 4;
    emit updateServerconnect();
}

void GetServer::serverError(const QLowEnergyController::Error& errorInfo) {
    setMsg(QString::fromStdString("扫描服务的时候发生错误 \n")+controller->errorString());
    m_serverconnect = 3;
    emit updateServerconnect();
}

void GetServer::scanServiceFinished() {

    qDebug()<<"Service scanning finished";

    if (m_serverconnect != -1) {
        setMsg(QString::fromStdString("无法连接"));
        m_serverconnect = 3;
        emit updateServerconnect();
        return;
    }

    setMsg(QString::fromStdString("连接成功"));
    m_serverconnect = 2;
    emit updateServerconnect();

    if (service) {
        delete service;
        service = nullptr;
    }

    service = controller->createServiceObject(
              QBluetoothUuid(
              QBluetoothUuid::ServiceClassUuid::HeartRate), this);

    if (service) {
        connect(service, &QLowEnergyService::stateChanged,
                this, &GetServer::serviceStatusChanged);
        connect(service, &QLowEnergyService::characteristicChanged,
                this, &GetServer::serviceDataChanged);
        connect(service, &QLowEnergyService::descriptorWritten,
                this, &GetServer::serverStatusChanged);
        service->discoverDetails();
    }
}

void GetServer::serviceStatusChanged(const QLowEnergyService::ServiceState& status) {
    switch (status) {
    case QLowEnergyService::RemoteServiceDiscovering:
        m_serverconnect = 5;
        emit updateServerconnect();
        break;
    case QLowEnergyService::RemoteServiceDiscovered: {
        m_serverconnect = 5;
        emit updateServerconnect();
        const QLowEnergyCharacteristic data =
                service->characteristic(
                QBluetoothUuid(
                QBluetoothUuid::CharacteristicType::HeartRateMeasurement));

        if (!data.isValid()) {
            setMsg(QString::fromStdString("未收到数据"));
            m_serverconnect = 3;
            break;
        }

        notistatus = data.descriptor(
            QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration);
        if (notistatus.isValid())
            service->writeDescriptor(notistatus,
                                     QByteArray::fromHex("0100"));

        break;
    }
    default: break;
    }
}

void GetServer::serviceDataChanged(const QLowEnergyCharacteristic& cha,
                                   const QByteArray& value) {
    if (cha.uuid() !=
        QBluetoothUuid(QBluetoothUuid::CharacteristicType::HeartRateMeasurement))
        return;

    auto data = reinterpret_cast <const qint8 *> (value.constData());
    quint8 flags = *data;
    int dataX = 0;
    int dataY = 0;
    int dataClick = 0;

    //以下是为了跨平台考虑，需要验证数据是否为16位
    if (flags & 0x1) {
        dataX = static_cast <int> (
            qFromLittleEndian <qint16> (data[1]));
        dataY = static_cast <int> (
            qFromLittleEndian <qint16> (data[2]));
        dataClick = static_cast <int> (
            qFromLittleEndian <qint16> (data[3]));
    }
    else {
        dataX = static_cast <int> (data[1]);
        dataY = static_cast <int> (data[2]);
        dataClick = static_cast <int> (data[3]);
    }

    qDebug()<<dataX<<" "<<dataY<<" "<<dataClick;

    if (m_data != dataX) {
        m_data = dataX;
        emit updateData();
    }
#if defined(Q_OS_MACOS) || defined(Q_OS_WIN)
    mouseMove.moveMouse(dataX, dataY, dataClick);
#endif
}

void GetServer::serverStatusChanged(const QLowEnergyDescriptor& desciptor, const QByteArray& value) {
    if (desciptor.isValid() &&
        desciptor == notistatus &&
        value == QByteArray::fromHex("0000")) {
        controller -> disconnectFromDevice();
        delete service;
        service = nullptr;
    }
}

void GetServer::setMsg(const QString& newMsg) {
    m_msg = newMsg;
    m_msgbox = true;
    emit updateMsg();
    emit updateMsgbox();
}

void GetServer::setMsgbox(const bool& newStatus) {
    m_msgbox = newStatus;
    emit updateMsgbox();
}

QString GetServer::getMsg() {
    return m_msg;
}

bool GetServer::getMsgbox() {
    return m_msgbox;
}

bool GetServer::getAgentstart() {
    return m_agentstart;
}
void GetServer::setAgentstart(const bool& newAgentStart) {
    m_agentstart = newAgentStart;
    emit updateAgentstart();
}

QVariant GetServer::getServerlist() {
    return QVariant::fromValue(serverList);
}

int GetServer::getServerconnect() {
    return m_serverconnect;
}

int GetServer::getData() {
    return m_data;
}
