/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#ifndef BESERVER_H
#define BESERVER_H

#include <QObject>

#include <QLowEnergyAdvertisingData>
#include <QLowEnergyAdvertisingParameters>

#include <QLowEnergyCharacteristic>
#include <QLowEnergyCharacteristicData>

#include <QLowEnergyService>
#include <QLowEnergyServiceData>

#include <QLowEnergyDescriptorData>
#include <QLowEnergyController>

using namespace std;

class BeServer: public QObject {
    Q_OBJECT

public:
    Q_PROPERTY(bool msgbox READ getMsgbox WRITE setMsgbox NOTIFY updateMsgbox);
    Q_PROPERTY(QString msg READ getMsg WRITE setMsg NOTIFY updateMsg);
    Q_PROPERTY(bool clientconnect READ getClientconnect WRITE setClientconnect NOTIFY updateClientconnect);
    Q_PROPERTY(bool senddata READ getSenddata WRITE setSenddata NOTIFY updateSenddata);
    Q_PROPERTY(int sig READ getSiga WRITE setSiga NOTIFY updateSiga);
    Q_PROPERTY(int speed READ getSpeed WRITE setSpeed NOTIFY updateSpeed);

    Q_INVOKABLE void startAdvertising();
    Q_INVOKABLE void generateData();
    Q_INVOKABLE void motionData(const double&, const double&, const int&);
    Q_INVOKABLE void disconnectClient();
    Q_INVOKABLE void connectClient();
    Q_INVOKABLE void changeSpeed();

    explicit BeServer(QObject *parent = nullptr);
    ~BeServer();

private:
    bool m_msgbox = false;
    bool getMsgbox();
    void setMsgbox(const bool&);

    QString m_msg;
    QString getMsg();
    void setMsg(const QString&);

    bool m_clientconnect = false;
    bool getClientconnect();
    void setClientconnect(const bool&){};

    bool m_senddata = true;
    bool getSenddata();
    void setSenddata(const bool&);

    int m_sig = 0;
    int getSiga();
    void setSiga(const int& newSig);

    int m_speed = 1;
    int getSpeed();
    void setSpeed(const int&);

    QLowEnergyAdvertisingData advertisingData;
    QLowEnergyCharacteristicData characteristicData;
    QLowEnergyServiceData serviceData;

    QLowEnergyController *controller = nullptr;
    QLowEnergyService *service = nullptr;

    quint8 dataX = 0;
    quint8 dataY = 0;
    quint8 dataClick = 0;

    void provideData(const int&, const int&, const int&);

private slots:
    void errorOccurred(const QLowEnergyController::Error&);
    void clientDisconnected();
    void clientConnected();

signals:
    void updateMsgbox();
    void updateMsg();
    void updateClientconnect();
    void updateSenddata();
    void updateSiga();
    void updateSpeed();
};

#endif // BESERVER_H
