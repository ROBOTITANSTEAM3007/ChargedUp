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

double Arm::height()
{ 
    return 
    SHOULDER_HEIGHT // Height of the shoulder to the ground
    + sqrt(pow((RETRACTED_LOWER_ARM_LENGTH + extension()), 2) + pow(UPPER_ARM_LENGTH, 2)) // Height of the arm
    * sin(rotation() * (M_PI / 180) + atan((RETRACTED_LOWER_ARM_LENGTH + extension()) / UPPER_ARM_LENGTH));
}

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

    extension_PID_controller.SetP(frc::SmartDashboard::GetNumber("Extension P", extension_PID.proportion));
    extension_PID_controller.SetI(frc::SmartDashboard::GetNumber("Extension I", extension_PID.integral));
    extension_PID_controller.SetD(frc::SmartDashboard::GetNumber("Extension D", extension_PID.derivative));

    rotation_PID_controller.SetP(frc::SmartDashboard::GetNumber("Rotation P", rotation_PID.proportion));
    rotation_PID_controller.SetI(frc::SmartDashboard::GetNumber("Rotation I", rotation_PID.integral));
    rotation_PID_controller.SetD(frc::SmartDashboard::GetNumber("Rotation D", rotation_PID.derivative));

    frc::SmartDashboard::PutNumber("poten diff", extension_offset);
    frc::SmartDashboard::PutNumber("Rotation Offset", rotation_offset);

    // Run Manual
    if(!manual){
        rotation_offset = (target_angle - rotation()) / ARM_ROTATION_CONSTANT;
        extension_offset = (target_extension - extension()) / ARM_EXTENSION_CONSTANT;
        safe_extension_offset = (SAFE_TARGET_EXTENSION - extension()) / ARM_EXTENSION_CONSTANT;

        // To prevent getting out of bounds
        if (rotation() < FREE_EXTENSION_POINT)
        { extension_offset = fmin(extension_offset, safe_extension_offset); }

        if (!(target_angle < FREE_EXTENSION_POINT && extension() > (SAFE_TARGET_EXTENSION + 1)))
        {
            // Rotates Arm.
            // this->upper_arm_motor.Set(-std::clamp(rotation_PID_controller.Calculate(rotation(), target_angle), -1.00, 1.00));

            if (fabs(rotation_offset) < ROTATION_PID_ZONE)
            { this->upper_arm_motor.Set(-std::clamp(rotation_PID_controller.Calculate(rotation(), target_angle), -1.00, 1.00)); }
            else
            { this->upper_arm_motor.Set(-std::clamp(rotation_offset, -0.80, 0.80)); }   
        }
        


        if (rotation() > MAX_UNSAFE_EXTENSION_ZONE || rotation() < MIN_UNSAFE_EXTENSION_ZONE)
        {
            // Extends and Retracts Arm.
            // this->lower_arm_motor.Set(-std::clamp(extension_PID_controller.Calculate(extension(), target_extension), -1.00, 1.00));
            if (fabs(extension_offset) < EXTENSION_PID_ZONE)
            { this->lower_arm_motor.Set(-std::clamp(extension_PID_controller.Calculate(extension(), target_extension), -1.00, 1.00)); }
            else
            { this->lower_arm_motor.Set(-std::clamp(target_extension, -1.00, 1.00)); }
        }


        // Turns manual off when in correct locations.
        // if (fabs(rotation_offset) <= MOVMENT_SUCCESS_ZONE && fabs(extension_offset) <= MOVMENT_SUCCESS_ZONE)
        // { this->manual = true; }
    }

    speed = speed.maximum(-1).minimum(1);

    // lower_arm_motor.Set(speed.y);
    // upper_arm_motor.Set(speed.x);
};

// void Arm::set_direct_rotation(float input)
// { this->speed = Vector2D{input, speed.y}; }

// void Arm::set_direct_extend(float input)
// { this->speed = Vector2D{speed.x, input}; }

void Arm::set_direct_rotation(float input)
{ 
    if (rotation() < MAX_UNSAFE_EXTENSION_ZONE && extension() > SAFE_TARGET_EXTENSION && input != 0)
    {
        this->upper_arm_motor.Set(0);
        this->lower_arm_motor.Set(1);
    }
    else
    {
        this->upper_arm_motor.Set(input);
    }
}

void Arm::set_direct_extend(float input)
{

    if (rotation() < MAX_UNSAFE_EXTENSION_ZONE && extension() > SAFE_TARGET_EXTENSION)
    { input = std::clamp(input, (float)0.00, (float)1.00); }

    this->lower_arm_motor.Set(input);
}


bool Arm::cone_auto_place_high(Drive &drive) {
    frc::SmartDashboard::PutNumber("poten diff", extension_offset);
    frc::SmartDashboard::PutNumber("poten ext", rotation_offset);

    if (!finished_cone_placment)
    {
        move_to_high_cone();

        this->target_angle = 164;

        rotation_offset = (target_angle - rotation()) / ARM_ROTATION_CONSTANT;
        extension_offset = (target_extension - extension()) / ARM_EXTENSION_CONSTANT;
        frc::SmartDashboard::PutNumber("Rotation Offset", rotation_offset);

        if (fabs(rotation_offset) < MOVMENT_SUCCESS_ZONE && fabs(extension_offset) < MOVMENT_SUCCESS_ZONE)
        {
            hand_solenoid.Set(true);

            finished_cone_placment = true;
        }

        return false;
    }
    else if (finished_cone_placment && !finished_arm_reset)
    {
        move_to_grab();

        rotation_offset = (target_angle - rotation()) / ARM_ROTATION_CONSTANT;
        extension_offset = (target_extension - extension()) / ARM_EXTENSION_CONSTANT;

        if (fabs(rotation_offset) < MOVMENT_SUCCESS_ZONE && fabs(extension_offset) < MOVMENT_SUCCESS_ZONE)
        {
            finished_arm_reset =  true;
        }

        return false;
    }

    return true;
}

void Arm::cone_auto_place_mid(Drive &drive) {
}

void Arm::move_to_mid_cone()
{
    this->manual = false;

    this->target_angle = 177;
    this->target_extension = 14.7;
}

void Arm::move_to_high_cone()
{
    this->manual = false;

    this->target_angle = 166;
    this->target_extension = 33.0;
}

void Arm::move_to_grab()
{
    this->manual = false;

    this->target_angle = 10;
    this->target_extension = 6.0;
    this->hand_solenoid.Set(true);
}