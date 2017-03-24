#ifndef DRIVETIME_H
#define DRIVETIME_H

#include "task.h"

class DriveTime : public Task
{
public:
    DriveTime(float);
    DriveTime(float, float);
    void Init(Robot&);
    bool Run(Robot&);
    void Finish(Robot&);
    bool isEnd();
private:
    float Time, Percent;
};

#endif // DRIVETIME_H

