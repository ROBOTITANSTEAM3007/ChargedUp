// Copyright (c) FIRST and other WPILib contributors.

// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include <chrono>

#include <fmt/core.h>

#include <rev/CANSparkMax.h>

#include <frc/PneumaticsControlModule.h>
#include <frc/Compressor.h>
#include <frc/Solenoid.h>

#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/TimedRobot.h>

#include <frc/ADXL345_I2C.h>

#include <iostream>

#include "Gyro.h"
#include "Limelight.h"
#include "Joystick.h"
#include "Button.h"
#include "Drive.h"
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

        // MOTORS

        // Right Side
        short 
        front_right_motor_ID { 2 }, //2
        back_right_motor_ID { 4 }, //4

        // Left Side
        front_left_motor_ID { 1 }, //1
        back_left_motor_ID { 3 }; //3

        // DRIVE
        Drive drive_train{front_left_motor_ID, back_left_motor_ID, front_right_motor_ID, back_right_motor_ID};    

        rev::SparkMaxAlternateEncoder encoder{drive_train.front_left_motor->GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8192)};

        // rev::SparkMaxAlternateEncoder encoder = drive_train.front_left_motor->GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8192);

        // STICKS
        // Drive Stick
        Joystick drive_joystick{0};

        // ALL = Always detecting input
        // PRESS = Only once on press down            
        // RELEASE = Only once on release               
        Button button_1{1, drive_joystick.object, ALL};

        Button button_2{2, drive_joystick.object, PRESS};

        Button button_6{6, drive_joystick.object, PRESS};
        Button button_3{3, drive_joystick.object, PRESS};

        // Button 

    private:
        frc::SendableChooser<std::string> auto_chooser;
        const std::string auto_profile_default = "Default";
        const std::string auto_profile_testing = "Testing";
        std::string selected_auto;
};
