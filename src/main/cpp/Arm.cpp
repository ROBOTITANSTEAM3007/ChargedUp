#include "Arm.h"

// Tries to auto calibrate arm motions
void Arm::calibrate(frc::Joystick *stick) {
    if(stick->GetRawButtonPressed(4)) {
        this->calibPoint1 = extension_potentiometer.Get();
    }
    if(stick->GetRawButtonPressed(5)) {
        this->calibPoint2 = extension_potentiometer.Get();
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

double Arm::get_potentiometer_value()
{
    double current_potentiometer_value = extension_potentiometer.Get();

    if (current_potentiometer_value < 0)
    
    { return previous_potentiometer_value; }
    
    else

    { previous_potentiometer_value = current_potentiometer_value; }

    return current_potentiometer_value;
}

double Arm::extension(){
    avrgExtension = 0;

    for(int i = 0; i < 9; i++) {
        avrgExtension = avrgExtension + ext[i];
    }

    avrgExtension = avrgExtension / 10;

    return((avrgExtension / ARM_EXTENSION_CONSTANT));
}

Arm::Arm() {
    this->target_extension = 0;
    this->target_angle = 0.2;
//     this->analogExt.SetAverageBits(8);
//     this->fs.open("calib.bin", std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
//     if(!this->fs.is_open()) {
//         this->fs.read((char*)(&extensionSlope), sizeof(extensionSlope));
//     }
};

void Arm::periodic() {
    // Get the average of the past 10 potentiometer reads
    ext[iterations] = get_potentiometer_value();
    
    if(iterations < 9) {
    
        iterations++;
    
    } else {
    
        iterations = 0;
    
    }

    // Run Manual
    if(!manual){
        
        if (target_angle < 0.2)
        {
            target_angle = 0.2;
        }

        if(target_extension < 0)
        {
            target_extension = 0;
        }

        angle_offset = fmax(fmin(target_angle, MAX_ARM_ROTATION), MIN_ARM_ROTATION) - rotation();
        

        if (fabs(angle_offset) > 0.01)
        {
            upper_arm_motor.Set(-fmin(angle_offset, 1));
            std::cout << "Correct Rotation: " << rotation() << std::endl;
        }

        extension_offset = (fmax(fmin(target_extension, MAX_ARM_EXTENSION), MIN_ARM_EXTENSION) - extension());


        if (fabs(extension_offset) > 0.01)
        {

            lower_arm_motor.Set(fmin(extension_offset, 1));

            std::cout << "Correct Extension: " << extension() << std::endl;

        }
    }
};

void Arm::set_direct_rotation(float x)
{ lower_arm_motor.Set(x); }

void Arm::set_direct_extend(float x)
{ upper_arm_motor.Set(x); }
