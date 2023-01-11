#pragma once
#include <frc/Joystick.h>
#include <rev/CANSparkMax.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/Spark.h>

class Drive {
    public:
        void sparkMax(rev::CANSparkMax* leftSide, rev::CANSparkMax* rightSide);
        //void frcSpark(frc::Spark* leftSide, frc::Spark* rightSide);
        void drive(float x, float y);

        static const double stickDeadzone = 0.1;
        static const double stickSensitivity = 1;

    protected
        rev::CANSparkMax* rightMaxDrive;
        rev::CANSparkMax* leftMaxDrive;
        frc::Spark* rightSparkDrive;
        frc::Spark* leftSparkDrive;    
}
