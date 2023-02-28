// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

using namespace std;

PP posPls;

void Robot::RobotInit() {

    frc::CameraServer::StartAutomaticCapture();

    auto_chooser.SetDefaultOption(auto_profile_default, auto_profile_default);
    auto_chooser.AddOption(auto_profile_testing, auto_profile_testing);
    auto_chooser.AddOption(auto_profile_whole_hog, auto_profile_whole_hog);

    frc::SmartDashboard::PutData("Auto Modes", &auto_chooser);

    drive_train.front_right_motor->RestoreFactoryDefaults();
    drive_train.back_right_motor->RestoreFactoryDefaults();
    drive_train.front_left_motor->RestoreFactoryDefaults();
    drive_train.back_left_motor->RestoreFactoryDefaults();

    // Motors are now following each other
    drive_train.back_left_motor->Follow(*drive_train.front_left_motor);
    drive_train.back_right_motor->Follow(*drive_train.front_right_motor);

    // encoder.

    // Gyro::imu.ConfigCalTime(frc::ADIS16470_IMU::CalibrationTime::_16s); // Default: 4s
    // Gyro::imu.Calibrate();

    // Gyro::imu.SetYawAxis(frc::ADIS16470_IMU::IMUAxis::kZ);

}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
    // cs::CvSink cvSink = frc::CameraServer::GetVideo();
    // cs::CvSource outputStream = frc::CameraServer::PutVideo("Front", 480, 480);
}

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

    if (selected_auto == auto_profile_testing) {
        
    } else {
        // Default Auto goes here
        
  }
}

void Robot::AutonomousPeriodic() {
    if (selected_auto == auto_profile_whole_hog) {
        drive_train.speed = Vector2D{0.8, 0};
    }
    else if (selected_auto == auto_profile_testing) {
        // Custom Auto goes here
    } else {
        // Default Auto goes here
        autonomus_place_cone();
    }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    // Gyro::update();

    // std::cout << "Acceleration: " << Gyro::acceleration.x << " " << Gyro::acceleration.y << " " << Gyro::acceleration.z << std::endl;
    // std::cout << "Position: " << Gyro::position.x << " " << Gyro::position.y << " " << Gyro::position.z << std::endl;

    // frc::SmartDashboard::PutNumber("AX", Gyro::acceleration.x);
    // frc::SmartDashboard::PutNumber("AY", Gyro::acceleration.y);
    // frc::SmartDashboard::PutNumber("AZ", Gyro::acceleration.z);

    // frc::SmartDashboard::PutNumber("VX", Gyro::velocity.x);
    // frc::SmartDashboard::PutNumber("VY", Gyro::velocity.y);
    // frc::SmartDashboard::PutNumber("VZ", Gyro::velocity.z);

    // frc::SmartDashboard::PutNumber("PX", Gyro::position.x);
    // frc::SmartDashboard::PutNumber("PY", Gyro::position.y);
    // frc::SmartDashboard::PutNumber("PZ", Gyro::position.z);

    // Default: Twist, X, Y
    // drive_train.DriveCartesian(-drive_joystick.get_y(0.15, 1.0), drive_joystick.get_x(0.15, 0.4), drive_joystick.get_twist(0.3, 0.3));
    // this commented drive is here to help me with merging
    // drive_train.DriveCartesian(drive_joystick.get_twist(0.3, 0.3), drive_joystick.get_x(0.15, 0.4), -drive_joystick.get_y(0.15, 1.0));

    drive_train.speed = 
    Vector2D
    {
        -to_sigmoidal(drive_joystick.get_y(0.2, 1.0), 5),
        to_sigmoidal(drive_joystick.get_twist(0.3, 0.5), 5)
    };
    
    // cout << to_sigmoidal(drive_joystick.get_twist(0.15, 1.0), 5) << endl;

    // drive_train.orientation = Gyro::imu.GetAngle();


    // Activate Limelight Auto Align
    if (button_1.is_active())
    { Limelight::retroreflective_auto_align(drive_train); }

    // Toggle Limelight LED
    if (button_2.is_active())
    {  
        std::cout << "Toggle LED" << std::endl;

        Limelight::toggle_led();
    }

    // Toggle Camera Mode
    if (button_3.is_active())
    {
        cout << "Toggle Camera Mode" << endl;

        Limelight::toggle_camera();
    }


    // Manual Arm Control

    // Arm Extension
    if (upper_arm_button.is_active())
    {
        double joystick_value = arm_joystick.get_y(0.15, 1);

        arm.extendSet(joystick_value);
        
    } 
    else
    {
        arm.extendSet(0);
    }

    // Arm Rotation
    if (lower_arm_button.is_active())
    {
        double joystick_value = arm_joystick.get_y(0.15, 1);

        arm.rotSet(joystick_value);
        
    }
    else
    {
        arm.rotSet(0);
    }

    // Toggle Hand Grip
    if (auto_arm_button.is_active())
    {
        hand_solenoid.Toggle();
    }

    // Toggle Pole
    if (pole_arm_button.is_active())
    {
        pole_solenoid.Toggle();
    }

    arm.periodic();

    frc::SmartDashboard::PutNumber("Encoder", arm.rotation());
    frc::SmartDashboard::PutNumber("Extension Switch 1", extension_switch_1.is_active());
    frc::SmartDashboard::PutNumber("Extension Switch 2", extension_switch_2.is_active());
    frc::SmartDashboard::PutNumber("Poten Value", arm.extension());

    
    posPls.PPP();

    // std::cout << (double)imu.GetAngle() << std::endl;

    drive_train.periodic();
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
