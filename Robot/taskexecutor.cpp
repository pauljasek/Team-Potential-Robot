#include "taskexecutor.h"

#define DELAY_BETWEEN_TASKS 0 //0.2

TaskExecutor::TaskExecutor() {}

/*
 * Method to execute tasks.
 */
void TaskExecutor::Execute(Robot& robot, Task* task)
{
    /*
     * Update robot state based on sensors.
     */
    robot.Update();

    /*
     * Call the task initialization function.
     */
    task->Init(robot);

    /*
     * Continuously update the robot state and run the task, until completion.
     */
    robot.Update();
    while (!task->Run(robot))
    {
        robot.Update();
    }

    /*
     * Update the robot state and call the task finish function.
     */
    robot.Update();
    task->Finish(robot);

    /*
     * Wait between tasks.
     */
    Sleep(DELAY_BETWEEN_TASKS);
}
