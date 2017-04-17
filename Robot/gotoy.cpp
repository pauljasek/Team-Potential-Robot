#include "gotoy.h"

#define MIN_POWER 15
#define MAX_POWER 40

// Constructor with default tolerance and orientation check
GoToY::GoToY(float y, float power)
{
    Y = y;
    Power = power;
    positive = false;
    waited = false;
    previous_power = MIN_POWER;
    Tolerance = .2;
    ChangeOrientation = true;
}

// Constructor that allows for raising and lowering the tolerance
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

// Constructor that allows for raising and lowering the tolerance
// and specifying whether or not to check orientation
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
    // Creates a task executor object
    TaskExecutor executor;

    // Updates RPS coordinates
    robot.WaitForRPS();
    robot.Update();

    // Calculates the distance to drive
    float distance = Y - robot.GetY();

    // Changes orientation to drive if desired
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
    previous_distance = Y - robot.GetY();
    StartX = robot.GetX();
    robot.DriveStraight(previous_distance, Power);
}

bool GoToY::Run(Robot& robot)
{
    // Checks RPS position
    robot.WaitForRPS();
    robot.Update();

    // Exits loop if in the no-RPS zone
    if (RPS.Y() == -1)
    {
        return true;
    }

    // Calculates the distance to drive
    float distance = Y - robot.GetY();

    // If the distance is not within the tolerance, drives the distance and reenters the loop
    if (abs(distance) > Tolerance)
    {
        float power = 13 * Power/abs(Power);
        robot.DriveStraight(distance * 9.0/10.0, power);
    }
    // Otherwise, exits the loop
    return true;
}

void GoToY::Finish(Robot& robot)
{
    // Stops the motors
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();
}

bool GoToY::isEnd()
{
    return false;
}
