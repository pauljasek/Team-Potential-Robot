#include "taskexecutor.h"

TaskExecutor::TaskExecutor()
{

}

void TaskExecutor::Execute(Robot& robot, Task* task)
{
    robot.Update();
    task->Init(robot);

    robot.Update();
    while (!task->Run(robot))
    {
        robot.Update();
    }

    robot.Update();
    task->Finish(robot);
}
