#ifndef SATELLITE_H
#define SATELLITE_H

#include "task.h"

class Satellite : public Task
{
public:
    Satellite();
    void Init(Robot&);
    bool Run(Robot&);
    void Finish(Robot&);
    bool isEnd();
};

#endif // SATELLITE_H

