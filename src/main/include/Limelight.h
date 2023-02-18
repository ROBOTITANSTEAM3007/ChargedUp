#pragma once

#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableValue.h>

#include <frc/drive/MecanumDrive.h>
#include <iostream>

#include "Drive.h"

class Limelight
{
private:

    static double convert_angle(double);

public:
    // Motion Properties
    static inline PID motion_pid{0.25, 0, 0};
    static inline Vector3D motion_limits{0.25, 0.25, 0.5};

    // Limelight Networktable Values
    static inline double 
    visible_target,
    horizontal_offset, // -27 degrees to 27 degrees (54 degrees)
    vertical_offset, // -20.5 degrees to 20.5 degrees (41 degrees)
    target_skew,
    target_area;

    // Vision Offsets
    static inline double
    percentage_horizontal_offset,
    percentage_vertical_offset,
    percentage_skew_offset;

    // Connecting To Limelight Network Tables
    static inline nt::NetworkTableInstance network_instance;
    static std::shared_ptr<nt::NetworkTable> get_table()
    {
        network_instance = nt::NetworkTableInstance::GetDefault();

        return network_instance.GetTable("limelight");
    };
    

    static void put_data(const std::string name, double data)
    { get_table()->PutNumber(name, data); }

    static double get_data(const std::string name, double fail = 0)
    { return get_table()->GetNumber(name, fail); }

    static void retroreflective_auto_align(Drive &);
};