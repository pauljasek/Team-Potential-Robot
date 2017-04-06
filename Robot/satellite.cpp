#include "satellite.h"
#include "drivedistance.h"
#include "drivetime.h"
#include <taskexecutor.h>
#include <gotox.h>
#include <gotoy.h>
#include <orient.h>
#include <moveservo.h>
#include <robot.h>

Satellite::Satellite()
{

}

void Satellite::Init(Robot& robot)
{
    TaskExecutor executor;

    robot.WaitForRPS();
    robot.Update();
    float x = robot.GetX();
    float y = robot.GetY();

    float target_x = 36;
    float target_y = 13;

    LCD.WriteLine(x);
    LCD.WriteLine(y);

    float angle = atan2(abs(y - target_y), abs(x - target_x)) * 180.0 / 3.1415926;

    LCD.WriteLine(angle);

    executor.Execute(robot, new Orient(180 - angle));


    /*robot.DriveArc(4, 45, 1, .5);
    //robot.DriveArc(2, 45, .75, 1);

    executor.Execute(robot, new DriveTime(1, 45));
    executor.Execute(robot, new GoToX(19, -35, 1, false));
    executor.Execute(robot, new MoveServo(70));*/
}

bool Satellite::Run(Robot& robot)
{
    return true;
}

void Satellite::Finish(Robot& robot)
{
}

bool Satellite::isEnd()
{
    return false;
}
