#include "orient.h"

// Basic constructor specifying RPS orientation
Orient::Orient(float orientation)
{
    Orientation = orientation;
    waited = false;
    Check = true;
}

// Overloaded constructor to specify whether or not the check orientation
// after the initial turn
Orient::Orient(float orientation, bool check)
{
    Orientation = orientation;
    waited = false;
    Check = check;
}

void Orient::Init(Robot& robot) {
    // Updates RPS coordinates
    robot.WaitForRPS();
    robot.Update();

    // Calculates the difference in orientation and desired heading
    float desired_heading = Orientation;
    if (desired_heading <= -180)
    {
        desired_heading += 360;
    }
    previous_difference = desired_heading - robot.GetHeading();
    if (previous_difference > 180)
    {
        previous_difference -= 360;
    }
    if (previous_difference <= -180)
    {
        previous_difference += 360;
    }

    // Turns to the calculated angle using encoders
    robot.Turn(previous_difference, 30);

    // If a check is desired, waits for the RPS coordinates to stabilize.
    if (Check)
    {
        robot.WaitForRPS();
    }
}

bool Orient::Run(Robot& robot)
{
    // If no check is required, exits the loop
    if (!Check)
    {
        return true;
    }

    // Otherwise, updates RPS coordinates
    Sleep(.15);
    robot.Update();

    // Calculates the difference between the current heading and the desired orientation
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

    // If |difference| > 1, turns the required distance
    if (heading_difference < -1)
    {
            robot.Turn(-.5, 18);
            return false;
    }
    else if (heading_difference > 1)
    {
            robot.Turn(.5,18);
            return false;
    }
    // Otherwise, exits the loop, because the heading is within the required tolerance.
    return true;
}

void Orient::Finish(Robot& robot)
{
    // Stops the motors, if required.
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();
}

bool Orient::isEnd()
{
    return false;
}
