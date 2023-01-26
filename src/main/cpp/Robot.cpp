// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

using namespace std;

void Robot::RobotInit() {
    m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
    m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);

    frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

    front_right_motor.RestoreFactoryDefaults();
    back_right_motor.RestoreFactoryDefaults();
    front_left_motor.RestoreFactoryDefaults();
    back_left_motor.RestoreFactoryDefaults();

    imu.Calibrate();
    imu.SetYawAxis(frc::ADIS16470_IMU::IMUAxis::kZ);
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
    m_autoSelected = m_chooser.GetSelected();
    m_autoSelected = frc::SmartDashboard::GetString("Auto Selector", kAutoNameDefault);

    fmt::print("Auto selected: {}\n", m_autoSelected);

    if (m_autoSelected == kAutoNameCustom) {
        // Custom Auto goes here
    } else {
        // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
    if (m_autoSelected == kAutoNameCustom) {
        // Custom Auto goes here
    } else {
        // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    // auto strafe_temp = drive_joystick.get_y(0.15, 0.5) * sin((double)imu.GetAngle()*(M_PI/180)) + drive_joystick.get_x(0.15, 0.5) * cos((double)imu.GetAngle()*(M_PI/180));
    // auto fwd = -drive_joystick.get_y(0.15, 0.5) * cos((double)imu.GetAngle()*(M_PI/180)) + strafe_temp * sin((double)imu.GetAngle()*(M_PI/180));
    // drive_train.DriveCartesian(drive_joystick.get_twist(0.3, 0.3), strafe_temp, fwd);
    drive_train.DriveCartesian(drive_joystick.get_twist(0.3, 0.3), drive_joystick.get_x(0.15, 0.4), -drive_joystick.get_y(0.15, 1.0));

    if (button_1.is_active())
    {  
        std::cout << "Button 1" << std::endl;

        if (Limelight::get_data("pipeline", 1) == 1)
        {
            Limelight::put_data("pipeline", 0);
        }
        else
        {
            Limelight::put_data("pipeline", 1);   
        }
    }


    if (button_2.is_active())
    {  
        std::cout << "Button 2" << std::endl;

        if (Limelight::get_data("ledMode", 1) == 1)
        {
            Limelight::put_data("ledMode", 3);
        }
        else
        {
            Limelight::put_data("ledMode", 1);
        }
    }

    if (button_6.is_active()) {
        
        cout << "Button 6 Gyro Reset" << endl;

        imu.Reset();
    }

    std::cout << (double)imu.GetAngle() << std::endl;
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
    return frc::StartRobot<Robot>();
}
#endif
