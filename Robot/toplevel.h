#ifndef TOPLEVEL_H
#define TOPLEVEL_H

#include <FEHLCD.h>
#include <FEHMotor.h>
#include "task.h"
#include <math.h>
#include <taskexecutor.h>
#include <FEHUtility.h>
#include <orient.h>
#include <drivedistance.h>

class TopLevel : public Task
{
public:
    TopLevel();
    void Init(Robot& robot);
    bool Run(Robot& robot);
    void Finish(Robot& robot);
    bool isEnd();
};

#endif // TOPLEVEL_H
