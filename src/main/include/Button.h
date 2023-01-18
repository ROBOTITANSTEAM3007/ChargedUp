#pragma once

#include <frc/Joystick.h>

struct Button
{
    short 
    ID, 
    type;

    bool active;

    frc::Joystick* joystick{nullptr};
    
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
        case 0:
            active = joystick->GetRawButton(ID);
            break;
        case 1:
            active = joystick->GetRawButtonPressed(ID);
            break;
        case 2:
            active = joystick->GetRawButtonReleased(ID);
            break;
        default:
            break;
        }
    }
};
