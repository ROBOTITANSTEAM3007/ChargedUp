#pragma once

#include <frc/drive/MecanumDrive.h>
#include <rev/CANSparkMax.h>

#include "Vector3D.h"

struct PID
{
    double
    proportion,
    integral,
    derivative;


    PID(double t_p, double t_i, double t_d)
    {
        proportion = t_p;
        integral = t_i;
        derivative = t_d;
    }
};

class Drive
{
public:

    // MOTORS
    rev::CANSparkMax *front_left_motor, *back_left_motor, *front_right_motor, *back_right_motor;

    // DRIVE
    frc::MecanumDrive *controller;

    // PROPERTIES
    Vector3D speed {Vector3D::zero()};
    frc::Rotation2d orientation {units::degree_t {0}};

    Drive(short front_left_motor_ID, short back_left_motor_ID, short front_right_motor_ID, short back_right_motor_ID)
    {
        front_left_motor = new rev::CANSparkMax{front_left_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
        back_left_motor = new rev::CANSparkMax{back_left_motor_ID, rev::CANSparkMax::MotorType::kBrushless};

        front_right_motor = new rev::CANSparkMax{front_right_motor_ID, rev::CANSparkMax::MotorType::kBrushless};
        back_right_motor = new rev::CANSparkMax{back_right_motor_ID, rev::CANSparkMax::MotorType::kBrushless};

        controller = new frc::MecanumDrive{*front_left_motor, *back_left_motor, *front_right_motor, *back_right_motor};
    }

    // UPDATES ROBOT DRIVE
    void update()
    { controller->DriveCartesian(fmax(fmin(speed.x, 1), -1), fmax(fmin(speed.y, 1), -1), fmax(fmin(speed.z, 1), -1), orientation); }
};
