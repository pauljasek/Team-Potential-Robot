#include "toplevel.h"

TopLevel::TopLevel()
{
}

void TopLevel::Init(Robot& robot) {
    // Set the robot motors to a turn.
    robot.LeftMotor.SetPercent(-43);
    robot.RightMotor.SetPercent(20);

    // Continue turning until the bump switch is pressed or 1 second passes.
    float initialTime = TimeNow();
    while(robot.ArmBumper.Value() && TimeNow() - initialTime < 1){}

    // Wait an additional .3 seconds.
    Sleep(.3);

    // Stop running the motors.
    robot.LeftMotor.Stop();
    robot.RightMotor.Stop();
}

bool TopLevel::Run(Robot& robot)
{
    // No looping action
    return true;
}

void TopLevel::Finish(Robot& robot)
{
    // No finishing action
}

bool TopLevel::isEnd()
{
    return false;
}
