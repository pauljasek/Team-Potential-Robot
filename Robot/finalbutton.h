#ifndef FINALBUTTON_H
#define FINALBUTTON_H

#include "task.h"
#include "drivedistance.h"
#include "drivetime.h"
#include <taskexecutor.h>
#include <gotox.h>
#include <gotoy.h>
#include <orient.h>

class FinalButton : public Task
{
public:
    FinalButton();
    void Init(Robot&);
    bool Run(Robot&);
    void Finish(Robot&);
    bool isEnd();
private:
    int STATE;
};

#endif // FINALBUTTON_H
