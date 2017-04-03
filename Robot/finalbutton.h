#ifndef FINALBUTTON_H
#define FINALBUTTON_H

#include "task.h"

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
