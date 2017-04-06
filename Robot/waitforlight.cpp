#include "waitforlight.h"

WaitForLight::WaitForLight()
{
    /*
     * Initializes variable values.
     */
    PreviousValue = 0;
    EndTime = 0;
}

void WaitForLight::Init(Robot& robot)
{
    robot.Update();
    /*
     * Remembers starting value of CdS cell.
     */
    PreviousValue = robot.GetCdSCellValue();
    EndTime = TimeNow() + 45;
}

bool WaitForLight::Run(Robot& robot)
{
    /*
     * Waits .2 seconds and returns completion if enough time has elapsed or change in CdS reading is large enough.
     */
    Sleep(.2);
    float cds_value = robot.CdSCell.Value();
    bool start = TimeNow() > EndTime || PreviousValue - cds_value > .3;
    PreviousValue = cds_value;

    return start;
}

void WaitForLight::Finish(Robot& robot)
{
}

bool WaitForLight::isEnd()
{
    return false;
}
