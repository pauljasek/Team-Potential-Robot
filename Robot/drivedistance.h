#ifndef DRIVEDISTANCE_H
#define DRIVEDISTANCE_H

#include "task.h"

class DriveDistance : public Task
{
public:
    DriveDistance(float);
    DriveDistance(float, float);
    void Init(Robot&);
    bool Run(Robot&);
    void Finish(Robot&);
    bool isEnd();
private:
    float Distance, Percent;
};

#endif // DRIVEDISTANCE_H
