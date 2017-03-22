/*
 * Includes for robot interface and task execution.
 */
#include <robot.h>
#include <taskexecutor.h>

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
Robot robot;
TaskExecutor executor;

/*
 * Completion of the course from start to finish.
 */
int main(void)
{
    /*
     * Allows the user to select the course that the robot is operating within.
     */
    RPS.InitializeTouchMenu();

    /*
     * Clears the screen.
     */
    LCD.Clear();

    /*
     * Initialize a list of pointers to individual task objects.
     * Contains instructions for completion of the course.
     */
    Task* tasks[] = {
        new MoveServo(180),
        new WaitForTouch("Touch to wait for light ..."),
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
    }

    return 0;
}
