/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#ifndef GETSENSOR_H
#define GETSENSOR_H

#include <QObject>


class GetSensor: public QObject {
    Q_OBJECT

    Q_PROPERTY(double x READ getX WRITE setX NOTIFY updateData);
    Q_PROPERTY(double y READ getY WRITE setY NOTIFY updateData);
    Q_PROPERTY(double z READ getZ WRITE setZ NOTIFY updateData);

public:
    explicit GetSensor(QObject* parent = nullptr);

    Q_INVOKABLE void startUpdates();

private:
    double m_x;
    double getX() const { return m_x; };
    void setX(const double&){};

    double m_y;
    double getY() const { return m_y; };
    void setY(const double&){};

    double m_z;
    double getZ() const { return m_z; };
    void setZ(const double&){};

signals:
    void updateData();

private slots:
    void updateSensorData();
};

#endif // GETSENSOR_H
