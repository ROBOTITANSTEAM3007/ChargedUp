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

    static inline double deadzone_value {0.02};
public:
    // FILTER
    static inline auto 
    acceleration_filter_x = frc::LinearFilter<double>::MovingAverage(10),
    acceleration_filter_y = frc::LinearFilter<double>::MovingAverage(10),
    acceleration_filter_z = frc::LinearFilter<double>::MovingAverage(10);

    // frc::LinearFilter<double> filter = frc::LinearFilter<double>::MovingAverage(5);

    // IMU
    static inline frc::ADIS16470_IMU imu{};
    // NOTE: I think the IMU measures acceleration in 'g' (g-force)

    // Robot Kinematics
    static inline Vector3D 
    acceleration {Vector3D::zero()},
    velocity {Vector3D::zero()},
    position {Vector3D::zero()},
    normalize {-0.03, 0.05, -1};

    // Update the acceleration, velocity, & position
    static void update()
    {
        current_tick = std::chrono::high_resolution_clock::now();

        if (initiallized)
        {
            // 1 Second = 1,000,000 Microseconds
            // 1 Second = 1,000 Milliseconds
            double delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_tick - previous_tick).count();

            // std::cout << delta_time << std::endl;

            static double 
            filtered_acceleration_x = Gyro::acceleration_filter_x.Calculate((double)Gyro::imu.GetAccelX()),
            filtered_acceleration_y = Gyro::acceleration_filter_y.Calculate((double)Gyro::imu.GetAccelY()),
            filtered_acceleration_z = Gyro::acceleration_filter_z.Calculate((double)Gyro::imu.GetAccelZ());

            acceleration.set(Vector3D{filtered_acceleration_x, filtered_acceleration_y, filtered_acceleration_z}.add(normalize).minimum(deadzone_value));
            velocity.set(velocity.add(acceleration.mult(METER_PER_SEC_PER_G).mult(delta_time/MILLISECOND_PER_SECOND)));
            // Vector3D p{velocity.mult(delta_time/MICROSECOND_PER_SECOND)};
            position.set(position.add(velocity));
        }

        initiallized = true;

        previous_tick = std::chrono::high_resolution_clock::now();
    }
};