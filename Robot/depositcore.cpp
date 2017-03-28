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
        executor.Execute(robot, new GoToX(14.2, 25));
    }
    else
    {
        executor.Execute(robot, new GoToX(6.75, 25));
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
