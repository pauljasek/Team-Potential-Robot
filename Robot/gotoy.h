#ifndef GOTOY_H
#define GOTOY_H

#include <FEHLCD.h>
#include <FEHMotor.h>
#include "task.h"

class GoToY : public Task
{
public:
    GoToY(float, float);
    void Init(Robot& robot);
    bool Run(Robot& robot);
    void Finish(Robot& robot);
    bool isEnd();
private:
    float Y, Power, StartX;
    bool positive;
};

#endif // GOTOY_H
