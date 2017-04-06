#define RED_LIGHT 0
#define BLUE_LIGHT 1

#include "depositcore.h"
#include "drivedistance.h"
#include <taskexecutor.h>
#include <gotox.h>
#include <gotoy.h>

DepositCore::DepositCore()
{
    STATE = RED;
}

void DepositCore::Init(Robot& robot)
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
        //executor.Execute(robot, new GoToX(18, 40, 2));
        executor.Execute(robot, new GoToX(14.2, 35, .2));

        //executor.Execute(robot, new GoToX(18.2, -35));

    }
    else
    {
        //executor.Execute(robot, new GoToX(10, 40, 2));
        executor.Execute(robot, new GoToX(6.1, 30, .2));
        //executor.Execute(robot, new GoToX(10, -35));
    }
}

bool DepositCore::Run(Robot& robot)
{
    return true;
}

void DepositCore::Finish(Robot& robot)
{
}

bool DepositCore::isEnd()
{
    return false;
}
