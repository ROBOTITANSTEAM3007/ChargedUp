
#include "Limelight.h"
#include <frc/smartdashboard/SmartDashboard.h>

double Limelight::convert_angle(double input_angle)
{
    if (input_angle > 45)
    {
        return input_angle - 90;
    }

    return input_angle;
}

void Limelight::retroreflective_auto_align(Drive &drive)
{
    // put_data("pipeline", 0);

    visible_target = get_data("tv", 0);
    
    horizontal_offset = get_data("tx", 0); // -27 degrees to 27 degrees (54 degrees)
    vertical_offset = get_data("ty", 0); // -20.5 degrees to 20.5 degrees (41 degrees)

    if (visible_target == 1) // If target is visible
    {  
        // std::cout << "Target Found!" << std::endl;

        percentage_horizontal_offset = horizontal_offset / 27;
        percentage_vertical_offset = vertical_offset / 20.5;

        drive.speed += Vector2D{0, percentage_horizontal_offset * motion_pid.proportion}.minimum(motion_limits);
    }
    else
    {
        std::cout << "No Target!" << std::endl;
    }
}