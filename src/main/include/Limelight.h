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
    static std::shared_ptr<nt::NetworkTable> get_table()
    {
        nt::NetworkTableInstance network_instance = nt::NetworkTableInstance::GetDefault();

        return network_instance.GetTable("limelight");
    };

public:
    static void put_data(const std::string name, double data)
    { get_table()->PutNumber(name, data); }

    static double get_data(const std::string name, double fail = 0)
    { return get_table()->GetNumber(name, fail); }

    static void retroreflective_auto(Drive &);
};