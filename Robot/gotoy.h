#ifndef GOTOY_H
#define GOTOY_H

#include "task.h"
#include <FEHLCD.h>
#include <FEHMotor.h>
#include <math.h>
#include <orient.h>
#include <taskexecutor.h>

class GoToY : public Task
{
public:
    GoToY(float, float);
    GoToY(float, float, float);
    GoToY(float, float, float, bool);
    void Init(Robot& robot);
    bool Run(Robot& robot);
    void Finish(Robot& robot);
    bool isEnd();
private:
    float Y, Power, StartX, previous_power, previous_distance, Tolerance;
    bool positive;
    bool waited, ChangeOrientation;
};

#endif // GOTOY_H
