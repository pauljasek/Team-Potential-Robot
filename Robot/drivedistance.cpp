#include "drivedistance.h"

DriveDistance::DriveDistance(float distance)
{
    Distance = distance;
    Percent = 40;
}

DriveDistance::DriveDistance(float distance ,float percent)
{
    Distance = distance;
    Percent = percent;
}

void DriveDistance::Init(Robot& robot)
{
}

bool DriveDistance::Run(Robot& robot)
{
    robot.DriveStraight(Distance, Percent);
    return true;
}

void DriveDistance::Finish(Robot& robot)
{
}

bool DriveDistance::isEnd()
{
    return false;
}
