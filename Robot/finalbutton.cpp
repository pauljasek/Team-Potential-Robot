#include "finalbutton.h"

#define RED_LIGHT 0
#define BLUE_LIGHT 1

#include "drivedistance.h"
#include "drivetime.h"
#include <taskexecutor.h>
#include <gotox.h>
#include <gotoy.h>
#include <orient.h>

FinalButton::FinalButton()
{
    STATE = RED;
}

void FinalButton::Init(Robot& robot)
{
    if (robot.GetRedLight())
    {
        STATE = RED_LIGHT;
    }
    else
    {
        STATE = BLUE_LIGHT;
    }

    TaskExecutor executor;
    if (STATE == BLUE_LIGHT)
    {
        //executor.Execute(robot, new GoToX(14.2, 25, 1));
        executor.Execute(robot, new Orient(0));
        executor.Execute(robot, new GoToX(3.7, 45, .2, false));
        executor.Execute(robot, new Orient(90));
        executor.Execute(robot, new DriveTime(10, -45));
    }
    else
    {
        executor.Execute(robot, new Orient(105));
        executor.Execute(robot, new DriveTime(10, -45));
    }
}

bool FinalButton::Run(Robot& robot)
{
    return true;
}

void FinalButton::Finish(Robot& robot)
{
}

bool FinalButton::isEnd()
{
    return false;
}