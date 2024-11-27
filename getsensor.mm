/*
Author: Stephen Zeng 曾浩正
Mail: stephenzeng@goforit.top
*/

#include "getsensor.h"
#include <CoreMotion/CoreMotion.h>

CMMotionManager *motionManager;

GetSensor::GetSensor(QObject *parent) : QObject(parent) {}

void GetSensor::startUpdates()
{
    motionManager = [[CMMotionManager alloc] init];
    if (motionManager.deviceMotionAvailable) {
        motionManager.deviceMotionUpdateInterval = 1.0 / 30.0;
        [motionManager startDeviceMotionUpdatesToQueue:[NSOperationQueue mainQueue]
                                           withHandler:^(CMDeviceMotion *motion, NSError *error) {
            if (error) {
                NSLog(@"Motion error: %@", error);
                return;
            }

            m_x = motion.attitude.roll;
            m_y = motion.attitude.pitch;
            m_z = motion.attitude.yaw;

            emit updateData();
        }];
    }
}

void GetSensor::updateSensorData(){}
