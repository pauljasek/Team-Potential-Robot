#include <robot.h>
#include <math.h>
#include <task.h>
#include <drive.h>
#include <waitfortouch.h>
#include <waitforlight.h>
#include <end.h>
#include <orient.h>
#include <moveservo.h>
#include <drivedistance.h>
#include <readlight.h>
#include <depositcore.h>
#include <taskexecutor.h>
#include <gotox.h>
#include <gotoy.h>

#define SERVOMIN 500
#define SERVOMAX 2286

#define CDSMIN 0.0
#define CDSMAX 3.3

#define MIMIMUM_POWER 15

#define POWER_RATIO 1
#define DEGREE_RATIO 1

Robot robot;
TaskExecutor executor;

int main(void)
{
    RPS.InitializeTouchMenu();

    LCD.Clear();

    while (false)
    {
        robot.Update();
        LCD.Clear();
        LCD.WriteLine(robot.GetX());
        LCD.WriteLine(robot.GetY());
        LCD.WriteLine(robot.GetHeading());
        Sleep(.1);
    }

    /*Task* tasks[] = {
        new MoveServo(180),
        new WaitForTouch(),
        new WaitForLight(),
        new Drive(6, 23),
        new Orient(0),
        new ReadLight(),
        new Drive(14, 20),
        new Drive(20, 50),
        new Orient(320),
        new MoveServo(85),
        new DriveDistance(20),
        new DriveDistance(-15),
        new MoveServo(180),
        new Drive(20, 18),
        new DepositCore(),
        new Orient(90),
        new DriveDistance(10),
        new MoveServo(85),
        new DriveDistance(-10),
        new MoveServo(180),
        new Drive(9, 20),
        new Drive(5, 25),
        new End()};*/

    /*Task* tasks[] = {
        new MoveServo(180),
        new WaitForTouch(),
        new WaitForLight(),
        new DriveDistance(-10),
        new Orient(0),
        new DriveDistance(-3),
        new ReadLight(),
        new DriveDistance(-7),
        new Orient(90),
        new DriveDistance(-30),
        new Orient(320),
        new MoveServo(85),
        new DriveDistance(20),
        new DriveDistance(-15),
        new MoveServo(180),
        new Orient(90),
        new DriveDistance(30),
        new Orient(0),
        new DepositCore(),
        new Orient(90),
        new DriveDistance(10),
        new MoveServo(85),
        new DriveDistance(-10),
        new MoveServo(180),
        new Orient(0),
        new DriveDistance(5),
        new Orient(90),
        new DriveDistance(-10),
        new End()};*/

    Task* tasks[] = {
        new MoveServo(180),
        new WaitForTouch(),
        new WaitForLight(),
        new GoToY(18, 30),
        new GoToX(10, -30),
        new GoToX(11, 30),
        new ReadLight(),
        new GoToX(20, 30),
        new GoToY(40, -50),
        new GoToX(27, 30),
        new GoToY(45, 30),
        new Orient(315),
        new MoveServo(80),
        new DriveDistance(15),
        new Orient(315),
        new DriveDistance(25),
        new DriveDistance(-17),
        new MoveServo(180),
        new GoToY(40, 30),
        new GoToX(17, 30),
        new GoToY(23, 30),
        new GoToY(18, 30),
        new DepositCore(),
        new Orient(90),
        new DriveDistance(15),
        new MoveServo(85),
        new DriveDistance(-7),
        new MoveServo(180),
        new GoToX(28, 30),
        new GoToY(10, 30),
        new End()};


    Task* task = tasks[0];
    for (int task_number = 0; !task->isEnd(); task_number++)
    {
        task = tasks[task_number];

        executor.Execute(robot, task);

        Sleep(1.0);
    }

    return 0;
}
