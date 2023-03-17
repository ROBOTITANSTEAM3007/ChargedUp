#pragma once

#include <chrono>

#include <frc/ADIS16470_IMU.h>
// #include <frc/filter/LinearFilter.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "Vector3D.h"
#include "Drive.h"

#define METER_PER_SEC_PER_G 9.80665
#define MICROSECOND_PER_SECOND 1000000
#define MILLISECOND_PER_SECOND 1000

class Gyro
{
private:
    double current_angle;

public:
    // IMU
    frc::ADIS16470_IMU imu;

    Gyro();

    void auto_level(Drive &);
};