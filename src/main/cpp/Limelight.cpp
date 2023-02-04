
#include "Limelight.h"

void Limelight::retroreflective_auto_align(Drive &drive)
{
    // put_data("pipeline", 0);

    PID motion_pid{0.25, 0, 0};
    Vector3D motion_limits{0.25, 0.25, 0.5};

    double 
    visible_target { get_data("tv", 0) },
    horizontal_offset { get_data("tx", 0) }, // -27 degrees to 27 degrees (54 degrees)
    vertical_offset {get_data("ty", 0)}, // -20.5 degrees to 20.5 degrees (41 degrees)
    target_skew {get_data("ts", 0)},
    target_area { get_data("ta", 0) };

    if (visible_target == 1)
    {  
        std::cout << "Target Found!" << std::endl;

        double
        percentage_horizontal_offset = horizontal_offset / 27,
        percentage_vertical_offset = vertical_offset / 20.5,
        percentage_skew_offset = target_skew;

        std::cout << percentage_skew_offset << std::endl;

        drive.speed.set(drive.speed.add(-percentage_vertical_offset * motion_pid.proportion, percentage_horizontal_offset * motion_pid.proportion, 0).minimum(motion_limits));
    }
    else
    {
        std::cout << "No Target!" << std::endl;
    }
}