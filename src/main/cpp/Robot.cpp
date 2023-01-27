// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

void Robot::RobotInit() {
    auto_chooser.SetDefaultOption(auto_profile_default, auto_profile_default);
    auto_chooser.AddOption(auto_profile_testing, auto_profile_testing);

    frc::SmartDashboard::PutData("Auto Modes", &auto_chooser);

    front_right_motor.RestoreFactoryDefaults();
    back_right_motor.RestoreFactoryDefaults();
    front_left_motor.RestoreFactoryDefaults();
    back_left_motor.RestoreFactoryDefaults();

    front_right_motor.SetInverted(true);
    back_right_motor.SetInverted(true);

    // Gyro::imu.Calibrate();
    Gyro::imu.SetYawAxis(frc::ADIS16470_IMU::IMUAxis::kZ);
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
    selected_auto = auto_chooser.GetSelected();
    selected_auto = frc::SmartDashboard::GetString("Auto Selector", auto_profile_default); // Retrieves data from networktables & returns autotype, Default: kAutoNameDefault

    // fmt::print("Auto selected: {}\n", selected_auto);

    if (selected_auto == auto_profile_testing) {
        
    } else {
        // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
    Gyro::update();

    std::cout << "Acceleration: " << Gyro::acceleration.x << " " << Gyro::acceleration.y << " " << Gyro::acceleration.z << std::endl;
    std::cout << "Position: " << Gyro::position.x << " " << Gyro::position.y << " " << Gyro::position.z << std::endl;

    frc::SmartDashboard::PutNumber("AX", (double)Gyro::imu.GetAccelX());
    frc::SmartDashboard::PutNumber("AY", (double)Gyro::imu.GetAccelY());
    frc::SmartDashboard::PutNumber("AZ", (double)Gyro::imu.GetAccelZ());

    if (selected_auto == auto_profile_testing) {
        // Custom Auto goes here
    } else {
        // Default Auto goes here
    }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    // Default: Twist, X, Y
    drive_train.DriveCartesian(-drive_joystick.get_y(0.15, 0.5), drive_joystick.get_x(0.15, 0.5), drive_joystick.get_twist(0.2, 0.25));

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

    // std::cout << (double)imu.GetAngle() << std::endl;
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
