#include "gotox.h"

#define PI 3.14159265
#define RM 1
#define LM -1

#define MIN_POWER 15
#define MAX_POWER 40
#define POWER_CHANGE_FACTOR 2
#define POWER_DECREASE_FACTOR 5

#include <math.h>
#include <orient.h>
#include <taskexecutor.h>

GoToX::GoToX(float x, float power)
{
    X = x;
    Power = power;
    positive = false;
    waited = false;
    previous_power = MIN_POWER;
    previous_distance = 0;
}

void GoToX::Init(Robot& robot) {
    TaskExecutor executor;

    float distance = X - robot.GetX();

    if (distance * Power < 0)
    {
        positive = true;
        executor.Execute(robot, new Orient(0));
    }
    else
    {
        executor.Execute(robot, new Orient(180));
    }

    if (Power < 0)
    {
        positive = !positive;
    }

    if (positive == true)
    {
        Power *= -1;
    }

    previous_distance = X - robot.GetX();

    StartY = robot.GetY();
}

bool GoToX::Run(Robot& robot)
{
    float distance = X - robot.GetX();

    if (abs(distance) > 7)
    {
        waited = false;
        robot.DriveStraight(distance*3/5.0, Power);
        return false;
    }
    else if (abs(distance) > .2)
    {
        robot.DriveStraight(distance*3/5.0, 13 * Power/abs(Power));
        Sleep(.1);
        return false;
    }
    else
    {
        if (waited)
        {
            return true;
        }
        else
        {
            Sleep(.1);
            waited = true;
            return false;
        }
    }
}

/*bool GoToX::Run(Robot &robot) {
    float distance = X - robot.GetX();

    float predicted_distance = (distance - previous_distance) + distance;

    if (abs(predicted_distance) < .5)
    {
        return true;
    }

    float power = abs(predicted_distance) * 4.0;
    if(power > MAX_POWER)
    {
        power = MAX_POWER;
    }
    if(power < MIN_POWER)
    {
        power = MIN_POWER;
    }

    if(power > previous_power + POWER_CHANGE_FACTOR)
    {
        power = previous_power + POWER_CHANGE_FACTOR;
    }

    if(power < previous_power - POWER_DECREASE_FACTOR)
    {
        power = previous_power - POWER_DECREASE_FACTOR;
    }

    previous_power = power;

    if (Power < 0)
    {
        power *= -1;
    }

    robot.DriveTime(.1, power*predicted_distance/abs(predicted_distance));

    previous_distance = distance;

    return false;
}*/

void GoToX::Finish(Robot& robot)
{
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();

    robot.Update();
    LCD.WriteLine(robot.GetX());
}

bool GoToX::isEnd()
{
    return false;
}
