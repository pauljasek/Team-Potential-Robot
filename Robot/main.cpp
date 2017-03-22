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
        LCD.WriteLine(robot.RightEncoder.Counts());
        LCD.WriteLine(robot.LeftEncoder.Counts());
        Sleep(.1);
    }

    /*
    Task* tasks[] = {
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

    /*Task* tasks[] = {
        new MoveServo(180),
        new WaitForTouch(),
        new WaitForLight(),
        new GoToY(16, 25),
        new GoToX(10, -25),
        new DriveDistance(4),
        new ReadLight(),
        new GoToX(18, 25),
        new GoToY(41, -45),
        new GoToX(27, 25),
        new GoToY(48.2, 25),
        new Orient(318),
        new MoveServo(75),
        new DriveDistance(13),
        new Orient(318),
        new DriveDistance(25),
        new DriveDistance(-13, 20),
        new MoveServo(180),
        new GoToY(40, 25),
        new GoToX(17, 25),
        new GoToY(20, 25),
        new GoToY(18, 25),
        new DepositCore(),
        new Orient(90),
        new DriveDistance(15),
        new MoveServo(85),
        new DriveDistance(-7),
        new MoveServo(180),
        new GoToX(28, 25),
        new GoToY(10, 25),
        new End()};*/

    Task* tasks[] = {
        new MoveServo(180),
        new WaitForTouch(),
        new WaitForLight(),
        new GoToY(16, 25),
        new GoToX(10, -25),
        new DriveDistance(4, 20),
        new ReadLight(),
        new GoToX(25, 25),
        new GoToY(14.5, 25),
        new Orient(170),
        new DriveDistance(15, 35),
        new GoToX(18, -25),
        new GoToY(15, 25),
        new GoToX(18, 25),
        new GoToY(41, -45),
        new GoToX(27, 25),
        new Orient(90),
        new DriveDistance(-40, 45),
        new DriveDistance(18, 20),
        new GoToX(27, 25),
        new GoToY(49.2, 25),
        new Orient(318),
        new MoveServo(75),
        new DriveDistance(13),
        new Orient(318),
        new DriveDistance(25),
        new DriveDistance(-20, 20),
        new MoveServo(180),
        new GoToY(42, 25),
        new GoToX(17, 25),
        new Orient(180),
        new DriveDistance(-15, 30),
        new DriveDistance(15, 20),
        new GoToY(40, 25),
        new GoToX(17, 25),
        new GoToY(20, 25),
        new DepositCore(),
        new Orient(90),
        new DriveDistance(15),
        new MoveServo(85),
        new DriveDistance(-7),
        new MoveServo(180),
        new GoToY(15, 30),
        new GoToX(4, 25),
        new Orient(90),
        new DriveDistance(-20, 35),
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
