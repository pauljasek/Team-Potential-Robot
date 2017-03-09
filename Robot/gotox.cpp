#include "gotox.h"

#define PI 3.14159265
#define RM 1
#define LM -1


#include <math.h>
#include <orient.h>
#include <taskexecutor.h>

GoToX::GoToX(float x, float power)
{
    X = x;
    Power = power;
    positive = false;
}

void GoToX::Init(Robot& robot) {
    TaskExecutor executor;

    float distance = X - robot.GetX();
    if (abs(distance) > 1)
    {
        if (distance * Power < 0)
        {
            positive = true;
            executor.Execute(robot, new Orient(0));
        }
        else
        {
            executor.Execute(robot, new Orient(180));
        }
    }

    if (Power < 0)
    {
        positive = !positive;
    }

    if (positive == true)
    {
        Power *= -1;
    }

    StartY = robot.GetY();
    Sleep(.5);
}

bool GoToX::Run(Robot& robot)
{
    float distance = X - robot.GetX();

    if (abs(distance) > 1)
    {
        robot.DriveStraight(distance*3/4.0, Power);
        return false;
    }
    else
    {
        return true;
    }
}

void GoToX::Finish(Robot& robot)
{
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();
}

bool GoToX::isEnd()
{
    return false;
}
