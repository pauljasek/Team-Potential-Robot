#include "moveservo.h"

MoveServo::MoveServo(float degree)
{
    // Sets the degrees to move the servo when the task is executed
    Degree = degree;
}

void MoveServo::Init(Robot& robot)
{
    // No initialization action
}

bool MoveServo::Run(Robot& robot)
{
    // Set the servo to the specified amount of degrees
    robot.Servo.SetDegree(Degree);
    return true;
}

void MoveServo::Finish(Robot& robot)
{
    // No finishing action
}

bool MoveServo::isEnd()
{
    return false;
}
