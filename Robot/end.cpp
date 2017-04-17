#include "end.h"

// Simply a task which tells the executing loop to stop executing tasks

End::End()
{
}
void End::Init(Robot& robot){}

bool End::Run(Robot& robot)
{
    return true;
}

void End::Finish(Robot& robot){}

bool End::isEnd()
{
    return true;
}
