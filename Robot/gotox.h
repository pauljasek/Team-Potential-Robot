#ifndef GOTOX_H
#define GOTOX_H

#include "task.h"
#include <FEHLCD.h>
#include <FEHMotor.h>
#include <math.h>
#include <orient.h>
#include <taskexecutor.h>

class GoToX : public Task
{
public:
    GoToX(float, float);
    GoToX(float, float, float);
    GoToX(float, float, float, bool);
    void Init(Robot& robot);
    bool Run(Robot& robot);
    void Finish(Robot& robot);
    bool isEnd();
private:
    float X, Power, StartY, previous_power, previous_distance, Tolerance;
    bool positive;
    bool waited, ChangeOrientation;
};

#endif // GOTOX_H
