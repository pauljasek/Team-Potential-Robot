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
    LCD.WriteLine(robot.GetCdSCellValue());
    if(robot.GetCdSCellValue() < 1)
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

    Sleep(2.0);
}

void ReadLight::Finish(Robot& robot)
{
}

bool ReadLight::isEnd()
{
    return false;
}
