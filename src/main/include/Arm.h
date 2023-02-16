// #pragma once

// // ARM LAYOUT
// // Hand Motor
// // Claw Pnumatic
// // Shoulder Motor

// // Shoulder Encoder
// // 


#include <frc/Solenoid.h>
#include <frc/Encoder.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/AnalogInput.h>
#include <fstream>

#include <rev/CANSparkMax.h>


#include "Vector2D.h"
#include "Robot.h"

// Height limit is 78 inches
#define UPPER_ARM_LENGTH 15.6 // inches

#define MAX_ARM_EXTENSION 35.3 // inches
#define MIN_ARM_EXTENSION 0 // inches

#define MAX_ARM_ROTATION 360 // degrees
#define MIN_ARM_ROTATION 0 // degrees


// NOTE!: 50in is the max length the arm can extend to stay inside the hight limit.
//        23.7in is the arm's length when retracted.
//        26.3in is the extension of the arm from 23.7in to make the lower arm's length equal to 50in.
//        35.3in is the maximum extension of the arm from 23.7in.
class Arm {
    private:

        frc::AnalogInput analogExt{0};

        std::fstream fs;


        //motors
        short
        upper_arm_motor_ID { 5 },
        lower_left_arm_motor_ID { 6 },
        lower_right_arm_motor_ID { 7 },


//         //pneumatics
//         hand_solenoid_channel { 0 },


        //encoders
        shoulder_encoder_channel { 0 };

        double angle_offset;

        float maxArmLength = 54.4;

        float calibPoint1 = 0, calibPoint2 = 0;

        float extensionSlope = 0;

        float extensionLength; //measured in inches sadly.

        float extension_offset;

        frc::Solenoid hand_solenoid{frc::PneumaticsModuleType::CTREPCM, hand_solenoid_channel};

        frc::DutyCycleEncoder encoder{shoulder_encoder_channel};

    public:
        double 
        target_extension{0}, // 0 - 35.3 inches
        target_angle{0};

        //declarations
        rev::CANSparkMax
        upper_arm_motor{upper_arm_motor_ID, rev::CANSparkMax::MotorType::kBrushless},
        lower_arm_motor{lower_arm_motor_ID, rev::CANSparkMax::MotorType::kBrushless};

        void reset_encoder()
        { encoder.Reset();}

        Arm();

        double rotation()
        { return encoder.GetAbsolutePosition(); } // Degrees
        
        double extension()
        { return extensionLength;}

        double distance()
        { return sqrt(pow(/*arm extension*/1, 2) * pow(UPPER_ARM_LENGTH, 2)); }

        void calibrate(frc::Joystick *stick); //Linear regression from arm at shortest and longest extension
        {
            target_angle = /*Correct Angle Here*/0;
            bool finished_rotation {update_rotation()};

        void cone_auto_place_high();

        static bool update_extension()
        {
            double extension_offset{fmax(fmin(target_extension, MAX_ARM_EXTENSION), MIN_ARM_EXTENSION) - extension()};

            lower_right_arm_motor.Set(fmin(extension_offset, 1));

            if (fabs(extension_offset) < 0.01)
            {
                std::cout << "Correct Extension" << extension() << std::endl;
                return true;
            }

            return false;
        }

        static bool update_rotation()
        {
            double angle_offset{fmax(fmin(target_angle, MAX_ARM_ROTATION), MIN_ARM_ROTATION) - rotation()};

            upper_arm_motor.Set(fmin(angle_offset, 1));

            if (fabs(angle_offset) < 0.01)
            {
                std::cout << "Correct Rotation" << rotation() << std::endl;
                return true;
            }

            return false;
        }
};  
