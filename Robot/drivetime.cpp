#include "drivetime.h"

DriveTime::DriveTime(float time)
{
    Time = time;
    Percent = 40;
}

DriveTime::DriveTime(float time ,float percent)
{
    Time = time;
    Percent = percent;
}

void DriveTime::Init(Robot& robot)
{
}

bool DriveTime::Run(Robot& robot)
{
    robot.DriveTime(Time, Percent);
    return true;
}

void DriveTime::Finish(Robot& robot)
{
}

bool DriveTime::isEnd()
{
    return false;
}
