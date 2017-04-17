#define RED_LIGHT 0
#define BLUE_LIGHT 1

#include "depositcore.h"

DepositCore::DepositCore()
{
    // Initialize the state to a default of RED_LIGHT
    STATE = RED_LIGHT;
}

void DepositCore::Init(Robot& robot)
{
    // Set the state depending on the outcome of the read light action
    if (robot.GetRedLight())
    {
        STATE = RED_LIGHT;
    }
    else
    {
        STATE = BLUE_LIGHT;
    }

    // Initialize a task executor object and drive to the appropriate bin,
    // depending on the value of the light using the RPS coordinates.
    TaskExecutor executor;
    if (STATE == BLUE_LIGHT)
    {
        executor.Execute(robot, new GoToX(14.2, 35, .2));
    }
    else
    {
        executor.Execute(robot, new GoToX(6.1, 30, .2));
    }
}

bool DepositCore::Run(Robot& robot)
{
    // Make no action and exit the loop.
    return true;
}

void DepositCore::Finish(Robot& robot)
{
    // No finishing action
}

bool DepositCore::isEnd()
{
    return false;
}
