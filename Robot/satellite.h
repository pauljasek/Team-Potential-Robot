#ifndef SATELLITE_H
#define SATELLITE_H

#include "task.h"
#include "drivedistance.h"
#include "drivetime.h"
#include <taskexecutor.h>
#include <gotox.h>
#include <gotoy.h>
#include <orient.h>
#include <moveservo.h>
#include <robot.h>

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

