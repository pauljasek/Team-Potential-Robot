#ifndef TASK_H
#define TASK_H

#include <robot.h>

/*
 * Task interface.
 * Each task is required to implement the following functions which are used by the task executor class.
 */

class Task
{
public:
    /*
     * Runs once at the beginning of execution.
     */
    virtual void Init(Robot&) = 0;
    /*
     * Continuously runs until true is returned.
     */
    virtual bool Run(Robot&) = 0;
    /*
     * Runs once at the end of the task execution.
     */
    virtual void Finish(Robot&) = 0;
    /*
     * Returns true if it is the end task, otherwise returns false.
     */
    virtual bool isEnd() = 0;
};

#endif // TASK_H
