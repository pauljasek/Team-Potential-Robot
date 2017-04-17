#include "readlight.h"

ReadLight::ReadLight()
{
    // No constructing action
}

void ReadLight::Init(Robot& robot)
{
    // No initialization action
}

bool ReadLight::Run(Robot& robot)
{
    // The robot drives straight and returns the lowest CdS Cell value
    float cds_value = robot.DriveStraightReadLight(10, 30);

    // The value is displayed to the screen
    LCD.WriteLine(cds_value);

    // If the value is less than 1, the light color is set to red and
    // is displayed to the screen. Otherwise, the light color is set to
    // blue and is displayed to the screen.
    if(cds_value < 1)
    {
        robot.SetRedLight(true);
        LCD.WriteLine("Red");
        LCD.Clear(RED);
    }
    else
    {
        robot.SetRedLight(false);
        LCD.WriteLine("Blue");
        LCD.Clear(BLUE);
    }
    return true;
}

void ReadLight::Finish(Robot& robot)
{
    // No finishing action
}

bool ReadLight::isEnd()
{
    return false;
}
