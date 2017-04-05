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
    float cds_value = robot.DriveStraightReadLight(8, 45);
    LCD.WriteLine(cds_value);
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
}

bool ReadLight::isEnd()
{
    return false;
}
