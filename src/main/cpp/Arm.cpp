#include "Arm.h"

void Arm::calibrate(frc::Joystick *stick) {
    if(stick->GetRawButtonPressed(4)) {
        this->calibPoint1 = analogExt.GetAverageValue();
    }
    if(stick->GetRawButtonPressed(5)) {
        this->calibPoint2 = analogExt.GetAverageValue();
    }

    if(this->calibPoint1 != 0 && this->calibPoint2 != 0 ){
        this->extensionSlope = (fabs(this->calibPoint2 - this->calibPoint1)/maxArmLength);
        this->calibPoint1 = 0;
        this->calibPoint2 = 0;
        if(!this->fs.is_open()) {
            this->fs.write((char*)(&extensionSlope), sizeof(extensionSlope));
            this->fs.close();
        } else {
            this->fs.open("calib.bin", std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
        }
        
    }

}
Arm::Arm() {
    this->extensionLength = 0;
    this->analogExt.SetAverageBits(8);
    this->fs.open("calib.bin", std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
    if(!this->fs.is_open()) {
        this->fs.read((char*)(&extensionSlope), sizeof(extensionSlope));
    }
};

void Arm::periodic() {
    angle_offset = fmax(fmin(target_angle, MAX_ARM_ROTATION), MIN_ARM_ROTATION) - rotation();

    

    if (fabs(angle_offset) < 0.01)
    {
        upper_arm_motor.Set(fmin(angle_offset, 1));
        std::cout << "Correct Rotation" << rotation() << std::endl;
    }
    extension_offset = (fmax(fmin(target_extension, MAX_ARM_EXTENSION), MIN_ARM_EXTENSION) - extension());


    if (fabs(extension_offset) < 0.01)
    {
        lower_right_arm_motor.Set(fmin(extension_offset, 1));

        std::cout << "Correct Extension" << extension() << std::endl;

    }
};
