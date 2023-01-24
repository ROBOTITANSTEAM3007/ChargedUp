#pragma once

#include <frc/Joystick.h>

struct Joystick
{
private:
    double y, x, twist;

    double evaluate(double value, double deadzone, double sensitivity)
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

    Joystick(short t_ID)
    {
        ID = t_ID;

        object = new frc::Joystick(t_ID);
    }

    double get_y(double deadzone, double sensitivity)
    {
        y = object->GetY();

        return evaluate(y, deadzone, sensitivity);
    }

    double get_x(double deadzone, double sensitivity)
    {
        x = object->GetX();

        return evaluate(x, deadzone, sensitivity);
    }

    double get_twist(double deadzone, double sensitivity)
    {
        twist = object->GetTwist();

        return evaluate(twist, deadzone, sensitivity);
    }
};