#pragma once

#include <chrono>

#include <frc/ADIS16470_IMU.h>

#define METER_PER_SEC_PER_G 9.80665
#define MICROSECOND_PER_SECOND 1000000

struct Vector3D
{
    double x, y, z;

    Vector3D(double t_x, double t_y, double t_z)
    {
        x = t_x;
        y = t_y;
        z = t_z;
    };

    Vector3D(Vector3D &t_vector)
    {
        x = t_vector.x;
        y = t_vector.y;
        z = t_vector.z;
    };

    void set(const Vector3D &t_vector)
    {
        x = t_vector.x;
        y = t_vector.y;
        z = t_vector.z;
    }

    void set(double t_x, double t_y, double t_z)
    {
        x = t_x;
        y = t_y;
        z = t_z;
    }

    Vector3D get()
    { return Vector3D{x, y, z}; }


    // Addition & Subtraction
    Vector3D add(const Vector3D &t_vector)
    { return Vector3D{x + t_vector.x, y + t_vector.y, z + t_vector.z}; }

    Vector3D sub(const Vector3D &t_vector)
    { return Vector3D{x - t_vector.x, y - t_vector.y, z - t_vector.z}; }

    Vector3D add(double t_x, double t_y, double t_z)
    { return Vector3D{x + t_x, y + t_y, z + t_z}; }

    Vector3D sub(double t_x, double t_y, double t_z)
    { return Vector3D{x - t_x, y - t_y, z - t_z}; }

    // Division & Multiplication
    Vector3D div(double value)
    { return Vector3D{x / value, y / value, z / value}; }

    Vector3D mult(double value)
    { return Vector3D{x * value, y * value, z * value}; }

    Vector3D div(const Vector3D &t_vector)
    { return Vector3D{x / t_vector.x, y / t_vector.y, z / t_vector.z}; }

    Vector3D mult(const Vector3D &t_vector)
    { return Vector3D{x * t_vector.x, y * t_vector.y, z * t_vector.z}; }

    // Other
    Vector3D minimum(double value)
    {
        return Vector3D
        {
            (fabs(x) < value ? x : value),
            (fabs(y) < value ? y : value),
            (fabs(z) < value ? z : value)
        };
    }

    Vector3D minimum(const Vector3D &t_vector)
    {
        return Vector3D
        {
            (fabs(x) < t_vector.x ? x : t_vector.x),
            (fabs(y) < t_vector.y ? y : t_vector.y),
            (fabs(z) < t_vector.z ? z : t_vector.z)
        };
    }

    Vector3D maximum(double value)
    {
        return Vector3D
        {
            (fabs(x) > value ? x : value),
            (fabs(y) > value ? y : value),
            (fabs(z) > value ? z : value)
        };
    }

    Vector3D maximum(const Vector3D &t_vector)
    {
        return Vector3D
        {
            (fabs(x) > t_vector.x ? x : t_vector.x),
            (fabs(y) > t_vector.y ? y : t_vector.y),
            (fabs(z) > t_vector.z ? z : t_vector.z)
        };
    }

    static Vector3D zero()
    { return Vector3D{0, 0, 0}; }

    static Vector3D one()
    { return Vector3D{1, 1, 1}; }
};

class Gyro
{
private:
    static inline bool initiallized {false};

    static inline std::chrono::high_resolution_clock::time_point current_tick, previous_tick;

    static inline double deadzone_value {0.02};
public:
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
            double delta_time = std::chrono::duration_cast<std::chrono::microseconds>(current_tick - previous_tick).count();

            // std::cout << delta_time << std::endl;

            acceleration.set(Vector3D{(double)imu.GetAccelX(), (double)imu.GetAccelY(), (double)imu.GetAccelZ()}.add(normalize).deadzone(deadzone_value).mult(METER_PER_SEC_PER_G));
            velocity.set(velocity.add(acceleration.mult(delta_time/MICROSECOND_PER_SECOND)));
            // Vector3D p{velocity.mult(delta_time/MICROSECOND_PER_SECOND)};
            position.set(position.add(velocity));
        }

        initiallized = true;

        previous_tick = std::chrono::high_resolution_clock::now();
    }
};