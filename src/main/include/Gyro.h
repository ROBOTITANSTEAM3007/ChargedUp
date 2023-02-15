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
    // IMU
    static inline frc::ADIS16470_IMU imu{};
    // NOTE: I think the IMU measures acceleration in 'g' (g-force)

    // Robot Kinematics
    static inline Vector3D 
    acceleration {Vector3D::zero()},
    velocity {Vector3D::zero()},
    position {Vector3D::zero()},
    normalize {0, 0, -1};

    // Update the acceleration, velocity, & position
    static void update()
    {
        current_tick = std::chrono::high_resolution_clock::now();

        if (initiallized)
        {
            // 1 Second = 1,000,000 Microseconds
            // 1 Second = 1,000 Milliseconds
            double delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_tick - previous_tick).count();
            
            // acceleration.set(Vector3D{filtered_acceleration_x, filtered_acceleration_y, filtered_acceleration_z}.add(normalize).deadzone(deadzone_value));
            acceleration.set(Vector3D{(double)Gyro::imu.GetAccelX(), (double)Gyro::imu.GetAccelY(), (double)Gyro::imu.GetAccelZ()}.add(normalize).deadzone(deadzone_value_acceleration));
            velocity.set(velocity.add(acceleration.mult(METER_PER_SEC_PER_G).mult(delta_time/MILLISECOND_PER_SECOND)).deadzone(deadzone_value_velocity));
            // Vector3D p{velocity.mult(delta_time/MICROSECOND_PER_SECOND)};
            position.set(position.add(velocity));
        }

        initiallized = true;

        previous_tick = std::chrono::high_resolution_clock::now();
    }
};