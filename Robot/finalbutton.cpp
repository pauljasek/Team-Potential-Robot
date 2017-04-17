#include "finalbutton.h"

#define RED_LIGHT 0
#define BLUE_LIGHT 1

FinalButton::FinalButton()
{
    // Initializes the state to RED_LIGHT
    STATE = RED_LIGHT;
}

void FinalButton::Init(Robot& robot)
{
    // Sets the light state based on the read light action's outcome
    if (robot.GetRedLight())
    {
        STATE = RED_LIGHT;
    }
    else
    {
        STATE = BLUE_LIGHT;
    }

    // Initializes a task exutor object
    TaskExecutor executor;
    if (STATE == BLUE_LIGHT)
    {
        // If the blue light was read, turn, line up with the button, turn again and drive to the button
        executor.Execute(robot, new Orient(0));
        executor.Execute(robot, new GoToX(3.7, 45, .2, false));
        executor.Execute(robot, new Orient(90));
        executor.Execute(robot, new DriveTime(10, -45));
    }
    else
    {
        // If the red light was read, turn slightly and drive straight back to the button
        executor.Execute(robot, new Orient(105));
        executor.Execute(robot, new DriveTime(10, -45));
    }
}

bool FinalButton::Run(Robot& robot)
{
    // No looping action
    return true;
}

void FinalButton::Finish(Robot& robot)
{
    // No finishing action
}

bool FinalButton::isEnd()
{
    return false;
}
