#include "gotoy.h"
#include <math.h>
#include <orient.h>
#include <taskexecutor.h>

#define MIN_POWER 15
#define MAX_POWER 40
#define POWER_CHANGE_FACTOR 2
#define POWER_DECREASE_FACTOR 5

GoToY::GoToY(float y, float power)
{
    Y = y;
    Power = power;
    positive = false;
    waited = false;
    previous_power = MIN_POWER;
    Tolerance = .4;
    ChangeOrientation = true;
}

GoToY::GoToY(float y, float power, float tolerance)
{
    Y = y;
    Power = power;
    positive = false;
    waited = false;
    previous_power = MIN_POWER;
    Tolerance = tolerance;
    ChangeOrientation = true;
}

GoToY::GoToY(float y, float power, float tolerance, bool orient)
{
    Y = y;
    Power = power;
    positive = false;
    waited = false;
    previous_power = MIN_POWER;
    Tolerance = tolerance;
    ChangeOrientation = orient;
}

void GoToY::Init(Robot& robot) {
    TaskExecutor executor;

    float distance = Y - robot.GetY();


    if (distance * Power < 0)
    {
        if (ChangeOrientation) {
            executor.Execute(robot, new Orient(90));
        }
        positive = true;
    }
    else
    {
        if (ChangeOrientation) {
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

    previous_distance = Y - robot.GetY();

    StartX = robot.GetX();

    robot.DriveStraight(previous_distance, Power);

    Sleep(.3);

    /*robot.DriveFast(distance * Power/abs(Power));
    Sleep(.3);*/
}

bool GoToY::Run(Robot& robot)
{
    float distance = Y - robot.GetY();
    /*if (abs(distance) > 7)
    {
        waited = false;
        robot.DriveStraight(distance*2/5.0, Power);
        //robot.PIDDrive(distance, Power);
        return false;
    }*/
    if (abs(distance) > Tolerance)
    {
        robot.DriveStraight(distance*2/5.0, 13 * Power/abs(Power));
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

/*bool GoToY::Run(Robot& robot)
{
    float distance = Y - robot.GetY();

    float predicted_distance = (distance - previous_distance) + distance;\

    if (abs(predicted_distance) < .5)
    {
        return true;
    }

    //LCD.WriteLine(predicted_distance);

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

    LCD.WriteLine(power);

    robot.DriveTime(.1, power*predicted_distance/abs(predicted_distance));
    //robot.DriveStraight(predicted_distance/abs(predicted_distance) * .5, power);

    previous_distance = distance;

    return false;
}*/

void GoToY::Finish(Robot& robot)
{
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();
}

bool GoToY::isEnd()
{
    return false;
}
