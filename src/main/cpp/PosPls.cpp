
#include "PosPls.h"


PP::PP(rev::SparkMaxRelativeEncoder* inRel) {
    previous_tick = std::chrono::high_resolution_clock::now();
    rel=inRel;
    lastPosition = rel->GetPosition();
}

/*void PP::PPP() {

    this->current_tick = std::chrono::high_resolution_clock::now();

    this->Acceleration.x = this->accel.GetX();
    this->Acceleration.y = this->accel.GetY();
    this->Acceleration.z = this->accel.GetZ();

    // 1 Second = 1,000,000 Microseconds
    this->delta_time = std::chrono::duration_cast<std::chrono::microseconds>(this->current_tick - this->previous_tick).count();


    this->Jerk.x = ((this->Acceleration.x - this->lastAcceleration.x)/(this->delta_time/MICROSECOND_PER_SECOND));
    this->Jerk.y = ((this->Acceleration.y - this->lastAcceleration.y)/(this->delta_time/MICROSECOND_PER_SECOND));
    this->Jerk.z = ((this->Acceleration.z - this->lastAcceleration.z)/(this->delta_time/MICROSECOND_PER_SECOND));

    // std::cout << "Jerk = " << this->Jerk.x << " " << this->Jerk.y << " " << this->Jerk.z << std::endl;

    // frc::SmartDashboard::PutNumber("Jerk-x", this->Jerk.x);
    // frc::SmartDashboard::PutNumber("Jerk-y", this->Jerk.y);
    // frc::SmartDashboard::PutNumber("Jerk-z", this->Jerk.z);

    this->pos.x = this->pos.x + (std::pow(this->Jerk.x, 3)* (1/6));
    this->pos.y = this->pos.y + (std::pow(this->Jerk.y, 3)* (1/6));
    this->pos.z = this->pos.z + (std::pow(this->Jerk.z, 3)* (1/6));

    // frc::SmartDashboard::PutNumber("Acceleration", this->Jerk.x);
    // frc::SmartDashboard::PutNumber("Acceleration", this->Jerk.y);
    // frc::SmartDashboard::PutNumber("Acceleration", this->Jerk.z);

    // std::cout << "Position = " << this->pos.x << ", " << this->pos.y << ", " << this->pos.z << std::endl;

    // frc::SmartDashboard::PutNumber("Position-x", this->pos.x);
    // frc::SmartDashboard::PutNumber("Position-y", this->pos.y);
    // frc::SmartDashboard::PutNumber("Position-z", this->pos.z);

    this->lastAcceleration = this->Acceleration;

    this->previous_tick = std::chrono::high_resolution_clock::now();
}*/


double PP::spinPP() {
    posDifference = rel->GetPosition() - lastPosition;
    posDifference /= 10.71;
    posDifference *= 18.849555924; //Circumfrence in inches
    pos.y += posDifference;
    lastPosition = rel->GetPosition();
    return(pos.y);
}
