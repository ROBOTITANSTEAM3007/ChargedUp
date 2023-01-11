#include <Drive.h>

Drive::Drive(rev::CANSparkMax* leftSide, rev::CANSparkMax* rightSide) {
    rightMaxDrive = rightSide;
    leftMaxDrive = leftSide;
}
Drive::Drive(frc::Spark* leftSide, frc::Spark* rightSide) {
    rightSparkDrive = rightSide;
    leftSparkDrive = leftSide;
}

void Drive::vroom(float x,  float y) {
    /* we probably dont need this since we already check if the inputs exceed the deadzone
    if (x < 0.1 && x > -0.1) {
        x = 0;
    }
    if (y < 0.1 && y > -0.1) {
        y = 0;
    }
    */
    float leftDrive = y + x;
    float rightDrive = y - x;
    if (leftDrive > 1) {
        leftDrive = 1;
    } else if (leftDrive < -1) {
        leftDrive = -1;
    }
    if (rightDrive > 1) {
        rightDrive = 1;
    } else if (rightDrive < -1) {
        rightDrive = -1;
    }

    rightMaxDrive->Set(rightDrive);
    leftMaxDrive->Set(leftDrive);
}
