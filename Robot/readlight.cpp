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
        robot.RedLight = true;
    }
    else
    {
        robot.RedLight = false;
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
