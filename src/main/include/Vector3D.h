#pragma once
#include <cmath>

#define M_PI 3.14159265358979323846

struct Vector3D
{
    double x, y, z;

    Vector3D(double t_x, double t_y, double t_z)
    {
        x = t_x;
        y = t_y;
        z = t_z;
    };

    Vector3D() {
        x = 0;
        y = 0;
        z = 0;
    };

    Vector3D(Vector3D &t_vector)
    {
        x = t_vector.x;
        y = t_vector.y;
        z = t_vector.z;
    };


    void operator = (const Vector3D &t_vector)
    {
        x = t_vector.x;
        y = t_vector.y;
        z = t_vector.z;
    }

    void operator += (const Vector3D &t_vector)
    { x += t_vector.x; y += t_vector.y; z += t_vector.z; }

    void operator += (double value)
    { x += value; y += value; z += value; }

    void operator -= (const Vector3D &t_vector)
    { x -= t_vector.x; y -= t_vector.y; z -= t_vector.z; }

    void operator -= (double value)
    { x -= value; y -= value; z -= value; }

    void operator *= (const Vector3D &t_vector)
    { x *= t_vector.x; y *= t_vector.y; z *= t_vector.z; }

    void operator *= (double value)
    { x *= value; y *= value; z *= value; }

    void operator /= (const Vector3D &t_vector)
    { x /= t_vector.x; y /= t_vector.y; z /= t_vector.z; }

    void operator /= (double value)
    { x /= value; y /= value; z /= value; }

    Vector3D get()
    { return Vector3D{x, y, z}; }

    // Addition & Subtraction
    Vector3D operator + (const Vector3D &t_vector)
    { return Vector3D{x + t_vector.x, y + t_vector.y, z + t_vector.z}; }

    Vector3D operator - (const Vector3D &t_vector)
    { return Vector3D{x - t_vector.x, y - t_vector.y, z - t_vector.z}; }

    // Division & Multiplication
    Vector3D operator * (const Vector3D &t_vector)
    { return Vector3D{x * t_vector.x, y * t_vector.y, z * t_vector.z}; }

    Vector3D operator * (double value)
    { return Vector3D{x * value, y * value, z * value}; }

    Vector3D operator / (const Vector3D &t_vector)
    { return Vector3D{x / t_vector.x, y / t_vector.y, z / t_vector.z}; }

    Vector3D operator / (double value)
    { return Vector3D{x / value, y / value, z / value}; }

    // Other
    Vector3D minimum(double value)
    {
        return Vector3D
        {
            (x < value ? x : value),
            (y < value ? y : value),
            (z < value ? z : value)
        };
    }

    Vector3D minimum(const Vector3D &t_vector)
    {
        return Vector3D
        {
            (x < t_vector.x ? x : t_vector.x),
            (y < t_vector.y ? y : t_vector.y),
            (z < t_vector.z ? z : t_vector.z)
        };
    }

    Vector3D maximum(double value)
    {
        return Vector3D
        {
            (x > value ? x : value),
            (y > value ? y : value),
            (z > value ? z : value)
        };
    }

    Vector3D maximum(const Vector3D &t_vector)
    {
        return Vector3D
        {
            (x > t_vector.x ? x : t_vector.x),
            (y > t_vector.y ? y : t_vector.y),
            (z > t_vector.z ? z : t_vector.z)
        };
    }

    Vector3D abs()
    { return Vector3D{fabs(x), fabs(y), fabs(z)}; }

    static Vector3D zero()
    { return Vector3D{0, 0, 0}; }

    static Vector3D one()
    { return Vector3D{1, 1, 1}; }
};