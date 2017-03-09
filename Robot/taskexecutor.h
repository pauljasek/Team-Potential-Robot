#ifndef TASKEXECUTOR_H
#define TASKEXECUTOR_H


#include <robot.h>
#include <task.h>
class TaskExecutor
{
public:
    TaskExecutor();
    void Execute(Robot&, Task*);
};

#endif // TASKEXECUTOR_H
