// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <iostream>

using namespace std;

void Robot::RobotInit() {

    server = frc::CameraServer::GetServer();
    
    front_camera = frc::CameraServer::StartAutomaticCapture("Front Camera", 1);
    arm_camera = frc::CameraServer::StartAutomaticCapture("Arm Camera", 0);

    arm_camera.SetFPS(10);
    front_camera.SetFPS(20);
    debug.out("Started Camera Server");


    front_camera.SetConnectionStrategy(cs::VideoSource::ConnectionStrategy::kConnectionKeepOpen);
    arm_camera.SetConnectionStrategy(cs::VideoSource::ConnectionStrategy::kConnectionKeepOpen);
    debug.out("Set Connection Strategy");

    auto_chooser.SetDefaultOption(auto_profile_default, auto_profile_default);
    auto_chooser.AddOption(auto_profile_whole_hog, auto_profile_whole_hog);
    auto_chooser.AddOption(cone_high, cone_high);
    auto_chooser.AddOption(cone_mid, cone_mid);
    auto_chooser.AddOption(runAway, runAway);
    auto_chooser.AddOption(dock, dock);

    frc::SmartDashboard::PutData("Auto Modes", &auto_chooser);

    frc::SmartDashboard::PutNumber("Target Extension", arm.target_extension);
    frc::SmartDashboard::PutNumber("Target Rotation", arm.target_angle);

    frc::SmartDashboard::PutNumber("Extension P", arm.extension_PID.proportion);
    frc::SmartDashboard::PutNumber("Extension I", arm.extension_PID.integral);
    frc::SmartDashboard::PutNumber("Extension D", arm.extension_PID.derivative);

    frc::SmartDashboard::PutNumber("Rotation P", arm.rotation_PID.proportion);
    frc::SmartDashboard::PutNumber("Rotation I", arm.rotation_PID.integral);
    frc::SmartDashboard::PutNumber("Rotation D", arm.rotation_PID.derivative);

    frc::SmartDashboard::PutNumber("Change Constant", gyro.change_constant);

    frc::SmartDashboard::PutNumber("Auto Drive Time", 0);

    drive_train.front_right_motor->RestoreFactoryDefaults();
    drive_train.back_right_motor->RestoreFactoryDefaults();
    drive_train.front_left_motor->RestoreFactoryDefaults();
    drive_train.back_left_motor->RestoreFactoryDefaults();
    debug.out("Reset Motor Defaults");

    drive_train.front_right_motor->SetInverted(true);

    // Motors are now following each other
    drive_train.back_left_motor->Follow(*drive_train.front_left_motor);
    drive_train.back_right_motor->Follow(*drive_train.front_right_motor);


    power_distribution_board.ClearStickyFaults();
    // IMU
    gyro.imu.ConfigCalTime(frc::ADIS16470_IMU::CalibrationTime::_16s); // Default: 4s
    gyro.imu.Calibrate();

    gyro.imu.SetYawAxis(frc::ADIS16470_IMU::IMUAxis::kX);

    debug.out("Finished RobotInit");
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
    frc::SmartDashboard::PutNumber("IMU Angle", (double)gyro.linear_filter);
    frc::SmartDashboard::PutNumber("IMU Delta Angle", (double)gyro.delta_angle);

    frc::SmartDashboard::PutNumber("Y Position" , position.spinPP());
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
    //selected_auto = frc::SmartDashboard::GetString("Auto Selector", auto_profile_default); // Retrieves data from networktables & returns autotype, Default: kAutoNameDefault

    if (selected_auto == cone_high) {
        arm.cone_auto_place_high(drive_train);
    } else if (selected_auto == dock) {
        position.pos.y = 0;
        gyro.reset();
    }
    // } else if (selected_auto == cone_mid) {
    //     arm.cone_auto_place_mid();

    // } else if (selected_auto == cube_high) {
    //     arm.cube_auto_place_high();

    // } else if (selected_auto == cube_high) {
    //     arm.cube_auto_place_mid();

    else {
        // Default Auto goes here
    }
    debug.out("Selected Auto = " + selected_auto);
}

bool finiForwardy = false;

void Robot::AutonomousPeriodic() {
    if (selected_auto == auto_profile_whole_hog) {
        drive_train.speed = Vector2D{0.99, 0};
    } else if (selected_auto == cone_high) {
        arm.cone_auto_place_high(drive_train);

    } else if (selected_auto == cone_mid) {
        arm.cone_auto_place_mid(drive_train);

    } 
    else if (selected_auto == dock) 
    {
        if (arm.cone_auto_place_high(drive_train))
        {
            if (position.spinPP() < 73 && finiForwardy == false)
            {
                drive_train.speed = Vector2D(0.6, 0);

            }  else {
                finiForwardy = true;
            }

            if (finiForwardy == true)
            {

                gyro.auto_level(drive_train);
            }
        }  
    } else if (selected_auto == runAway) {
        if (arm.cone_auto_place_high(drive_train))
        {
            if (position.spinPP() < 192)
            {
                drive_train.speed = Vector2D(0.6, 0);
            } else {
                drive_train.speed = Vector2D(0,0);
            }

        }  
    }
    else {
        // Default Auto goes here
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
        -to_sigmoidal(drive_joystick.get_y(0.2, 1.0), 10),
        -to_sigmoidal(drive_joystick.get_twist(0.3, 0.8), 10)
    };
    
    // cout << to_sigmoidal(drive_joystick.get_twist(0, 1.0), 10) << endl;

    // Activate Limelight Auto Align
    if (button_1.is_active())
    { Limelight::retroreflective_auto_align(drive_train); }

    // Tries to Auto Level on the charging station
    if (auto_level_button.is_active()) // Button 5
    {
        gyro.auto_level(drive_train);
        // gyro.imu.get
    }

    // Toggle Limelight LED
    if (button_2.is_active())
    {  
        debug.out("Toggle LED");

        Limelight::toggle_led();
    }

    
    if (button_6.is_active())
    {
        gyro.reset();
    }

    // Extension 6in for safe start distance

    // Toggle Camera Mode
    if (button_3.is_active())
    {
        debug.out("Toggle Camera Mode");

        Limelight::toggle_camera();
    }

    // frc::PowerDistribution::Faults current_fault = power_distribution_board.GetFaults(); // Channel 3

    // frc::SmartDashboard::PutNumber("Power", arm.upper_arm_motor.GetOutputCurrent());

    if (button_6.is_active())
    {
        gyro.reset();
    }

    // Manual Arm Control

    // if (arm.manual)
    // {
        // Arm Extension
        if (lower_arm_button.is_active())
        { 
            arm.manual = true;

            arm.set_direct_extend(arm_joystick.get_y(0.15, 1));
        } 
        else if (arm.manual)
        { arm.set_direct_extend(0); }

        // Arm Rotation
        if (upper_arm_button.is_active())
        {
            arm.manual = true;

            arm.set_direct_rotation(arm_joystick.get_y(0.15, 1));
        }
        else if (arm.manual)
        { arm.set_direct_rotation(0); }

        // Toggle Hand Grip
        if (auto_arm_button.is_active())
        { arm.hand_solenoid.Toggle();
            debug.out("Hand Grip Toggled By Button");
        }

        // Toggle Pole
        if (pole_arm_button.is_active())
        { arm.pole_solenoid.Toggle(); }
    // }

    // arm.manual = false;

    // Moves arm to position for high cone
    if (move_to_high_button.is_active())
    { 
        debug.out("Setup High Cone");

        arm.move_to_high_cone(); 
    }

    // Moves arm to position for mid cone
    if (move_to_mid_button.is_active())
    { 
        cout << "Setup Mid Cone" << endl;

        arm.move_to_mid_cone(); 
    }

    // Moves arm and extension to position for picking up
    if (setup_grab_button.is_active())
    { 
        debug.out("Setup Grab");

        arm.move_to_grab();
    }

    // arm.target_extension = frc::SmartDashboard::GetNumber("Target Extension", 0.2);
    // arm.target_angle = frc::SmartDashboard::GetNumber("Target Rotation", POTENTIOMETER_OFFSET);

    time_remaining = frc::SmartDashboard::GetNumber("Auto Drive Time", 0);
    if (time_remaining > 0)
    {
        drive_train.speed += Vector2D{0.5, 0};

        frc::SmartDashboard::PutNumber("Auto Drive Time", time_remaining - 20);
    }

    arm.periodic();
    drive_train.periodic();

    frc::SmartDashboard::PutNumber("Target Extension", arm.target_extension);
    frc::SmartDashboard::PutNumber("Target Rotation", arm.target_angle);

    frc::SmartDashboard::PutNumber("Encoder", arm.rotation());
    frc::SmartDashboard::PutNumber("Poten Value", arm.extension());
    frc::SmartDashboard::PutNumber("IMU Angle", (double)gyro.imu.GetAngle());

    

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
