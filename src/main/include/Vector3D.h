#pragma once

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
            (fabs(x) < value ? x : value * (x/fabs(x))),
            (fabs(y) < value ? y : value * (y/fabs(y))),
            (fabs(z) < value ? z : value * (z/fabs(z)))
        };
    }

    Vector3D minimum(const Vector3D &t_vector)
    {
        return Vector3D
        {
            (fabs(x) < t_vector.x ? x : t_vector.x * (x/fabs(x))),
            (fabs(y) < t_vector.y ? y : t_vector.y * (y/fabs(y))),
            (fabs(z) < t_vector.z ? z : t_vector.z * (z/fabs(z)))
        };
    }

    Vector3D maximum(double value)
    {
        return Vector3D
        {
            (fabs(x) > value ? x : value * (x/fabs(x))),
            (fabs(y) > value ? y : value * (y/fabs(y))),
            (fabs(z) > value ? z : value * (z/fabs(z)))
        };
    }

    Vector3D maximum(const Vector3D &t_vector)
    {
        return Vector3D
        {
            (fabs(x) > t_vector.x ? x : t_vector.x * (x/fabs(x))),
            (fabs(y) > t_vector.y ? y : t_vector.y * (y/fabs(y))),
            (fabs(z) > t_vector.z ? z : t_vector.z * (z/fabs(z)))
        };
    }

    Vector3D deadzone(const Vector3D &t_vector)
    {
        return Vector3D
        {
            (fabs(x) > t_vector.x ? x : 0),
            (fabs(y) > t_vector.y ? y : 0),
            (fabs(z) > t_vector.z ? z : 0)
        };
    }

    Vector3D deadzone(double value)
    {
        return Vector3D
        {
            (fabs(x) > value ? x : 0),
            (fabs(y) > value ? y : 0),
            (fabs(z) > value ? z : 0)
        };
    }

    Vector3D abs()
    { return Vector3D{fabs(x), fabs(y), fabs(z)}; }

    static Vector3D zero()
    { return Vector3D{0, 0, 0}; }

    static Vector3D one()
    { return Vector3D{1, 1, 1}; }
};