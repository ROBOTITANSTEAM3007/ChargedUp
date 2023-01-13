// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <fmt/core.h>

#include <rev/CANSparkMax.h>

#include <frc/TimedRobot.h>

#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/drive/DifferentialDrive.h>

#include <Joystick.h>

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

        //Motors
        short right_drive_motor_ID = 1;
        short left_drive_motor_ID = 2;

        rev::CANSparkMax right_drive_motor{right_drive_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax left_drive_motor{left_drive_motor_ID, rev::CANSparkMax::MotorType::kBrushless};

        frc::DifferentialDrive robot_drive{left_drive_motor, right_drive_motor};

        Joystick drive_joystick{0, 0.1, 1};

    private:
        frc::SendableChooser<std::string> m_chooser;
        const std::string kAutoNameDefault = "Default";
        const std::string kAutoNameCustom = "My Auto";
        std::string m_autoSelected;
};
