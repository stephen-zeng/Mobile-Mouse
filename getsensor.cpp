/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#include "getsensor.h"

#include <QAccelerometer>
#include <QAccelerometerReading>

QAccelerometer* accelerometer = nullptr;
QAccelerometerReading* reading = nullptr;

GetSensor::GetSensor(QObject *parent) : QObject(parent) {}

void GetSensor::startUpdates() {
    accelerometer = new QAccelerometer(this);
    connect(accelerometer, &QAccelerometer::readingChanged,
            this, &GetSensor::updateSensorData);
    accelerometer->start();
}

void GetSensor::updateSensorData() {
    reading = accelerometer->reading();
    m_x = reading->x();
    m_y = reading->y();
    m_z = reading->z();
    m_x /= -6.4;
    m_y /= 6.4;
    m_z /= 6.4;
    emit updateData();
}
