#pragma once
#include <rev/CANSparkMax.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/Spark.h>

class Drive {
    Drive(rev::CANSparkMax* leftSide, rev::CANSparkMax* rightSide);
    Drive(frc::Spark* leftSide, frc::Spark* rightSide);
    public:
        void vroom(float x, float y);

        static inline double stickDeadzone = 0.1;
        static inline double stickSensitivity = 1;

    protected:
        rev::CANSparkMax* rightMaxDrive;
        rev::CANSparkMax* leftMaxDrive;
        frc::Spark* rightSparkDrive;
        frc::Spark* leftSparkDrive;    
};

