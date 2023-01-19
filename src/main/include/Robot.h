// Copyright (c) FIRST and other WPILib contributors.

// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <fmt/core.h>

#include <rev/CANSparkMax.h>

#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/TimedRobot.h>

#include <Joystick.h>
#include <Button.h>
#include <Arm.h>

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
        front_right_motor_ID { 1 },
        back_right_motor_ID { 3 },

        // Left Side
        front_left_motor_ID { 2 },
        back_left_motor_ID { 4 };

        // Initalize
        rev::CANSparkMax front_right_motor{front_right_motor_ID , rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax back_right_motor{back_right_motor_ID , rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax front_left_motor{front_left_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax back_left_motor{back_left_motor_ID, rev::CANSparkMax::MotorType::kBrushless};

        // DRIVE
        frc::MecanumDrive drive_train{front_left_motor, back_left_motor, front_right_motor, back_right_motor};

        // STICKS
        // Drive Stick
        Joystick drive_joystick{0, 0.1, 1};

        // 0 = Always detecting input
        // 1 = Only once on press down            |
        // 2 = Only once on release               v
        Button button_1{1, drive_joystick.object, 0};

    private:
        frc::SendableChooser<std::string> m_chooser;
        const std::string kAutoNameDefault = "Default";
        const std::string kAutoNameCustom = "My Auto";
        std::string m_autoSelected;
};
