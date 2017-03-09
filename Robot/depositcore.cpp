#define RED_LIGHT 0
#define BLUE_LIGHT 1

#include "depositcore.h"
#include "drivedistance.h"

DepositCore::DepositCore()
{
    STATE = RED;
}

void DepositCore::Init(Robot& robot)
{
    if (robot.RedLight)
    {
        STATE = RED_LIGHT;
    }
    else
    {
        STATE = BLUE_LIGHT;
    }

    Task* moveTask;
    if (STATE == BLUE_LIGHT)
    {
        moveTask = new DriveDistance(5);
    }
    else
    {
        moveTask = new DriveDistance(12);
    }
    moveTask->Init(robot);
}

bool DepositCore::Run(Robot& robot)
{
    Task* moveTask;
    if (STATE == BLUE_LIGHT)
    {
        moveTask = new DriveDistance(5);
    }
    else
    {
        moveTask = new DriveDistance(12);
    }

    return moveTask->Run(robot);
}

void DepositCore::Finish(Robot& robot)
{
    Task* moveTask;
    if (STATE == BLUE_LIGHT)
    {
        moveTask = new DriveDistance(5);
    }
    else
    {
        moveTask = new DriveDistance(12);
    }

    moveTask->Finish(robot);
}

bool DepositCore::isEnd()
{
    return false;
}
