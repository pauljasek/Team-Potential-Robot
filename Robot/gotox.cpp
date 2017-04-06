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
    Tolerance = .2;
    ChangeOrientation = true;
}

GoToX::GoToX(float x, float power, float tolerance)
{
    X = x;
    Power = power;
    positive = false;
    waited = false;
    previous_power = MIN_POWER;
    previous_distance = 0;
    Tolerance = tolerance;
    ChangeOrientation = true;
}

GoToX::GoToX(float x, float power, float tolerance, bool orient)
{
    X = x;
    Power = power;
    positive = false;
    waited = false;
    previous_power = MIN_POWER;
    previous_distance = 0;
    Tolerance = tolerance;
    ChangeOrientation = orient;
}

void GoToX::Init(Robot& robot) {
    TaskExecutor executor;

    robot.WaitForRPS();
    robot.Update();

    /*if (RPS.Y() == -1)
    {
        return;
    }*/

    float distance = X - robot.GetX();


    if (distance * Power < 0)
    {
        if (ChangeOrientation) {
            executor.Execute(robot, new Orient(0));
        }
        positive = true;
    }
    else
    {
        if (ChangeOrientation) {
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

    if (ChangeOrientation)
    {
        robot.WaitForRPS();
    }

    previous_distance = X - robot.GetX();

    StartY = robot.GetY();

    robot.DriveStraight(previous_distance, Power);
    //Sleep(.3);
}

bool GoToX::Run(Robot& robot)
{
    robot.WaitForRPS();
    robot.Update();

    /*if (RPS.Y() == -1)
    {
        return true;
    }*/

    float distance = X - robot.GetX();

    /*if (abs(distance) > 7)
    {
        waited = false;
        robot.DriveStraight(distance*2/5.0, Power);
        //robot.PIDDrive(distance, Power);
        return false;
    }*/
    if (abs(distance) > Tolerance)
    {
        float power = 13 * Power/abs(Power);//Power/2;
        /*if (power > 0 && power < 15)
        {
            power = 15;
        }
        else if (power < 0 && power > -15)
        {
            power = -15;
        }*/
        robot.DriveStraight(distance, power);
        //Sleep(.1);
        //robot.WaitForRPS();
        //return true;
        return false;
    }
    return true;
    /*else
    {
        if (waited)
        {
            return true;
        }
        else
        {
            //Sleep(.1);

            waited = true;
            return true;
        }
    }*/
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

    //robot.Update();
    //LCD.WriteLine(robot.GetX());
}

bool GoToX::isEnd()
{
    return false;
}
