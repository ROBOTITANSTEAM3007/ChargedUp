#include "Arm.h"

Arm::Arm() {
    this->target_extension = 0;
    this->target_angle = 0;
    this->speed = Vector2D{0, 0};
//     this->analogExt.SetAverageBits(8);
//     this->fs.open("calib.bin", std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
//     if(!this->fs.is_open()) {
//         this->fs.read((char*)(&extensionSlope), sizeof(extensionSlope));
//     }
};

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

double Arm::potentiometer_value()
{
    current_potentiometer_value = extension_potentiometer.Get();

    if (current_potentiometer_value < 0)
    { return previous_potentiometer_value; }
    
    else
    { previous_potentiometer_value = current_potentiometer_value; }

    return current_potentiometer_value;
}

double Arm::extension(){
    avrgExtension = 0;

    for(int i = 0; i < 9; i++)
    { avrgExtension += ext[i]; }

    avrgExtension = avrgExtension / 10; // Average of the values

    return((avrgExtension * ARM_EXTENSION_CONSTANT));
}

double Arm::rotation() // Degrees
{ return (encoder.GetAbsolutePosition() - ENCODER_OFFSET) * ARM_ROTATION_CONSTANT; }

double Arm::distance() // From the shoulder point to the hand
{ return sqrt(pow(extension(), 2) * pow(UPPER_ARM_LENGTH, 2)); }

void Arm::update_average_extension(double input)
{
    // Get the average of the past 10 potentiometer reads
    ext[iterations] = input;
    
    if(iterations < 9)
    { iterations++; }
    else
    { iterations = 0; }
}

void Arm::periodic() {
    update_average_extension(potentiometer_value() - POTENTIOMETER_OFFSET);

    // Run Manual
    if(!manual){
        rotation_offset = target_angle - rotation();
        extension_offset = target_extension - extension();
        safe_extension_offset = SAFE_TARGET_EXTENSION - extension();
        
        // Rotates Arm.
        if (fabs(rotation_offset) > MOVMENT_SUCCESS_ZONE)
        { this->speed += Vector2D{-fmax(fmin(rotation_offset * 2, 1), -1), 0}; }
        else
        { std::cout << "Correct Rotation: " << rotation() << std::endl; }



        // Extends and Retracts Arm.
        if (fabs(extension_offset) > MOVMENT_SUCCESS_ZONE)
        { this->speed += Vector2D{0, -fmax(fmin(extension_offset, 1), -1)}; }
        else
        { std::cout << "Correct Extension: " << extension() << std::endl; }

        // Turns manual off when in correct locations.
        if (fabs(rotation_offset) <= MOVMENT_SUCCESS_ZONE && fabs(extension_offset) <= MOVMENT_SUCCESS_ZONE)
        { this->manual = true; }
    }

    lower_arm_motor.Set(speed.y);
    upper_arm_motor.Set(speed.x);
};

void Arm::set_direct_rotation(float input)
{ this->speed = Vector2D{input, speed.y}; }

void Arm::set_direct_extend(float input)
{ this->speed = Vector2D{speed.x, input}; }


void Arm::cone_auto_place_high() {
    this->manual = false;
    this->target_angle = 0;//Change ME!!!
    this->target_extension = 0;
}

void Arm::cone_auto_place_mid() {
    this->manual = false;
    this->target_angle = 0;//Change ME!!!
    this->target_extension = 0;
}

void Arm::cube_auto_place_high() {
    this->manual = false;
    this->target_angle = 0;//Change ME!!!
    this->target_extension = 0;
}

void Arm::cube_auto_place_mid() {
    this->manual = false;
    this->target_angle = 0;//Change ME!!!
    this->target_extension = 0;
}


void Arm::move_to_high()
{
    this->manual = false;

    this->target_angle = 165;
    this->target_extension = 28.0;
}

void Arm::move_to_grab()
{
    this->manual = false;

    this->target_angle = 0;
    this->target_extension = 5.0;
    this->hand_solenoid.Set(true);
}