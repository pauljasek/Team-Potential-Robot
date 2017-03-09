#ifndef DEPOSITCORE_H
#define DEPOSITCORE_H

#include "task.h"
#include "drive.h"

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
