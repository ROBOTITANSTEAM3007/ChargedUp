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
#include <frc/DutyCycleEncoder.h>


#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/AnalogInput.h>
#include <frc/TimedRobot.h>

#include <iostream>

#include "PosPls.h"

#include "Gyro.h"
#include "Limelight.h"
#include "Joystick.h"
#include "Vector3D.h"
#include "Button.h"
#include "Drive.h"
#include "Switch.h"
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
        short front_right_motor_ID { 2 };
        short back_right_motor_ID { 4 };

        // Left Side
        short front_left_motor_ID { 1 };
        short back_left_motor_ID { 3 };


        // Compressor
        short compressor_ID {0};

        frc::Compressor compressor{compressor_ID, frc::PneumaticsModuleType::CTREPCM};

        // DRIVE
        Drive drive_train{front_left_motor_ID, back_left_motor_ID, front_right_motor_ID, back_right_motor_ID};    

        // ARM
        // Arm robot_arm;

        short
        upper_arm_motor_ID { 5 },
        lower_arm_motor_ID { 6 },

        hand_solenoid_channel { 0 },
        pole_solenoid_channel { 4 },

        extension_switch_1_port { 2 },
        extension_switch_2_port { 3 },
        shoulder_encoder_port { 4 },
        
        extension_potentiometer_port { 0 };

        rev::CANSparkMax
        upper_arm_motor{upper_arm_motor_ID, rev::CANSparkMax::MotorType::kBrushless},
        lower_arm_motor{lower_arm_motor_ID, rev::CANSparkMax::MotorType::kBrushed};

        frc::Solenoid hand_solenoid{frc::PneumaticsModuleType::CTREPCM, hand_solenoid_channel};
        frc::Solenoid pole_solenoid{frc::PneumaticsModuleType::CTREPCM, pole_solenoid_channel};

        frc::DutyCycleEncoder encoder{shoulder_encoder_port};

        frc::AnalogInput extension_potentiometer{extension_potentiometer_port}; //0V to 5V

        // Switches
        Switch grab_position_switch{0, ALL};// DIO 0 & 1 are rotaion arm limit switches
        // 0 is the grab postion

        Switch extension_switch_1{extension_switch_1_port, ALL};// DIO 2 & 3 are extension arm limit switches
        Switch extension_switch_2{extension_switch_2_port, ALL};

        // STICKS
        // Drive Stick
        Joystick drive_joystick{0};
        Joystick arm_joystick{1};

        // Button 

        // ALL = Always detecting input
        // PRESS = Only once on press down            
        // RELEASE = Only once on release   

        Button button_1{1, drive_joystick.object, ALL};
        Button button_2{2, drive_joystick.object, PRESS};
        Button button_6{6, drive_joystick.object, PRESS};
        Button button_3{3, drive_joystick.object, PRESS};

        Button auto_arm_button{1, arm_joystick.object, PRESS};
        Button pole_arm_button{2, arm_joystick.object, PRESS};

        Button upper_arm_button{3, arm_joystick.object, ALL};
        Button lower_arm_button{4, arm_joystick.object, ALL};

    private:
        frc::SendableChooser<std::string> auto_chooser;
        const std::string auto_profile_default = "Default";
        const std::string auto_profile_testing = "Testing";
        std::string selected_auto;
};
