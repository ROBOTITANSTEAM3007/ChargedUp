#pragma once

#include <chrono>

#include <frc/ADIS16470_IMU.h>
#include <frc/filter/LinearFilter.h>

#include "Vector3D.h"

#define METER_PER_SEC_PER_G 9.80665
#define MICROSECOND_PER_SECOND 1000000
#define MILLISECOND_PER_SECOND 1000

class Gyro
{
private:
    static inline bool initiallized {false};

    static inline std::chrono::high_resolution_clock::time_point current_tick, previous_tick;

    static inline double 
    deadzone_value_velocity {0.02},
    deadzone_value_acceleration {0.001};
public:
    // FILTER
/*     static inline auto
        acceleration_filter_x = frc::LinearFilter<double>::MovingAverage(10),
        acceleration_filter_y = frc::LinearFilter<double>::MovingAverage(10),
        acceleration_filter_z = frc::LinearFilter<double>::MovingAverage(10); */

    static double 
    filtered_acceleration_x,
    filtered_acceleration_y,
    filtered_acceleration_z;


    // frc::LinearFilter<double> filter = frc::LinearFilter<double>::MovingAverage(5);

    // IMU
    static inline frc::ADIS16470_IMU imu{};
    // NOTE: I think the IMU measures acceleration in 'g' (g-force)

    // Robot Kinematics
    static inline Vector3D 
    acceleration,
    velocity,
    position,
    normalize {0, 0, -1};

    // Update the acceleration, velocity, & position
    static void update();
};