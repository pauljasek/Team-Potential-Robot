#ifndef DEPOSITCORE_H
#define DEPOSITCORE_H

#include "task.h"
#include "drive.h"
#include "drivedistance.h"
#include <taskexecutor.h>
#include <gotox.h>
#include <gotoy.h>

class DepositCore : public Task
{
public:
    DepositCore();
    void Init(Robot&);
    bool Run(Robot&);
    void Finish(Robot&);
    bool isEnd();
private:
    int STATE;
};

#endif // DEPOSITCORE_H
