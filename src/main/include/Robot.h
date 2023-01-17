// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/Joystick.h>
#include <frc/smartdashboard/SendableChooser.h>

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

        double joystick_deadzone = 0.1;
        double joystick_sensitivity = 1;

        //IDs for someone else to figure out
        //sticks
        short drive_joystick = 1;

        //sparkmax
        short right_drive_motor_ID = 1;
        short left_drive_motor_ID = 2;
        short right_lag_motor_ID = 3;
        short left_lag_motor_ID = 4;

        rev::CANSparkMax m_frontLeft{right_drive_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_frontRight{left_drive_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_backRight{right_lag_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_backLeft{left_lag_motor_ID, rev::CANSparkMax::MotorType::kBrushless};

        frc::DifferentialDrive m_robotDrive{m_frontLeft, m_frontRight};
        frc::MecanumDrive m_robotDriveMecanum{m_frontLeft, m_backLeft, m_frontRight, m_backRight};
        frc::Joystick m_driveStick{drive_joystick};

    private:
        frc::SendableChooser<std::string> m_chooser;
        const std::string kAutoNameDefault = "Default";
        const std::string kAutoNameCustom = "My Auto";
        std::string m_autoSelected;
};
