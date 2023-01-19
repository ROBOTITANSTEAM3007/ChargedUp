#pragma once

#include <frc/Joystick.h>

enum {ALL, PRESS, RELEASE};

struct Button
{
    short 
    ID, 
    type;

    bool active,
         disabled{ false };

    frc::Joystick* joystick{ nullptr };
    
    Button(short t_ID, frc::Joystick* t_joystick, short t_type = 0)
    {
        ID = t_ID;
        joystick = t_joystick;
        type = t_type;
    }

    void update()
    {
        switch (type)
        {
        case ALL:
            active = joystick->GetRawButton(ID);
            break;
        case PRESS:
            active = joystick->GetRawButtonPressed(ID);
            break;
        case RELEASE:
            active = joystick->GetRawButtonReleased(ID);
            break;
        default:
            break;
        }

        if (disabled)
        { active = false; }
    }

    bool is_active()
    {
        update();

        return active;
    }

    void disable()
    { disabled = true; }

    void enable()
    { disabled = false; }
};
