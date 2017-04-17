#include "satellite.h"

Satellite::Satellite()
{

}

void Satellite::Init(Robot& robot)
{
    // Creates a task executor object
    TaskExecutor executor;

    // Calculates the desired angle to turn to.
    robot.WaitForRPS();
    robot.Update();
    float x = robot.GetX();
    float y = robot.GetY();
    float target_x = 35;
    float target_y = 13;
    float angle = atan2(abs(y - target_y), abs(x - target_x)) * 180.0 / 3.1415926;

    // Orients the robot to the calculated angle using RPS
    executor.Execute(robot, new Orient(180 - angle));
}

bool Satellite::Run(Robot& robot)
{
    // No loop action
    return true;
}

void Satellite::Finish(Robot& robot)
{
    // No finishing action
}

bool Satellite::isEnd()
{
    return false;
}
