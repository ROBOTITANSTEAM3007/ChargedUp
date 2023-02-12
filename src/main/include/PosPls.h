#pragma once
#include "Robot.h"
#include "Vector3D.h"
#include <frc/ADXL345_I2C.h>

class PP {

    public:


        //Previous acceleration    
        Vector3D lastAcceleration;

        //Position
        Vector3D pos;

        //Real time
        double delta_time;

        //Acceleration (Actually jerk)
        Vector3D Acceleration;

        //Jerk
        Vector3D Jerk;


        //Periodic PP
        void PPP();

        //Constructor
        PP();

    protected:

        frc::ADXL345_I2C accel{frc::I2C::Port::kMXP, frc::Accelerometer::Range::kRange_8G};


    private:

        static inline std::chrono::high_resolution_clock::time_point current_tick, previous_tick;

};