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
     * Displays message to screen and waits for screen to be unpressed, pressed, and then pressed.
     */
    LCD.WriteLine(DisplayText);
    while (!LCD.Touch(&x, &y)) {Sleep(0.05);}
    while (LCD.Touch(&x, &y)) {Sleep(0.05);}
    while (!LCD.Touch(&x, &y)) {Sleep(0.05);}
}

bool WaitForTouch::Run(Robot& robot)
{
    // No looping action.
    return true;
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
