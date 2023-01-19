#pragma once

#include <frc/Joystick.h>

struct Joystick
{
private:
    double deadzone, sensitivity, y, x, twist;

    double evaluate(double value)
    {
        if (fabs(value) >= deadzone)
        {
            return value * sensitivity;
        }
        else
        {
            return 0;
        }
    }

public:

    short ID;

    frc::Joystick *object{nullptr};

    Joystick(short t_ID, double t_deadzone, double t_sensitivity)
    {
        ID = t_ID;
        deadzone = t_deadzone;
        sensitivity = t_sensitivity;

        object = new frc::Joystick(t_ID);
    }

    double get_y()
    {
        y = object->GetY();

        return evaluate(y);
    }

    double get_x()
    {
        x = object->GetX();

        return evaluate(x);
    }

    double get_twist()
    {
        twist = object->GetTwist();

        return evaluate(twist);
    }
};