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

    PID gyro_PID{0.05, 0.003, 0};
    frc2::PIDController gyro_PID_controller{gyro_PID.proportion, gyro_PID.integral, gyro_PID.derivative};

    Gyro();

    void auto_level(Drive &);
    void reset();
};