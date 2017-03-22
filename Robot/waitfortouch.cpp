#include "waitfortouch.h"

using namespace std;

/*
 * Waits for LCD screen to be touched.
 */

WaitForTouch::WaitForTouch(char* s)
{
    /*
     * Initializes variables.
     */
    touched = false;
    DisplayText = s;
}

void WaitForTouch::Init(Robot& robot)
{
    /*
     * Displays message to screen.
     */
    LCD.WriteLine(DisplayText);
}

bool WaitForTouch::Run(Robot& robot)
{
    /*
     * Waits for touch and release.
     */
    if (touched)
    {
        if (!LCD.Touch(&x, &y))
        {
            return true;
        }
    }
    else
    {
        if (LCD.Touch(&x, &y))
        {
            touched = true;
        }
    }
    return false;
}

void WaitForTouch::Finish(Robot& robot)
{
    /*
     * Displays completion notification.
     */
    LCD.WriteLine("Touched.");
}

bool WaitForTouch::isEnd()
{
    return false;
}
