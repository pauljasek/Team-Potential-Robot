#ifndef ROBOT_H
#define ROBOT_H

#include <FEHMotor.h>
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHRPS.h>
#include <worldstate.h>
#include <math.h>

class Robot
{
public:
    Robot();
    void SetRightPercent(float);
    void SetLeftPercent(float);
    void DriveStraight(float, float);
    void Turn(float, float);
    float GetX();
    float GetY();
    float GetHeading();
    float GetCdSCellValue();
    void SetRedLight(bool);
    bool GetRedLight();
    void Update();
    FEHMotor RightMotor;
    FEHMotor LeftMotor;
    FEHServo Servo;
    DigitalEncoder RightEncoder;
    DigitalEncoder LeftEncoder;
    AnalogInputPin CdSCell;
    AnalogInputPin LeftOptosensor;
    AnalogInputPin MiddleOptosensor;
    AnalogInputPin RightOptosensor;
    DigitalInputPin SkidBumper;
    DigitalInputPin BLBumper;
    DigitalInputPin BRBumper;
    DigitalInputPin FLBumper;
    DigitalInputPin ArmBumper;
    DigitalInputPin SideBumper;
private:
    float X;
    float Y;
    float Heading;
    float CdSCellVallue;
    bool RedLight;
};

#endif // ROBOT_H
