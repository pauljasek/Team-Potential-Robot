/*
 * FEH ROBOT COMPETITION 2017 FINAL PROGRAM
 * C8: Team Potential
 *
 * Members:
 * Paul Jasek
 * Harrison Kearby
 * Joshua Rocheleau
 * Jack Rochester
 */

/*
 * Includes for robot interface and task execution.
 */
#include <robot.h>
#include <taskexecutor.h>
#include <FEHSD.h>
#include <FEHBattery.h>

/*
 * Includes for task classes.
 */
#include <task.h>
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
    /*
     * Allows the user to select the course that the robot is operating within.
     */
    RPS.InitializeTouchMenu();

    /*
     * Clears the screen.
     */
    LCD.Clear();

    /*
     * Displays the batter voltage and RPS location to the tester.
     */
    LCD.Write("Voltage: ");
    LCD.WriteLine(Battery.Voltage());

    LCD.Write("X: ");
    LCD.WriteLine(RPS.X());

    LCD.Write("Y: ");
    LCD.WriteLine(RPS.Y());

    /*
     * Initializes the robot object.
     */
    Robot robot;

    /*
     * Creates an array of task objects that the program will execute in order.
     */
    Task* tasks[] = {
            // Starting configuration
            new MoveServo(180),
            new WaitForTouch("Random Touch."),
            new WaitForTouch("Touch to wait for light ..."),
            new WaitForLight(),
            // Line up to read the bin light
            new GoToY(20.3, -20, .1, false),
            new Orient(179),
            // Drive over the bin light and read its value
            new ReadLight(),
            // Drive to the satellite dish corner
            new Orient(181),
            new GoToX(25.2, 30, .1, false),
            // Drive into the corner at a calculated angle
            new Satellite(),
            // Drive backwards to rotate the satellite.
            new DriveTime(1.7, 50),
            // Position robot to drive up the ramp
            new GoToX(19.6, -35, .2, true),
            new Orient(95),
            // Drive up ramp
            new DriveDistance(26, -45),
            // Wait to ensure that the RPS coordinates are stable
            new DriveTime(.6, 0),
            // Position robot to pull lever
            new GoToY(43.5, -20, .1),
            new Orient(180),
            new DriveTime(2.5, -16),
            // Drop servo arm to extract core
            new MoveServo(70),
            // Pull the lever by driving backwards
            new DriveDistance(2.5, 25),
            // Position robot to extract the core
            new Orient(288),
            new DriveDistance(17.25, 30),
            // Extract the core
            new TopLevel(),
            new DriveDistance(-3, 25),
            // Drive backwards and position to press the button
            new DriveDistance(-10, 45),
            new GoToX(24, -35, .2, false),
            // Move servo arm to upward position
            new MoveServo(180),
            // Change orietation and drive to button and press for 6 seconds
            new Orient(90, true),
            new DriveTime(1, -40),
            new DriveTime(6, -25),
            // Position robot at edge of ramp
            new DriveDistance(19, 45),
            // Drive down the ramp at an angle
            new Orient(80),
            new DriveDistance(25, 45),
            // Drive to the correct bin to deposit the core
            new DepositCore(),
            // Orient the robot towards the bin
            new Orient(90),
            // Move the servo arm at an angle
            new MoveServo(107),
            // Drive forward to knock out the core sample with the pins in the servo arm
            new DriveTime(1, 40),
            // Drive backwards away from the bin
            new DriveDistance(-5, 40),
            // Push final button depending on bin position
            new FinalButton(),
            // Notifies the executing loop that it has reached the end of the task execution list
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

        /*
         * Logs a report of the robots current state to the SD card.
         */
        robot.LogReport();
    }

    /*
     * Closes any SD card log file that may have been opened throughout the run.
     */
    SD.CloseLog();

    return 0;
}
