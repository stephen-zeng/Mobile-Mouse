/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#include "beserver.h"

#include <QList>
#include <QTimer>
#include <QPermissions>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QStandardPaths>

using namespace std;

BeServer::BeServer(QObject *parent)
    : QObject(parent) {
#if defined(Q_OS_IOS)
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
#elif defined(Q_OS_ANDROID)
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#else
    QString path = ".";
#endif

    file = path + "/mobileConfig";
    // qDebug()<<file;
    if (!QFile::exists(file)) {
        qDebug()<<"New File";
        QFile mobileConfig(file);
        QString tmp = "SZ Remote Device";
        mobileConfig.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&mobileConfig);
        // out.setEncoding(QStringConverter::Utf8);  // 设置编码为UTF-8，方便中文
        out<<tmp;
        mobileConfig.close();
    }

    // qDebug()<<QFile::exists(file);

    QFile mobileConfig(file);
    mobileConfig.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&mobileConfig);
    // in.setEncoding(QStringConverter::Utf8);
    m_name = in.readAll();

    mobileConfig.close();
    // qDebug()<<"Start Advising"<<m_name;

    advertisingData.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);
    advertisingData.setIncludePowerLevel(true);
    advertisingData.setServices(
        QList <QBluetoothUuid>() <<
        QBluetoothUuid::ServiceClassUuid::HeartRate);

    characteristicData.setUuid(QBluetoothUuid::CharacteristicType::HeartRateMeasurement);
    characteristicData.setValue(QByteArray(2, 0));
    characteristicData.setProperties(QLowEnergyCharacteristic::Notify);
    const QLowEnergyDescriptorData config(
        QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration,
        QByteArray(2, 0));
    characteristicData.addDescriptor(config);

    serviceData.setType(QLowEnergyServiceData::ServiceTypePrimary);
    serviceData.setUuid(QBluetoothUuid::ServiceClassUuid::HeartRate);
    serviceData.addCharacteristic(characteristicData);

}

BeServer::~BeServer() {
    delete controller;
    delete service;
}

void BeServer::startAdvertising() {
    QFile mobileConfig(file);
    mobileConfig.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&mobileConfig);
    // out.setEncoding(QStringConverter::Utf8);
    out<<m_name;
    mobileConfig.close();
    // qDebug()<<m_name;
    advertisingData.setLocalName(m_name);

    delete controller;
    controller = QLowEnergyController::createPeripheral();
    connect(controller, &QLowEnergyController::errorOccurred,
            this, &BeServer::errorOccurred);
    connect(controller, &QLowEnergyController::disconnected,
            this, &BeServer::clientDisconnected);
    connect(controller, &QLowEnergyController::connected,
            this, &BeServer::clientConnected);

    service = controller->addService(serviceData);
    controller->startAdvertising(QLowEnergyAdvertisingParameters(),
                                 advertisingData,
                                 advertisingData);

    qDebug()<<"Start Advertising "<<m_name;
}

void BeServer::errorOccurred(const QLowEnergyController::Error& errorInfo) {
    qDebug()<<errorInfo;
    if (errorInfo ==
        QLowEnergyController::RemoteHostClosedError)
        setMsg(QString::fromStdString("对面设备发生错误"));
    else
        setMsg(QString::fromStdString("本机发生错误"));
}

void BeServer::clientDisconnected() {
    delete service;
    service = controller->addService(serviceData);
    controller->startAdvertising(QLowEnergyAdvertisingParameters(),
                                 advertisingData,
                                 advertisingData);
    m_clientconnect = false;
    emit updateClientconnect();
}

void BeServer::clientConnected() {
    m_clientconnect = true;
    emit updateClientconnect();
}

void BeServer::generateData() {
    int speed = m_speed * 5;
    switch(m_sig) {
    case 1: provideData(0, speed * -1, 0);break;
    case 2: provideData(0, speed, 0);break;
    case 3: provideData(speed * -1, 0, 0);break;
    case 4: provideData(speed, 0, 0);break;
    case 5: provideData(0, 0, 1);break;
    case 6: provideData(0, 0, -1);break;
    case 7: provideData(0, 0, 2);break;
    default: break;
    }
}

void BeServer::motionData(const double& x, const double& y, const int& click) {
    int speed = m_speed * 10;
    int p_x = (int) (x * speed);
    int p_y = (int) (y * speed);
    provideData(p_x, p_y, click);
}

void BeServer::provideData(const int& x, const int& y, const int& click) {
    if (!m_senddata) return;

    qDebug()<<x<<" "<<y<<" "<<click;
    dataX = static_cast <qint8> (x);
    dataY = static_cast <qint8> (y);
    dataClick = static_cast <qint8> (click);

    QByteArray value;
    value.append(char(0)); // 芝士数据包的头
    value.append(char(dataX)); //芝士真实的数据
    value.append(char(dataY)); //芝士真实的数据
    value.append(char(dataClick)); //芝士真实的数据
    QLowEnergyCharacteristic charateristic =
        service->characteristic(QBluetoothUuid::CharacteristicType::HeartRateMeasurement);

    Q_ASSERT(charateristic.isValid()); //用来打断点调试用的

    service->writeCharacteristic(charateristic, value);
}

void BeServer::disconnectClient() {
    controller->disconnectFromDevice();
    controller = nullptr;
    service = nullptr;
    qDebug()<<"Disconnected from Client";
}
void BeServer::connectClient() {
    controller = QLowEnergyController::createPeripheral();
    service = controller->addService(serviceData);
    controller->startAdvertising(QLowEnergyAdvertisingParameters(),
                                 advertisingData,
                                 advertisingData);
    qDebug()<<"Start Advertising, mid-way";
}

void BeServer::setMsg(const QString& newMsg) {
    m_msg = newMsg;
    m_msgbox = true;
    emit updateMsg();
    emit updateMsgbox();
}

void BeServer::setMsgbox(const bool& newStatus) {
    m_msgbox = newStatus;
    emit updateMsgbox();
}

QString BeServer::getMsg() {
    return m_msg;
}

bool BeServer::getMsgbox() {
    return m_msgbox;
}

bool BeServer::getClientconnect() {
    return m_clientconnect;
}

bool BeServer::getSenddata() {
    return m_senddata;
}
void BeServer::setSenddata(const bool& newStatus) {
    if (m_senddata!=newStatus) {
        m_senddata = newStatus;
        emit updateSenddata();
    }
}

int BeServer::getSiga() {
    return m_sig;
}
void BeServer::setSiga(const int& newSig) {
    if (m_sig != newSig) {
        m_sig = newSig;
        emit updateSiga();
    }
}

int BeServer::getSpeed() {
    return m_speed;
}
void BeServer::setSpeed(const int& newSpeed) {
    if (m_speed != newSpeed) {
        m_speed = newSpeed;
        emit updateSpeed();
    }
}
void BeServer::upSpeed() {
    m_speed++;
    if (m_speed>5) m_speed = 1;
    emit updateSpeed();
}
void BeServer::downSpeed() {
    m_speed--;
    if (m_speed<1) m_speed = 5;
    emit updateSpeed();
}

QString BeServer::getName() {
    return m_name;
}
void BeServer::setName(const QString& newName) {
    qDebug()<<"Changing name";
    if (newName != m_name) {
        m_name = newName;
        emit updateName();
    }
}


