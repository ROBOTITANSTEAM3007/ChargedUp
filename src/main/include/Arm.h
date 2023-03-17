#pragma once

// // ARM LAYOUT
// // Hand Motor
// // Claw Pnumatic
// // Shoulder Motor

// // Shoulder Encoder


#include <frc/Solenoid.h>
#include <frc/Encoder.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/AnalogPotentiometer.h>
#include <fstream>
#include <frc/Joystick.h>
#include <iostream>
#include <rev/CANSparkMax.h>
#include <frc/controller/PIDController.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include "Vector2D.h"
#include "Limelight.h"
#include "Drive.h"

// Height limit is 78 inches
// 52 Height rule limit

// Robot Component Constants
#define SHOULDER_HEIGHT 23.5 // inches
#define UPPER_ARM_LENGTH 15.6 // inches
#define RETRACTED_LOWER_ARM_LENGTH 23.7 //inches

// Robot Sensor Constants
#define MAX_ARM_EXTENSION 29 // inches
#define MIN_ARM_EXTENSION 0 // inches

#define POTENTIOMETER_OFFSET 0 // 0 - 1
#define ENCODER_OFFSET 0.15 // 0 - 1

#define MAX_ARM_ROTATION 360 // degrees
#define MIN_ARM_ROTATION 0 // degrees

#define ARM_EXTENSION_CONSTANT 44.24342102 // Was 0.0226022305, inches
#define ARM_ROTATION_CONSTANT 360.00 // degrees

#define SAFE_TARGET_EXTENSION 30.0 // inches 

// Zones where gravity will impact the extension
#define MIN_UNSAFE_EXTENSION_ZONE 45
#define MAX_UNSAFE_EXTENSION_ZONE 130

#define FREE_EXTENSION_POINT 140

#define MOVMENT_SUCCESS_ZONE 0.01

#define ROTATION_PID_ZONE 20 // Degrees
#define EXTENSION_PID_ZONE 5 // Inches


// NOTE!: 50in is the max length the arm can extend to stay inside the hight limit.
//        23.7in is the arm's length when retracted.
//        26.3in is the extension of the arm from 23.7in to make the lower arm's length equal to 50in.
//        35.3in is the maximum extension of the arm from 23.7in.
class Arm {
    private:
        std::fstream fs;

        // Stages
        bool finished_cone_placment {false};
        bool finished_forward_drive {false};

        // Sensor IDs
        short 
        extension_potentiometer_port { 4 },
        shoulder_encoder_channel { 10 };

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

        // Potentiometer
        double current_potentiometer_value, previous_potentiometer_value { 0 };

        float ext[10];

        double avrgExtension; 

        short iterations = 0;

        // Arm Calibration & Movment
        double rotation_offset, extension_offset, safe_extension_offset;

        double maxArmLength = 54.4;

        float calibPoint1 = 0, calibPoint2 = 0;

        float extensionSlope = 0;

        float extensionLength; //measured in inches sadly.

    public:
        PID rotation_PID{0.02, 0, 0};
        PID extension_PID{0.3, 0, 0};

        frc2::PIDController rotation_PID_controller{rotation_PID.proportion, rotation_PID.integral, rotation_PID.derivative};
        frc2::PIDController extension_PID_controller{extension_PID.proportion, extension_PID.integral, extension_PID.derivative};

        Vector2D speed;
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

        double rotation();
        
        double extension();

        double potentiometer_value();

        double distance();

        double height();

        void update_average_extension(double);

        void calibrate(frc::Joystick *stick); //Linear regression from arm at shortest and longest extension
 

        void set_direct_extend(float);

        void set_direct_rotation(float);

        void periodic();


        void move_to_high_cone();
        void move_to_mid_cone();

        void move_to_grab();


        void cone_auto_place_mid(Drive &);

        void cone_auto_place_high(Drive &);

};  
