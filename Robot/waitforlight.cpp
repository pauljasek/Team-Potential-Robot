#include "waitforlight.h"

WaitForLight::WaitForLight()
{
    /*
     * Initializes variable values.
     */
    PreviousValue = 0;
    Checks = 0;
}

void WaitForLight::Init(Robot& robot)
{
    /*
     * Remembers starting value of CdS cell.
     */
    PreviousValue = robot.GetCdSCellValue();
    Checks = 0;
}

bool WaitForLight::Run(Robot& robot)
{
    /*
     * Waits .2 seconds and returns completion if enough time has elapsed or change in CdS reading is large enough.
     */
    Sleep(.2);
    bool start = Checks > 75 || PreviousValue - robot.GetCdSCellValue() > .3;
    PreviousValue = robot.GetCdSCellValue();

    Checks++;
    return start;
}

void WaitForLight::Finish(Robot& robot)
{
}

bool WaitForLight::isEnd()
{
    return false;
}
