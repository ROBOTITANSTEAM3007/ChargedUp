#pragma once

// ARM LAYOUT
// Hand Motor
// Claw Pnumatic
// Shoulder Motor

// Shoulder Encoder
// 

#include <frc/Solenoid.h>
#include <rev/CANSparkMax.h>

class Arm {
    public:
        Arm() {
                
        }
    private:
        //motors
        short
        shoulder_motor_ID { 5 },
        wrist_motor_ID { 6 },

        //pneumatics
        hand_solenoid_channel { 0 },

        //encoders
        shoulder_encoder_ID { 0 };
        
        //declarations
        rev::CANSparkMax mtr_shoulder{shoulder_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
        rev::CANSparkMax mtr_hand{wrist_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
        frc::Solenoid claw_solenoid{frc::PneumaticsModuleType::CTREPCM, hand_solenoid_channel};


};