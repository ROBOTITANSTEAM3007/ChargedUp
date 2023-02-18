#include "Gyro.h"

void Gyro::update()
{
  current_tick = std::chrono::high_resolution_clock::now();

  if (initiallized)
  {
      // 1 Second = 1,000,000 Microseconds
      // 1 Second = 1,000 Milliseconds
      double delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_tick - previous_tick).count();

      // std::cout << delta_time << std::endl;

    /*   
      filtered_acceleration_x = acceleration_filter_x.Calculate((double)Gyro::imu.GetAccelX()),
      filtered_acceleration_y = acceleration_filter_y.Calculate((double)Gyro::imu.GetAccelY()),
      filtered_acceleration_z = acceleration_filter_z.Calculate((double)Gyro::imu.GetAccelZ());

      // acceleration.set(Vector3D{filtered_acceleration_x, filtered_acceleration_y, filtered_acceleration_z}.add(normalize).deadzone(deadzone_value));
      acceleration.set(Vector3D::Vector3D{(double)Gyro::imu.GetAccelX(), (double)Gyro::imu.GetAccelY(), (double)Gyro::imu.GetAccelZ()}.add(normalize).deadzone(deadzone_value_acceleration));
      velocity.set(velocity.add(acceleration.mult(METER_PER_SEC_PER_G).mult(delta_time/MILLISECOND_PER_SECOND)).deadzone(deadzone_value_velocity));
      // Vector3D p{velocity.mult(delta_time/MICROSECOND_PER_SECOND)};
      position.set(position.add(velocity)); */
  }

  initiallized = true;

  previous_tick = std::chrono::high_resolution_clock::now();
}