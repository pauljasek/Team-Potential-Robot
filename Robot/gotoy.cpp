#include "gotoy.h"

#include <math.h>
#include <orient.h>
#include <taskexecutor.h>

GoToY::GoToY(float y, float power)
{
    Y = y;
    Power = power;
    positive = false;
}

void GoToY::Init(Robot& robot) {
    TaskExecutor executor;

    float distance = Y - robot.GetY();
    if (distance * Power < 0)
    {
        executor.Execute(robot, new Orient(90));
        positive = true;
    }
    else
    {
        executor.Execute(robot, new Orient(270));
    }

    if (Power < 0)
    {
        positive = !positive;
    }

    if (positive == true)
    {
        Power *= -1;
    }

    StartX = robot.GetX();
    Sleep(.5);
}

bool GoToY::Run(Robot& robot)
{
    float distance = Y - robot.GetY();
    if (abs(distance) > 5)
    {
        robot.DriveStraight(distance*3/5.0, Power);
        return false;
    }
    if (abs(distance) > .2)
    {
        robot.DriveStraight(distance*3/5.0, 15 * Power/abs(Power));
        Sleep(.1);
        return false;
    }
    else
    {
        return true;
    }
}

void GoToY::Finish(Robot& robot)
{
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();
}

bool GoToY::isEnd()
{
    return false;
}
