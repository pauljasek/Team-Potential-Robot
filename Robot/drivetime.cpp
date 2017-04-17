#include "drivetime.h"

DriveTime::DriveTime(float time)
{
    Time = time;
    // Set the initial power level to 40%
    Percent = 40;
}

// Overloaded constructor to set custom power level
DriveTime::DriveTime(float time, float percent)
{
    Time = time;
    Percent = percent;
}

void DriveTime::Init(Robot& robot)
{
    // No initialization action
}

bool DriveTime::Run(Robot& robot)
{
    // Drive the robot for a specified amount of time and exit the loop
    robot.DriveTime(Time, Percent);
    return true;
}

void DriveTime::Finish(Robot& robot)
{
    // No finishing action
}

bool DriveTime::isEnd()
{
    return false;
}
