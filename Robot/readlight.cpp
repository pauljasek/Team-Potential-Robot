#include "readlight.h"
#include <FEHLCD.h>

ReadLight::ReadLight()
{
}

void ReadLight::Init(Robot& robot)
{
}

bool ReadLight::Run(Robot& robot)
{
    float cds_value = robot.DriveStraightReadLight(10, 25);
    LCD.WriteLine(cds_value);
    if(cds_value < 1)
    {
        robot.SetRedLight(true);
        LCD.WriteLine("Red");
    }
    else
    {
        robot.SetRedLight(false);
        LCD.WriteLine("Blue");
    }
    return true;
}

void ReadLight::Finish(Robot& robot)
{
}

bool ReadLight::isEnd()
{
    return false;
}
