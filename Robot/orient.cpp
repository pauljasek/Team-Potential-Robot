#define PI 3.14159265
#define RM -1
#define LM 1

#include "orient.h"

Orient::Orient(float orientation)
{
    Orientation = orientation;
}

void Orient::Init(Robot& robot) {
}

bool Orient::Run(Robot& robot)
{
    float desired_heading = Orientation;
    if (desired_heading <= -180)
    {
        desired_heading += 360;
    }
    float heading_difference = desired_heading - robot.GetHeading();
    if (heading_difference > 180)
    {
        heading_difference -= 360;
    }
    if (heading_difference <= -180)
    {
        heading_difference += 360;
    }

    if (heading_difference < -1)
    {
        if (heading_difference > -10)
        {
            robot.Turn(-.5,20);
        }
        else
        {
            robot.Turn(-3, 20);
        }
        Sleep(.1);
    }
    else if (heading_difference > 1)
    {
        if (heading_difference < 10)
        {
            robot.Turn(.5,20);
        }
        else
        {
            robot.Turn(3,20);
        }
        Sleep(.1);
    }
    else
    {
        return true;
    }
    return false;
}

void Orient::Finish(Robot& robot)
{
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();
}

bool Orient::isEnd()
{
    return false;
}