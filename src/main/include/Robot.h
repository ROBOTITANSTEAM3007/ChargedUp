// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>

#include <frc/TimedRobot.h>
#include <rev/CANSparkMax.h>
#include <frc/drive/DifferentialDrive.h>
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

        void onDriveRequest(double); 

        //IDs for someone else to figure out
        //sticks
        static unsigned const short otherJoystickID = 0;
        static unsigned const short driveJoystickID = 1;

        //sparkmax
        unsigned const short rightDriveMotorID = 1;
        unsigned const short leftDrivemotorID = 2;

        rev::CANSparkMax m_rightDriveMotor{rightDriveMotorID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax m_leftDriveMotor{leftDrivemotorID, rev::CANSparkMax::MotorType::kBrushless};

        frc::DifferentialDrive m_robotDrive{m_leftDriveMotor, m_rightDriveMotor};
        frc::Joystick m_driveStick{driveJoystickID};

    private:
        frc::SendableChooser<std::string> m_chooser;
        const std::string kAutoNameDefault = "Default";
        const std::string kAutoNameCustom = "My Auto";
        std::string m_autoSelected;
};
