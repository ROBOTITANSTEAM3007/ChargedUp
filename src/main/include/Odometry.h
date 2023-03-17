#pragma once

#include "Gyro.h"
#include "Robot.h"

#include <frc/kinematics/MecanumDriveOdometry.h>

// Locations of the wheels relative to the robot center.
frc::Translation2d
front_left_location{},
front_right_location{},
back_left_location{},
back_right_location{};

// Creating my kinematics object using the wheel locations.
frc::MecanumDriveKinematics mecanum_kinematics {front_left_location, front_right_location, back_left_location, back_right_location};

// frc::Rotation2d robot_orientation{Gyro::imu.GetAngle()};

// frc::MecanumDriveWheelPositions
// {
//     units::meter_t{},
//     units::meter_t{},
//     units::meter_t{},
//     units::meter_t{}
// };

// // Creating my odometry object from the kinematics object. Here,
// // our starting pose is 5 meters along the long end of the field and in the
// // center of the field along the short end, facing forward.
// frc::MecanumDriveOdometry mecanum_odometry{mecanum_kinematics, robot_orientation, }