
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
    target_skew = get_data("ts", 0);
    target_area = get_data("ta", 0);

    if (visible_target == 1)
    {  
        // std::cout << "Target Found!" << std::endl;

        percentage_horizontal_offset = horizontal_offset / 27;
        percentage_vertical_offset = vertical_offset / 20.5;
        percentage_skew_offset = convert_angle(target_skew) / 10;

        // if (fabs(percentage_skew_offset) > 0.3)
        // {
        //     percentage_horizontal_offset = 0;
        // }
        // else
        // {
        //     percentage_skew_offset = 0;
        // }

        frc::SmartDashboard::PutNumber("Skew Offset", percentage_skew_offset);

        drive.speed *= Vector3D{1, 1, 0};
        // Note: tx shows the amount that the robot needs to rotate while ts is the amount of horizontal movment of the robot.
        drive.speed += Vector3D{0, percentage_skew_offset * motion_pid.proportion, percentage_horizontal_offset * motion_pid.proportion}.minimum(motion_limits);
        drive.orientation = units::degree_t {0};
    }
    else
    {
        std::cout << "No Target!" << std::endl;
    }
}