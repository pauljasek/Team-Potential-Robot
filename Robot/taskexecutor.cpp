#include "taskexecutor.h"

TaskExecutor::TaskExecutor() {}

/*
 * Method to execute tasks.
 */
void TaskExecutor::Execute(Robot& robot, Task* task)
{
    /*
     * Call the task initialization function.
     */
    task->Init(robot);

    /*
     * Continuously runs the task until true is returned.
     */
    while (!task->Run(robot));

    /*
     * Calls the task finish function.
     */
    task->Finish(robot);
}
