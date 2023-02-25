#pragma once

struct Vector2D
{
    double x, y;

    Vector2D(double t_x, double t_y)
    {
        x = t_x;
        y = t_y;
    };

    Vector2D(Vector2D &t_vector)
    {
        x = t_vector.x;
        y = t_vector.y;
    };

    Vector2D()
    {
        x = 0;
        y = 0;
    };

    void operator = (const Vector2D &t_vector)
    { x = t_vector.x; y = t_vector.y; }

    void operator += (const Vector2D &t_vector)
    {  x += t_vector.x; y += t_vector.y; }

    void operator += (double value)
    {  x += value; y += value; }

    void operator -= (const Vector2D &t_vector)
    { x -= t_vector.x; y -= t_vector.y; }

    void operator -= (double value)
    { x -= value; y -= value; }

    void operator *= (const Vector2D &t_vector)
    { x *= t_vector.x; y *= t_vector.y; }

    void operator *= (double value)
    { x *= value; y *= value; }

    void operator /= (const Vector2D &t_vector)
    { x /= t_vector.x; y /= t_vector.y; }

    void operator /= (double value)
    { x /= value; y /= value; }

    Vector2D get()
    { return Vector2D{x, y}; }

    // Addition & Subtraction
    Vector2D operator + (const Vector2D &t_vector)
    { return Vector2D{x + t_vector.x, y + t_vector.y}; }

    Vector2D operator - (const Vector2D &t_vector)
    { return Vector2D{x - t_vector.x, y - t_vector.y}; }

    // Division & Multiplication
    Vector2D operator * (const Vector2D &t_vector)
    { return Vector2D{x * t_vector.x, y * t_vector.y}; }

    Vector2D operator * (double value)
    { return Vector2D{x * value, y * value}; }

    Vector2D operator / (const Vector2D &t_vector)
    { return Vector2D{x / t_vector.x, y / t_vector.y}; }

    Vector2D operator / (double value)
    { return Vector2D{x / value, y / value}; }

    // Other
    Vector2D minimum(double value)
    {
        return Vector2D
        {
            (fabs(x) < value ? x : value * (x/fabs(x))),
            (fabs(y) < value ? y : value * (y/fabs(y)))
        };
    }

    Vector2D minimum(const Vector2D &t_vector)
    {
        return Vector2D
        {
            (fabs(x) < t_vector.x ? x : t_vector.x * (x/fabs(x))),
            (fabs(y) < t_vector.y ? y : t_vector.y * (y/fabs(y)))
        };
    }

    Vector2D maximum(double value)
    {
        return Vector2D
        {
            (fabs(x) > value ? x : value * (x/fabs(x))),
            (fabs(y) > value ? y : value * (y/fabs(y)))
        };
    }

    Vector2D maximum(const Vector2D &t_vector)
    {
        return Vector2D
        {
            (fabs(x) > t_vector.x ? x : t_vector.x * (x/fabs(x))),
            (fabs(y) > t_vector.y ? y : t_vector.y * (y/fabs(y)))
        };
    }

    Vector2D deadzone(const Vector2D &t_vector)
    {
        return Vector2D
        {
            (fabs(x) > t_vector.x ? x : 0),
            (fabs(y) > t_vector.y ? y : 0)
        };
    }

    Vector2D deadzone(double value)
    {
        return Vector2D
        {
            (fabs(x) > value ? x : 0),
            (fabs(y) > value ? y : 0)
        };
    }

    Vector2D abs()
    { return Vector2D{fabs(x), fabs(y)}; }

    static Vector2D zero()
    { return Vector2D{0, 0}; }

    static Vector2D one()
    { return Vector2D{1, 1}; }
};