#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTableEntry.h>
#include <networktables/NetworkTableValue.h>

class Limelight
{
    auto Limelight::get_table()
    {
        nt::NetworkTableInstance network_instance = nt::NetworkTableInstance::GetDefault();

        return network_instance.GetTable("limelight");
    };

    static void put_data(const std::string name, double data)
    {
        return get_table()
    }

    static double get_data(const std::string, double = 0)
    {

    }


};