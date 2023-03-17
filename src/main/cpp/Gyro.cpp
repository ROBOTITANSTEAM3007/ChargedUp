#include "Gyro.h"

Gyro::Gyro()
{
  current_angle = 0;
}

void Gyro::auto_level(Drive &drive)
{
  gyro_PID.proportion = frc::SmartDashboard::GetNumber("Leveling P", 0);
  gyro_PID.integral = frc::SmartDashboard::GetNumber("Leveling I", 0);
  gyro_PID.derivative = frc::SmartDashboard::GetNumber("Leveling D", 0);

  current_angle = (double)Gyro::imu.GetAngle();

  drive.speed += Vector2D{std::clamp(gyro_PID_controller.Calculate(current_angle, 0), -0.40, 0.40), 0};
}

void Gyro::reset()
{
  Gyro::imu.Reset();
}