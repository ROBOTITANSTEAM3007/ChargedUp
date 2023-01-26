
#include "Limelight.h"

void Limelight::retroreflective_auto(frc::MecanumDrive &drive_train)
{
    put_data("pipeline", 0);

    double 
    visible_target { get_data("tv", 0) },
    horizontal_offset { get_data("tx", 0) }, // -27 degrees to 27 degrees (54 degrees)
    target_area { get_data("ta", 0) };

    if (visible_target == 1)
    {  
        std::cout << "Target Found!" << std::endl;

        double percentage_offset = horizontal_offset / 27;

        drive_train.DriveCartesian(0.5 * percentage_offset, 0, 0);
    }
    else
    {
        std::cout << "No Target!" << std::endl;
    }
}