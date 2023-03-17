#include "Gyro.h"

Gyro::Gyro()
{
  current_angle = 0;
}

void Gyro::auto_level(Drive &drive)
{
  current_angle = (double)Gyro::imu.GetAngle();

  drive.speed += Vector2D{-current_angle * 0.5, 0};
}