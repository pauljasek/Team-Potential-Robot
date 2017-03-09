#ifndef GOTOX_H
#define GOTOX_H

#include <FEHLCD.h>
#include <FEHMotor.h>
#include "task.h"

class GoToX : public Task
{
public:
    GoToX(float, float);
    void Init(Robot& robot);
    bool Run(Robot& robot);
    void Finish(Robot& robot);
    bool isEnd();
private:
    float X, Power, StartY;
    bool positive;
};

#endif // GOTOX_H
