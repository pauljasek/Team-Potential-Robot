#include "drivedistance.h"

DriveDistance::DriveDistance(float distance)
{
    Distance = distance;
    // Set the default power level to 20%
    Percent = 20;
}

// Overloaded constructor to allow different power levels
DriveDistance::DriveDistance(float distance, float percent)
{
    Distance = distance;
    Percent = percent;
}

void DriveDistance::Init(Robot& robot)
{
    // No initial action
}

bool DriveDistance::Run(Robot& robot)
{
    // Drive the specified distance at the specified power level and exit the loop.
    robot.DriveStraight(Distance, Percent);
    return true;
}

void DriveDistance::Finish(Robot& robot)
{
    // No finishing action
}

bool DriveDistance::isEnd()
{
    return false;
}
