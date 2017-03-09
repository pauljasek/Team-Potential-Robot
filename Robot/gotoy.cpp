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
    if (abs(distance) > 1)
    {
        if (distance * Power < 0)
        {
            executor.Execute(robot, new Orient(90));
            positive = true;
        }
        else
        {
            executor.Execute(robot, new Orient(270));
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

    StartX = robot.GetX();
    Sleep(.5);
}

bool GoToY::Run(Robot& robot)
{
    float distance = Y - robot.GetY();
    if (abs(distance) > 1)
    {
        LCD.Clear();
        LCD.WriteLine(distance);
        LCD.WriteLine(Power);
        LCD.WriteLine(positive);
        robot.DriveStraight(distance*3/4.0, Power);
        //robot.DriveStraight(1, Power);
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
