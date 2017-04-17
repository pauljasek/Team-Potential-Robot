#ifndef WAITFORTOUCH_H
#define WAITFORTOUCH_H

#include "task.h"
#include <FEHLCD.h>

using namespace std;

class WaitForTouch : public Task
{
public:
    WaitForTouch(char*);
    void Init(Robot&);
    bool Run(Robot&);
    void Finish(Robot&);
    bool isEnd();
private:
    bool touched;
    float x, y;
    char* DisplayText;
};

#endif // WAITFORTOUCH_H
