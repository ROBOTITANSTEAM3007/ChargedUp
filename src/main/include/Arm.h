#pragma once

#include <rev/CANSparkMax.h>

class Arm {
    public:

        Arm() {

        }
    private:
        //motors
        short mtr_shoulder_ID = 5;
        short mtr_hand_ID = 6;
        //pneumatics
        short pnm_claw_ID = 0;
        //encoders
        short enc_shoulder_ID = 0;
};