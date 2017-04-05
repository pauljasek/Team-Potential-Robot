#ifndef ORIENT_H
#define ORIENT_H

#include <FEHLCD.h>
#include <FEHMotor.h>
#include "task.h"
#include <math.h>

class Orient : public Task
{
public:
    Orient(float);
    Orient(float, bool);
    void Init(Robot& robot);
    bool Run(Robot& robot);
    void Finish(Robot& robot);
    bool isEnd();
private:
    float Orientation, previous_difference, previous_power;
    bool waited, Check;
};
#endif // ORIENT_H
