#define PI 3.14159265
#define RM -1
#define LM 1

#define MIN_POWER 20
#define MAX_POWER 20
#define POWER_CHANGE_FACTOR 2
#define POWER_DECREASE_FACTOR 5

#include "orient.h"

Orient::Orient(float orientation)
{
    Orientation = orientation;
    waited = false;
}

void Orient::Init(Robot& robot) {

    Sleep(.15);

    robot.Update();

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

    if (previous_difference < 0)
    {
        previous_difference += 1;
    }
    if (previous_difference > 0)
    {
        previous_difference -= 1;
    }

    robot.Turn(previous_difference, 20);
    Sleep(.15);
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
        if (heading_difference > -15)
        {
            robot.Turn(-.5, 20);
            Sleep(.15);
        }
        else
        {
            robot.Turn(-.5, 20);
            waited = false;
        }
    }
    else if (heading_difference > 1)
    {
        if (heading_difference < 15)
        {
            robot.Turn(.5,18);
            Sleep(.15);
        }
        else
        {
            robot.Turn(.5, 20);
            waited = false;
        }
    }
    else
    {
        if (waited)
        {
            return true;
        }
        else
        {
            waited = true;
            Sleep(.15);
            return false;
        }
    }
    return false;
}

/*bool Orient::Run(Robot &robot)
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

    float predicted_difference = (heading_difference - previous_difference) + heading_difference;

    if (abs(heading_difference) < 1)
    {
        return true;
    }

    float power = abs(heading_difference)*2.0;
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
    previous_difference = heading_difference;

    LCD.WriteLine(heading_difference);

    if (heading_difference < 0)
    {
        robot.Turn(-.5,power);
    }
    else if (heading_difference > 0)
    {
        robot.Turn(.5,power);
    }

    return false;
}*/

void Orient::Finish(Robot& robot)
{
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();

    LCD.WriteLine(robot.GetHeading());
}

bool Orient::isEnd()
{
    return false;
}
