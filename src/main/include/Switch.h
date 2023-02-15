#pragma once

#include "Button.h"
#include <frc/DigitalInput.h>

struct Switch
{
    short 
    port,
    type;

    bool
    was_read{ false },
    active,
    disabled{ false };

    frc::DigitalInput *object;

    Switch(short t_port, short t_type)
    {
        port = t_port;
        object = new frc::DigitalInput{port};
        type = t_type;

        if (type == RELEASE) { was_read = true; }
    }

    void update()
    {
        bool switch_pressed {object->Get()};

        switch (type)
        {
        case ALL:
            active = switch_pressed;
            break;
        case PRESS:
            active = false;

            if (switch_pressed && !was_read)
            {
                active = true;
                was_read = true;
            }
            else if (!switch_pressed && was_read)
            {
                was_read = false;
            }
            break;
        case RELEASE:
            active = false;

            if (!switch_pressed && !was_read)
            {
                active = true;
                was_read = true;
            }
            else if (switch_pressed && was_read)
            {
                was_read = false;
            }
            break;
        default:
            break;
        }

        // previous_state = object->Get();
    }

    bool is_active()
    {
        update();

        if (disabled)
        { return false; }

        return active;
    }

    void disable()
    { disabled = true; }

    void enable()
    { disabled = false; }
};