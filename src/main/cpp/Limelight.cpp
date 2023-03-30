#include "Limelight.h"
#include <frc/smartdashboard/SmartDashboard.h>

void Limelight::toggle_led(short toggle_type)
{
    Limelight::put_data("pipeline", 0);

    switch (toggle_type)
    {
    case LED::ON:
        Limelight::put_data("ledMode", 3);
        break;
    case LED::OFF:
        Limelight::put_data("ledMode", 1);
        break;
    default:
        if (Limelight::get_data("ledMode", 1) == 1)
        {
            Limelight::put_data("ledMode", 3);
        }
        else
        {
            Limelight::put_data("ledMode", 1);
        }
        break;
    }
}

void Limelight::toggle_camera(short toggle_type)
{
    switch (toggle_type)
    {
    case CAM::COMPUTER:
        Limelight::put_data("pipeline", 0);
        break;
    case CAM::DRIVER:
        Limelight::put_data("pipeline", 1);
        break;
    default:
        if (Limelight::get_data("pipeline", 0) == 0)
        {
            Limelight::put_data("pipeline", 1);
        }
        else
        {
            Limelight::put_data("pipeline", 0);
        }
        break;
    }
}

void Limelight::retroreflective_auto_align(Drive &drive)
{
    visible_target = get_data("tv", 0);
    
    horizontal_offset = get_data("tx", 0); // -27 degrees to 27 degrees (54 degrees)
    vertical_offset = get_data("ty", 0); // -20.5 degrees to 20.5 degrees (41 degrees)

    vertical_offset += VERTICAL_DISTANCE_OFFSET;

    if (visible_target == 1) // If target is visible
    {  
        std::cout << "Target Found!" << std::endl;

        percentage_horizontal_offset = horizontal_offset / 27;
        percentage_vertical_offset = 0.4;

        // if (fabs(horizontal_offset) > 0.1)
        // {
        //     vertical_offset = 0;
        // }

        drive.speed += Vector2D{0, std::clamp(motion_PID_controller.Calculate(horizontal_offset, 0), -0.50, 0.50)};
    }
    else
    {
        std::cout << "No Target!" << std::endl;
    }
}