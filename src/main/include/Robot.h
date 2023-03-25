// Copyright (c) FIRST and other WPILib contributors.

// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include <chrono>

#include <fmt/core.h>
#include <cameraserver/CameraServer.h>

#include <rev/CANSparkMax.h>
#include <cscore_oo.h>

#include <frc/PneumaticsControlModule.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>
#include "Debug.h"
#include <frc/DutyCycleEncoder.h>


#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/AnalogInput.h>
#include <frc/AnalogPotentiometer.h>
#include <frc/TimedRobot.h>

#include <frc/PowerDistribution.h>
#include <hal/PowerDistribution.h>


#include <iostream>

#include "PosPls.h"

#include "Gyro.h"
#include "Limelight.h"
#include "Joystick.h"
#include "Vector3D.h"
#include "Button.h"
#include "Drive.h"
#include "Switch.h"
#include "Arm.h"


class Robot : public frc::TimedRobot {
    public:
        void RobotInit() override;
        void RobotPeriodic() override;
        void AutonomousInit() override;
        void AutonomousPeriodic() override;
        void TeleopInit() override;
        void TeleopPeriodic() override;
        void DisabledInit() override;
        void DisabledPeriodic() override;
        void TestInit() override;
        void TestPeriodic() override;
        void SimulationInit() override;
        void SimulationPeriodic() override;

        frc::PowerDistribution power_distribution_board{0, frc::PowerDistribution::ModuleType::kCTRE};

        // MOTORS

        // Right Side
        short front_right_motor_ID { 2 };
        short back_right_motor_ID { 4 };

        // Left Side
        short front_left_motor_ID { 1 };
        short back_left_motor_ID { 3 };


        // Compressor
        short compressor_ID {0};
        frc::Compressor compressor{compressor_ID, frc::PneumaticsModuleType::CTREPCM};

        // cs::UsbCamera front_camera;
        // cs::UsbCamera arm_camera;

        cs::VideoSource front_camera;
        cs::VideoSource arm_camera;

        dbg debug;

        cs::VideoSink server;

        // DRIVE
        Drive drive_train{front_left_motor_ID, back_left_motor_ID, front_right_motor_ID, back_right_motor_ID};    

        rev::SparkMaxRelativeEncoder rel = drive_train.back_right_motor->GetEncoder();
        //drive_train.back_left_motor

        PP position{&rel};


        // ARM
        Arm arm;

        // GYRO
        Gyro gyro;
        
        // short extSens = 1;
        // short rotSens = 1;

        double to_sigmoidal(double input, double scale) // Anything larger than a scale of 10 is optimal
        {
            if (input == 0)
            { return 0; }
        

            // return 2 * sin(M_PI / 2 * input) * (1 / (1 + exp(-scale / 2 * input)) - 0.5) * (fabs(input) / input); 
            return 2 / (1 + exp(-scale * (fabs(input / 2) - 0.5))) * (fabs(input) / input);
        }
        //
        double to_exponential(double input) {
            if (input == 0) {
                return 0;
            }
            return exp(5.42*(fabs(input)-1))*(fabs(input)/input);
        }

        void autonomus_place_cone()
        {
            drive_train.speed = Vector2D{0.2, 0}.minimum(Limelight::motion_limits);
        }

// End Of ARM

        // STICKS
        // Drive Stick
        Joystick drive_joystick{0};
        Joystick arm_joystick{1};


        //Arm

        // Button 

        // ALL = Always detecting input
        // PRESS = Only once on press down            
        // RELEASE = Only once on release   

        Button button_1{1, drive_joystick.object, ALL}; // Limelight Autoalign
        Button button_2{2, drive_joystick.object, PRESS}; // Toggle LED
        Button button_6{6, drive_joystick.object, PRESS}; // Reset IMU
        Button button_3{3, drive_joystick.object, PRESS}; // Toggle Camera Mode

        Button auto_level_button{5, drive_joystick.object, ALL}; // Autolevel

        Button auto_arm_button{1, arm_joystick.object, PRESS};
        Button pole_arm_button{2, arm_joystick.object, PRESS};

        Button upper_arm_button{3, arm_joystick.object, ALL};
        Button lower_arm_button{4, arm_joystick.object, ALL};

        Button move_to_high_button{6, arm_joystick.object, PRESS};
        Button move_to_mid_button{12, arm_joystick.object, PRESS};
        Button setup_grab_button{5, arm_joystick.object, PRESS};

        double time_remaining {0};

    private:
        frc::SendableChooser<std::string> auto_chooser;
        const std::string auto_profile_default = "Default";
        const std::string auto_profile_whole_hog = "No Chill";
        const std::string cone_high = "High As A Cone";
        const std::string cone_mid = "Pretty Mid Cone Der Bud";
        const std::string dock = "Dock";
        const std::string runAway = "Run Away!";
        std::string selected_auto;
};
