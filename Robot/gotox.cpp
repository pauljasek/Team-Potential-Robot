#include "gotox.h"

#define MIN_POWER 15
#define MAX_POWER 40

// Constructor with default tolerance and orientation check
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

// Constructor that allows for raising and lowering the tolerance
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

// Constructor that allows for raising and lowering the tolerance
// and specifying whether or not to check orientation
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
    // Creates a task executor object
    TaskExecutor executor;

    // Updates RPS coordinates
    robot.WaitForRPS();
    robot.Update();

    // Calculates the distance to drive
    float distance = X - robot.GetX();

    // Changes orientation to drive if desired
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

    // Calculating which direction to turn motors
    if (Power < 0)
    {
        positive = !positive;
    }
    if (positive == true)
    {
        Power *= -1;
    }

    // Updates RPS coordinates, if robot turned
    if (ChangeOrientation)
    {
        robot.WaitForRPS();
        robot.Update();
    }

    // Makes an initial drive to the desired location using encoder values
    previous_distance = X - robot.GetX();
    StartY = robot.GetY();
    robot.DriveStraight(previous_distance, Power);
}

bool GoToX::Run(Robot& robot)
{
    // Checks RPS position
    robot.WaitForRPS();
    robot.Update();

    // Calculates the distance to drive
    float distance = X - robot.GetX();

    // If the distance is not within the tolerance, drives the distance and reenters the loop
    if (abs(distance) > Tolerance)
    {
        float power = 13 * Power/abs(Power);//Power/2;
        robot.DriveStraight(distance * 9.0/10.0, power);
        return false;
    }
    // Otherwise, exits the loop
    return true;
}

void GoToX::Finish(Robot& robot)
{
    // Stops the motors
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();
}

bool GoToX::isEnd()
{
    return false;
}
