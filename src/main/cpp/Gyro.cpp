#include "Gyro.h"

Gyro::Gyro()
{
  current_angle = 0;
}

void Gyro::auto_level(Drive &drive)
{
  change_constant = frc::SmartDashboard::GetNumber("Change Constant", 0);
  
  current_angle = (double)Gyro::imu.GetAngle();

  linear_filter = change_constant * linear_filter + (1 - change_constant) * current_angle;

  delta_angle = linear_filter - previous_angle;

  if (fabs(current_angle) > 10 && abs(delta_angle) < 0.25)
  {
    drive.speed = Vector2D{std::clamp(-linear_filter, -0.40, 0.40), drive.speed.y};
  }

  previous_angle = current_angle;
}

void Gyro::reset()
{
  Gyro::imu.Reset();
}