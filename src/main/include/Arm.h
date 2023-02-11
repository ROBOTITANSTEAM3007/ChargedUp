// #pragma once

// // ARM LAYOUT
// // Hand Motor
// // Claw Pnumatic
// // Shoulder Motor

// // Shoulder Encoder
// // 

// #include <frc/Solenoid.h>
// #include <rev/CANSparkMax.h>

// #include "Robot.h"
// class Arm {
//     public:
//         static inline void update_lower_arm(Joystick arm) {
//             lower_arm_motor.Set(arm.get_y(0, 0.2));
//         }
//         static inline void update_upper_arm(Joystick arm) {
//             upper_arm_motor.Set(arm.get_y(0, 0.2));
//         }
//         static inline void toggle_hand() {
//             hand_solenoid.Toggle();
//         }
//         static inline double get_encoder() {
//             // return encoder.GetPosition();
//         }
//         static inline void move_grab() {
//             PID pid{1.0, 0.0, 0.0};
//             upper_arm_motor.Set(0.0);
//         }
//         static inline void move_hold() {
//             PID pid{1.0, 0.0, 0.0};
//             upper_arm_motor.Set(0.0);
//         }
//         static inline void move_place() {
//             PID pid{1.0, 0.0, 0.0};
//             upper_arm_motor.Set(0.0);
//         }
//     private:
//         //motors
//         static inline short
//         shoulder_motor_ID { 5 },
//         wrist_motor_ID { 6 },

//         //pneumatics
//         hand_solenoid_channel { 0 },

//         //encoders
//         shoulder_encoder_ID { 0 };
        
//         //declarations
//         static inline rev::CANSparkMax upper_arm_motor{shoulder_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
//         static inline rev::CANSparkMax lower_arm_motor{wrist_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
//         static inline frc::Solenoid hand_solenoid{frc::PneumaticsModuleType::CTREPCM, hand_solenoid_channel};
//         // static inline rev::SparkMaxAlternateEncoder encoder{upper_arm_motor.GetAlternateEncoder(rev::CANEncoder::AlternateEncoderType::kQuadrature, 8192)};
// };
