// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

using namespace std;

PP posPls;

void Robot::RobotInit() {

    front_camera = frc::CameraServer::StartAutomaticCapture(1);
    arm_camera = frc::CameraServer::StartAutomaticCapture(0);

    camera_selection = nt::NetworkTableInstance::GetDefault().GetTable("")->GetEntry("CameraSelection");

    auto_chooser.SetDefaultOption(auto_profile_default, auto_profile_default);
    auto_chooser.AddOption(auto_profile_testing, auto_profile_testing);
    auto_chooser.AddOption(auto_profile_whole_hog, auto_profile_whole_hog);

    frc::SmartDashboard::PutData("Auto Modes", &auto_chooser);

    frc::SmartDashboard::PutNumber("Target Extension", 0.2);
    frc::SmartDashboard::PutNumber("Target Rotation", 0.15);

    drive_train.front_right_motor->RestoreFactoryDefaults();
    drive_train.back_right_motor->RestoreFactoryDefaults();
    drive_train.front_left_motor->RestoreFactoryDefaults();
    drive_train.back_left_motor->RestoreFactoryDefaults();

    drive_train.front_right_motor->SetInverted(true);

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

    arm.periodic();
    drive_train.periodic();
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
    drive_train.speed = 
    /*Vector2D
    {
        -to_sigmoidal(drive_joystick.get_y(0.2, 1.0), 5),
        to_sigmoidal(drive_joystick.get_twist(0.3, 0.5), 5)
    };*/
    Vector2D
    {
        -to_exponential(drive_joystick.get_y(0.2, 1.0)),
        -to_exponential(drive_joystick.get_twist(0.3, 0.75))
    };
    
    // cout << to_sigmoidal(drive_joystick.get_twist(0, 1.0), 10) << endl;

    // Activate Limelight Auto Align
    if (button_1.is_active())
    { Limelight::retroreflective_auto_align(drive_train); }

    // Toggle Limelight LED
    if (button_2.is_active())
    {  
        std::cout << "Toggle LED" << std::endl;

        Limelight::toggle_led();
    }

    // Switch Camera
    if (button_6.is_active())
    {
        std::cout << "Change Camera" << std::endl;

        if (camera_selection.GetString(arm_camera.GetName()) == arm_camera.GetName())
        {
            camera_selection.SetString(front_camera.GetName());
        }
        else
        {
            camera_selection.SetString(arm_camera.GetName());
        }
    }

    // Toggle Camera Mode
    if (button_3.is_active())
    {
        cout << "Toggle Camera Mode" << endl;

        Limelight::toggle_camera();
    }


    // Manual Arm Control

    if (arm.manual)
    {
        // Arm Extension
        if (lower_arm_button.is_active())
        {
            double joystick_value = arm_joystick.get_y(0.15, 1);

            arm.set_direct_extend(joystick_value);
            
        } 
        else
        {
            arm.set_direct_extend(0);
        }

        // Arm Rotation
        if (upper_arm_button.is_active())
        {
            double joystick_value = arm_joystick.get_y(0.15, 1);

            arm.set_direct_rotation(joystick_value);
            
        }
        else
        {
            arm.set_direct_rotation(0);
        }

        // Toggle Hand Grip
        if (auto_arm_button.is_active())
        {
            arm.hand_solenoid.Toggle();
        }

        // Toggle Pole
        if (pole_arm_button.is_active())
        {
            arm.pole_solenoid.Toggle();
        }
    }

    // arm.manual = false;

    arm.target_extension = frc::SmartDashboard::GetNumber("Target Extension", 0.2);
    arm.target_angle = frc::SmartDashboard::GetNumber("Target Rotation", 0.15);

    arm.periodic();
    drive_train.periodic();


    frc::SmartDashboard::PutNumber("Encoder", arm.rotation());
    frc::SmartDashboard::PutNumber("Poten Value", arm.extension());

    
    posPls.PPP();

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
