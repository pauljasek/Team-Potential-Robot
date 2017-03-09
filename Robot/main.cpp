<<<<<<< HEAD
#include <FEHUtility.h>
#include <FEHLCD.h>
#include <FEHSD.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHIO.h>
#include <FEHRPS.h>

=======
#include <robot.h>
>>>>>>> paul
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

#include "worldstate.h"

using namespace std;

#define SERVOMIN 500
#define SERVOMAX 2286

#define CDSMIN 0.0
#define CDSMAX 3.3

#define MIMIMUM_POWER 15

<<<<<<< HEAD
#define POWER_RATIO 1.4
#define DEGREE_RATIO 1.02

int commands[] = {WAIT_FOR_LIGHT};

FEHMotor right_motor(FEHMotor::Motor0, 12.0);
FEHMotor left_motor(FEHMotor::Motor1, 12.0);

FEHServo servo(FEHServo::Servo0);

DigitalInputPin front_right_bumper(FEHIO::P1_0);
DigitalInputPin front_left_bumper(FEHIO::P1_1);
DigitalInputPin back_right_bumper(FEHIO::P1_2);
DigitalInputPin back_left_bumper(FEHIO::P1_3);

DigitalEncoder right_encoder(FEHIO::P0_2);
DigitalEncoder left_encoder(FEHIO::P0_3);
=======
#define POWER_RATIO 1
#define DEGREE_RATIO 1
>>>>>>> paul

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

<<<<<<< HEAD
    right_motor.Stop();
    left_motor.Stop();
}


DigitalInputPin SideBumper(FEHIO::P1_4);
DigitalInputPin ArmBumper(FEHIO::P1_5);

int main(void)
{
    int adsadasdasdads;

    LCD.SetBackgroundColor(BLACK);
    LCD.SetFontColor(WHITE);

    LCD.WriteLine("WORLD STATE REPORTER TEST");
    LCD.WriteLine("Creating WorldState object...");
    WorldState ws(right_encoder, left_encoder, front_right_bumper, front_left_bumper, back_right_bumper, back_left_bumper, SideBumper, ArmBumper, cds_cell);

    LCD.WriteLine("Running startup selfcheck...");
    bool checkResult = ws.SelfCheck(0, 0, true, true, true, true, true, true, 0.0, 3.3);

    if (checkResult) {
        LCD.WriteLine("Selfcheck passed!");
        Sleep(2000);
    } else {
        LCD.WriteLine("Selfcheck failed!");
        Sleep(2000);
    }

    float x_pos, y_pos;

    while (!LCD.Touch(&x_pos, &y_pos)) {
        ws.LogReport(true);
        Sleep(100);
        LCD.Clear();
    }

    LCD.WriteLine("Running shutdown selfcheck");
    checkResult = ws.SelfCheck(0, 0, true, true, true, true, true, true, 0.0, 3.3);

    if (checkResult) {
        LCD.WriteLine("Selfcheck passed!");
        Sleep(2000);
    } else {
        LCD.WriteLine("Selfcheck failed!");
        Sleep(2000);
    }

    LCD.WriteLine("Closing log...");
    SD.CloseLog();
    LCD.WriteLine("Log closed");

=======
        executor.Execute(robot, task);

        Sleep(1.0);
    }

>>>>>>> paul
    return 0;
}


