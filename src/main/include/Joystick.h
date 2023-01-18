#pragma once

#include <frc/Joystick.h>

struct Joystick
{
    short ID;

    double deadzone, sensitivity, y, x, twist;

    frc::Joystick* object{nullptr};

    Joystick(short t_ID, double t_deadzone, double t_sensitivity)
    {
        ID = t_ID;
        deadzone = t_deadzone;
        sensitivity = t_sensitivity;

        object = new frc::Joystick(t_ID);
    }

    void update(double sens = 1)
    {
        y = object->GetY() * sens;
        x = object->GetX() * sens;
        twist = object->GetTwist() * sens;
    }
};