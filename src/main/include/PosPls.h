#pragma once
#include "Vector3D.h"
//#include "Vector2D.h"
#include "Gyro.h"
//#include "Odometry.h"
#include <rev/CANSparkMax.h>
#include <time.h>
#include <cmath>
#include <frc/ADXL345_I2C.h>

class PP {

    public:

        


        //Previous acceleration    
        //Vector3D lastAcceleration;

        //Position
        //Vector3D pos;

        //Holds encoder for wheel
        rev::SparkMaxRelativeEncoder* rel;

        double lastPosition;

        Vector2D pos{0, 0};


        //Real time
        double delta_time;

        //Acceleration
        //Vector3D Acceleration;

        //Jerk
        //Vector3D Jerk;

        double spinPP();

        double posDifference;


        //Periodic PP
        void PPP();

        //Constructor
        PP(rev::SparkMaxRelativeEncoder* rel);

    protected:

        frc::ADXL345_I2C accel{frc::I2C::Port::kMXP, frc::Accelerometer::Range::kRange_8G};


    private:

        static inline std::chrono::high_resolution_clock::time_point current_tick, previous_tick;

};