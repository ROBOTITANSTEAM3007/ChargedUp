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

    // ~Vector2D();

    void set(const Vector2D &t_vector)
    {
        x = t_vector.x;
        y = t_vector.y;
    }

    void set(double t_x, double t_y)
    {
        x = t_x;
        y = t_y;
    }

    Vector2D get()
    { return Vector2D{x, y}; }


    // Addition & Subtraction
    Vector2D add(const Vector2D &t_vector)
    { return Vector2D{x + t_vector.x, y + t_vector.y}; }

    Vector2D sub(const Vector2D &t_vector)
    { return Vector2D{x - t_vector.x, y - t_vector.y}; }

    Vector2D add(double t_x, double t_y)
    { return Vector2D{x + t_x, y + t_y}; }

    Vector2D sub(double t_x, double t_y)
    { return Vector2D{x - t_x, y - t_y}; }

    // Division & Multiplication
    Vector2D div(double value)
    { return Vector2D{x / value, y / value}; }

    Vector2D mult(double value)
    { return Vector2D{x * value, y * value}; }

    Vector2D div(const Vector2D &t_vector)
    { return Vector2D{x / t_vector.x, y / t_vector.y}; }

    Vector2D mult(const Vector2D &t_vector)
    { return Vector2D{x * t_vector.x, y * t_vector.y}; }

    // Other
    Vector2D minimum(double value)
    {
        return Vector2D
        {
            (fabs(x) < value ? x : value),
            (fabs(y) < value ? y : value)
        };
    }

    Vector2D minimum(const Vector2D &t_vector)
    {
        return Vector2D
        {
            (fabs(x) < t_vector.x ? x : t_vector.x),
            (fabs(y) < t_vector.y ? y : t_vector.y)
        };
    }

    Vector2D maximum(double value)
    {
        return Vector2D
        {
            (fabs(x) > value ? x : value),
            (fabs(y) > value ? y : value)
        };
    }

    Vector2D maximum(const Vector2D &t_vector)
    {
        return Vector2D
        {
            (fabs(x) > t_vector.x ? x : t_vector.x),
            (fabs(y) > t_vector.y ? y : t_vector.y)
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

    static Vector2D zero()
    { return Vector2D{0, 0}; }

    static Vector2D one()
    { return Vector2D{1, 1}; }
};