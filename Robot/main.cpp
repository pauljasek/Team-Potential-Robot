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
            new GoToY(16, 30, .2, false),
            new Orient(180),
            //new GoToX(16, 25),
            new ReadLight(),
            // Satellite Dish
            new GoToX(25, 25, 2, false),
            new Orient(157),
            new DriveTime(2.5, 30),
            new GoToX(19, -35, 1, false),
            // Drive up ramp.
            new Orient(90),
            new DriveDistance(25, -43),
            // Pull lever.
            new DriveTime(.5, 0),
            new GoToY(45.25, -16, .2, false),
            new Orient(180),
            new DriveTime(2.5, -16),
            new MoveServo(70),
            // Complete the Top Level
            new DriveDistance(3,25),
            new Orient(284),
            new DriveDistance(13.7, 30),
            new TopLevel(),
            new DriveDistance(-19, 30),
            new MoveServo(180),
            new MoveServo(180),
            new MoveServo(180),
            new Orient(90),
            new DriveTime(7, -25),
            new DriveDistance(2, 30),
            //new GoToY(45, 40, 2),
            // Drve downramp
            new Orient(70),
            new GoToX(17, 30, 1, false),
            //new GoToY(18, 25, 1),
            new Orient(90),
            new DriveDistance(25, 25),
            // Deposit Core
            new DepositCore(),
            new Orient(90),
            new DriveTime(2, 20),
            new MoveServo(70),
            new DriveTime(.5, 0),
            new DriveDistance(-5, 50),
            new MoveServo(180),
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
