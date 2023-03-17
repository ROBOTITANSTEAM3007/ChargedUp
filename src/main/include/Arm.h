#pragma once

// // ARM LAYOUT
// // Hand Motor
// // Claw Pnumatic
// // Shoulder Motor

// // Shoulder Encoder
// // 


#include <frc/Solenoid.h>
#include <frc/Encoder.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/AnalogPotentiometer.h>
#include <fstream>
#include <frc/Joystick.h>
#include <iostream>
#include <rev/CANSparkMax.h>

#include "Vector2D.h"

// Height limit is 78 inches
#define UPPER_ARM_LENGTH 15.6 // inches

#define MAX_ARM_EXTENSION 35.3 // inches
#define MIN_ARM_EXTENSION 0 // inches

#define MAX_ARM_ROTATION 360 // degrees
#define MIN_ARM_ROTATION 0 // degrees

#define ARM_EXTENSION_CONSTANT 0.0226022305


// NOTE!: 50in is the max length the arm can extend to stay inside the hight limit.
//        23.7in is the arm's length when retracted.
//        26.3in is the extension of the arm from 23.7in to make the lower arm's length equal to 50in.
//        35.3in is the maximum extension of the arm from 23.7in.
class Arm {
    private:
        std::fstream fs;

        // Sensor IDs
        short 
        extension_potentiometer_port { 4 },
        shoulder_encoder_channel { 14 };

        frc::AnalogPotentiometer extension_potentiometer{extension_potentiometer_port}; //0V to 5V
        frc::DutyCycleEncoder encoder{shoulder_encoder_channel};

        // Motor IDs
        short
        upper_arm_motor_ID { 5 },
        lower_arm_motor_ID { 6 };

        // Solenoid IDs
        short
        hand_solenoid_channel { 0 },
        pole_solenoid_channel { 4 };

        double previous_potentiometer_value { 0 };

        float ext[10];

        double avrgExtension;

        short iterations = 0;

        double angle_offset;

        double maxArmLength = 54.4;

        float calibPoint1 = 0, calibPoint2 = 0;

        float extensionSlope = 0;

        float extensionLength; //measured in inches sadly.

        float extension_offset;

        //frc::Solenoid hand_solenoid{frc::PneumaticsModuleType::CTREPCM, hand_solenoid_channel};

    public:

        bool manual {true};

        double target_extension{0}; // 0 - 35.3 inches
        double target_angle{0};

        //declarations
        rev::CANSparkMax
        upper_arm_motor{upper_arm_motor_ID, rev::CANSparkMax::MotorType::kBrushless},
        lower_arm_motor{lower_arm_motor_ID, rev::CANSparkMax::MotorType::kBrushed};

        frc::Solenoid 
        hand_solenoid{frc::PneumaticsModuleType::CTREPCM, hand_solenoid_channel},
        pole_solenoid{frc::PneumaticsModuleType::CTREPCM, pole_solenoid_channel};

        Arm();

        void reset_encoder()
        { encoder.Reset();}

        double rotation()
        { return encoder.GetAbsolutePosition(); } // Degrees
        
        double extension();

        double get_potentiometer_value();

        double distance()
        { return sqrt(pow(/*arm extension*/1, 2) * pow(UPPER_ARM_LENGTH, 2)); }

        void calibrate(frc::Joystick *stick); //Linear regression from arm at shortest and longest extension
 
        void set_direct_extend(float x);

        void set_direct_rotation(float x);

        void periodic();

        void cone_auto_place_high();

};  
