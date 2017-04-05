/*
 * Includes for robot interface and task execution.
 */
#include <robot.h>
#include <taskexecutor.h>
#include <FEHSD.h>

/*
 * Includes for task classes.
 */
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
#include <gotox.h>
#include <gotoy.h>
#include <drivetime.h>
#include <toplevel.h>
#include <finalbutton.h>
#include <satellite.h>

/*
 * Main Program for 2017 FEH Robot Competition
 *
 * C8: Team Potential
 *
 * Paul Jasek
 * Harrison Kearby
 * Joshua Rocheleau
 * Jack Rochester
 *
 */

/*
 * Initialize a robot object and an object for executing robot tasks.
 */
TaskExecutor executor;

/*
 * Completion of the course from start to finish.
 */
int main(void)
{
    /*for (int j = 0; j < 4; j++) {
        robot.Turn(45, 20);
        Sleep(3.0);
    }*/

    /*
     * Allows the user to select the course that the robot is operating within.
     */
    RPS.InitializeTouchMenu();

    /*
     * Clears the screen.
     */
    LCD.Clear();

    Robot robot;

        /*for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                float distance = 5 + j * 5;
                float power = 10 + i*10;

                Sleep(2.0);
                robot.Update();
                float start_x = robot.GetX();
                robot.DriveStraight(distance, power);
                Sleep(2.0);
                robot.Update();
                SD.Printf("%d, %d, %f, %f\n", robot.RightEncoder.Counts(), robot.LeftEncoder.Counts(), power, robot.GetX() - start_x);

                power *= -1;

                Sleep(2.0);
                robot.Update();
                start_x = robot.GetX();
                robot.DriveStraight(distance, power);
                Sleep(2.0);
                robot.Update();
                SD.Printf("%d, %d, %f, %f\n", robot.RightEncoder.Counts(), robot.LeftEncoder.Counts(), power, robot.GetX() - start_x);
            }
        }*/

    while (false)
    {
    robot.LeftEncoder.ResetCounts();
    robot.RightEncoder.ResetCounts();
    robot.SetLeftPercent(-45);
    robot.SetRightPercent(-45);
    //Sleep(1.0);
    float initial_time = TimeNow();
    while (TimeNow() < initial_time + 1)
    {
        LCD.Write(robot.LeftEncoder.Counts());
        LCD.Write(" ");
        LCD.WriteLine(robot.RightEncoder.Counts());

    }
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();

    Sleep(2.0);

    robot.SetLeftPercent(45);
    robot.SetRightPercent(45);
    Sleep(1.0);
    robot.RightMotor.Stop();
    robot.LeftMotor.Stop();

    Sleep(2.0);

    robot.DriveStraight(20, 25);

    Sleep(2.0);

    robot.DriveStraight(-20, 25);

    Sleep(2.0);
    }

    /*float last_x = 0;
    float last_time = TimeNow();
    while (true)
    {
        float x = RPS.X();
        if (x != last_x)
        {
            last_x = x;
            float time = TimeNow();
            LCD.Write(time - last_time);
            LCD.Write(" ");
            LCD.WriteLine(last_x);
            last_time = time;
        }
    }*/

    /*while (true)
    {
        robot.DriveFast(30);
        Sleep(3.0);
    }*/
    //robot.Turn(90,20);

    //robot.PIDDrive(20,30);

    /*
     * Initialize a list of pointers to individual task objects.
     * Contains instructions for completion of the course.
     */
    /*Task* tasks[] = {
        // Starting
        new MoveServo(180),
        new WaitForTouch("Touch to wait for light ..."),
        new WaitForLight(),
        // Read Light
        new GoToY(16, 25),
        new GoToX(7, -25),
        new ReadLight(),
        // Satellite Dish
        new GoToX(25, 25),
        new Orient(165),
        new DriveDistance(15, 20),
        new GoToX(18, -25),
        // Drive up ramp.
        new Orient(90),
        new DriveDistance(25, -45),
        // Pull lever.
        new GoToY(46, 25),
        new GoToY(44, 25),
        new Orient(180),
        new DriveTime(4, -25),
        new DriveDistance(15, 20),
        // Push Button
        new GoToX(26, 25),
        new Orient(90),
        new DriveTime(10,-30),
        new DriveDistance(18, 25),
        // Navigate to Core
        new GoToX(27, 25),
        new GoToY(47.5, 25),
        new Orient(318),
        new MoveServo(75),
        new DriveDistance(13,20),
        new Orient(318),
        new DriveTime(4, 20),
        // Extract core
        new DriveDistance(-20, 20),
        new MoveServo(180),
        // Drve downramp
        new GoToY(40, 25),
        new GoToX(17, 25),
        new GoToY(20, 25),
        // Deposit Core
        new DepositCore(),
        new Orient(90),
        new DriveTime(3, 15),
        new MoveServo(85),
        new DriveDistance(-7),
        new MoveServo(180),
        // Push final button
        new GoToY(15, 30),
        new GoToX(4, 25),
        new Orient(90),
        new DriveTime(10, -35),
        new End()};
    */

    Task* tasks[] = {
            // Starting
            new MoveServo(180),
            new WaitForTouch("Touch to wait for light ..."),
            new WaitForLight(),
            // Read Light
            //new DriveDistance(7.5, 30),
            //new GoToY(16, 45, 100, false),
            new DriveDistance(8, 45),
            new Orient(180),
            //new GoToX(16, 25),
            new ReadLight(),
            // Satellite Dish
            //new GoToX(25, 45, 2, false),
            //new Orient(170, false),
            //new DriveTime(2.5, 45),
            //new GoToX(19, -35, 1, false),
            new Satellite(),
            // Drive up ramp.
            new Orient(90, false),
            new DriveDistance(25, -45),
            // Pull lever.
            new DriveTime(1, 0),
            new GoToY(44.7, -15, .2, false),
            new Orient(180, false),
            new DriveTime(2.5, -16),
            new MoveServo(70),
            // Complete the Top Level
            new DriveDistance(3,40),
            new Orient(284),
            new DriveDistance(14, 40),
            new TopLevel(),
            new DriveDistance(-21, 45),
            new MoveServo(180),
            new MoveServo(180),
            new MoveServo(180),
            new Orient(90, false),
            new DriveTime(1, -45),
            new DriveTime(6, -25),
            new DriveDistance(19, 45),
            new DriveDistance(25, 25),
            //new GoToY(45, 40, 2),
            // Drve downramp
            //new Orient(50),
            //new GoToX(17, 30, 1, false),
            //new GoToY(18, 25, 1),
            //new Orient(90),
            //new DriveDistance(25, 25),
            // Deposit Core
            new DepositCore(),
            new Orient(90, false),
            new MoveServo(115),
            new DriveTime(1, 45),
            new DriveDistance(-5, 45),
            //new MoveServo(180),
            // Push final button
            //new GoToY(15, 30, 1),
            /*new GoToX(4, 25, 1),
            new Orient(90),
            new DriveTime(10, -45),*/
            new FinalButton(),
            new End()};

    /*
     * Iterates through and executes each task within the list.
     */
    Task* task = tasks[0];
    for (int task_number = 0; !task->isEnd(); task_number++)
    {
        /*
         * Selects the next task.
         */
        task = tasks[task_number];

        /*
         * Executes the task until completed.
         */
        executor.Execute(robot, task);

        robot.LogReport();
    }

    SD.CloseLog();

    return 0;
}
