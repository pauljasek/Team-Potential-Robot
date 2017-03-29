#define PI 3.14159265

/*
 * Conversion factors for driving specific distances and turning specific degrees.
 */
#define COUNTS_PER_INCH 33.7408479355
#define COUNTS_PER_DEGREE 2.09055555556

/*
 * Left and right wheel power multipliers.
 */
#define RM -1
#define LM 1

/*
 * Encoder count adjustmnet factors.
 */
#define LCM 1.01
#define RCM 1

/*
 * Motor power multiplier to correct when in the case of a count discrepency.
 */
#define CORRECTION_MULTIPLIER .70

/*
 * Servo calibration constants.
 */
#define SERVOMIN 500
#define SERVOMAX 2286

#include "robot.h"

Robot::Robot()
    : RightMotor(FEHMotor::Motor1, 12.0),
      LeftMotor(FEHMotor::Motor0, 12.0),
      Servo(FEHServo::Servo5),
      RightEncoder(FEHIO::P0_0),
      LeftEncoder(FEHIO::P0_2),
      RightOptosensor(FEHIO::P1_1),
      MiddleOptosensor(FEHIO::P1_2),
      LeftOptosensor(FEHIO::P1_4),
      CdSCell(FEHIO::P1_6),
      SkidBumper(FEHIO::P2_0),
      BLBumper(FEHIO::P2_2),
      BRBumper(FEHIO::P2_4),
      FLBumper(FEHIO::P2_6),
      ArmBumper(FEHIO::P3_0),
      SideBumper(FEHIO::P3_2)
{
    /*
     * Set the default value of the color of the bin indicator light.
     */
    RedLight = true;
}

/*
 * Set the right motor power level.
 */
void Robot::SetRightPercent(float percent)
{
    RightMotor.SetPercent(RM * percent);
}

/*
 * Set the left motor power level.
 */
void Robot::SetLeftPercent(float percent)
{
    LeftMotor.SetPercent(LM * percent);
}

/*
 * Basic functionality for driving straight a certain number of inches at a given power level.
 */
void Robot::DriveStraight(float inches, float percent)
{
    /*
     * Account for negative values.
     */
    percent *= -1;
    if (inches < 0)
    {
        inches *= -1;
        percent *= -1;
    }

    /*
     * Reset encoder counts.
     */
    RightEncoder.ResetCounts();
    LeftEncoder.ResetCounts();

    /*
     * Calculate the number of counts to drive a given distance.
     */
    int counts = COUNTS_PER_INCH * inches;

    /*
     * Create variables to store number of counts.
     */
    int r_counts = RightEncoder.Counts() * RCM;
    int l_counts = LeftEncoder.Counts() * LCM;

    /*
     * While average of counts is less than calculated counts.
     */
    while (r_counts + l_counts < counts * 2)
    {
        /*
         * Update count variables.
         */
        r_counts = RightEncoder.Counts() * RCM;
        l_counts = LeftEncoder.Counts() * LCM;

        /*
         * Calculate corrected percentages.
         */
        float r_percent = percent;
        float l_percent = percent;

        if (r_counts < l_counts)
        {
            l_percent *= CORRECTION_MULTIPLIER;
        }
        else if (l_counts < r_counts)
        {
            r_percent *= CORRECTION_MULTIPLIER;
        }

        /*
         * Apply motor percentages.
         */
        RightMotor.SetPercent(RM * r_percent);
        LeftMotor.SetPercent(LM * l_percent);
    }
    /*
     * Stop the motors.
     */
    RightMotor.Stop();
    LeftMotor.Stop();
}

/*
 * Basic functionality for driving straight a certain amount of time at a given power level.
 */
void Robot::DriveTime(float time, float percent)
{
    /*
     * Account for negative values.
     */
    percent *= -1;

    /*
     * Reset encoder counts.
     */
    RightEncoder.ResetCounts();
    LeftEncoder.ResetCounts();

    /*
     * Create variables to store number of counts.
     */
    int r_counts = RightEncoder.Counts() * RCM;
    int l_counts = LeftEncoder.Counts() * LCM;

    float t = 0;

    /*
     * While average of counts is less than calculated counts.
     */
    while (t < time * 10)
    {
        /*
         * Update count variables.
         */
        r_counts = RightEncoder.Counts() * RCM;
        l_counts = LeftEncoder.Counts() * LCM;

        /*
         * Calculate corrected percentages.
         */
        float r_percent = percent;
        float l_percent = percent;

        if (r_counts < l_counts)
        {
            l_percent *= CORRECTION_MULTIPLIER;
        }
        else if (l_counts < r_counts)
        {
            r_percent *= CORRECTION_MULTIPLIER;
        }

        /*
         * Apply motor percentages.
         */
        RightMotor.SetPercent(RM * r_percent);
        LeftMotor.SetPercent(LM * l_percent);

        t++;
        Sleep(.1);
    }
    /*
     * Stop the motors.
     */
    RightMotor.Stop();
    LeftMotor.Stop();
}



/*
 * Turn a specific number of degrees at a given power level.
 */
void Robot::Turn(float degrees, float percent)
{
    /*
     * Account for negative inputs.
     */
    if (degrees < 0)
    {
        degrees *= -1;
        percent *= -1;
    }

    /*
     * Reset encoder counts.
     */
    RightEncoder.ResetCounts();
    LeftEncoder.ResetCounts();

    /*
     * Calculate counts to turn given amount.
     */
    int counts = COUNTS_PER_DEGREE * degrees;

    /*
     * Create variables for encoder counts.
     */
    int r_counts = RightEncoder.Counts() * RCM;
    int l_counts = LeftEncoder.Counts() * LCM;

    /*
     * While average of counts is less than calculated counts.
     */
    while (r_counts + l_counts < counts * 2)
    {
        /*
         * Update count variables.
         */
        r_counts = RightEncoder.Counts() * RCM;
        l_counts = LeftEncoder.Counts() * LCM;

        /*
         * Calculate corrected percentages.
         */
        float r_percent = percent;
        float l_percent = percent;

        if (r_counts < l_counts)
        {
            l_percent *= CORRECTION_MULTIPLIER;
        }
        else if (l_counts < r_counts)
        {
            r_percent *= CORRECTION_MULTIPLIER;
        }

        /*
         * Set motor power levels.
         */
        RightMotor.SetPercent(RM * r_percent);
        LeftMotor.SetPercent(-LM * l_percent);
    }
    /*
     * Stop motors.
     */
    RightMotor.Stop();
    LeftMotor.Stop();
}

/*
 * Return current understanding of bin light color.
 */
bool Robot::GetRedLight()
{
    return RedLight;
}

/*
 * Change current understanding of bin light color.
 */
void Robot::SetRedLight(bool red_light)
{
    RedLight = red_light;
}

/*
 * Return current calculated x position.
 */
float Robot::GetX()
{
    return X;
}

/*
 * Return current calculated y position.
 */
float Robot::GetY()
{
    return Y;
}

/*
 * Return current calculated heading.
 */
float Robot::GetHeading()
{
    return Heading;
}

/*
 * Return CdS cell value.
 */
float Robot::GetCdSCellValue()
{
    return CdSCellVallue;
}

/*
 * Update state variables from sensory inputs.
 */
void Robot::Update()
{
    X = RPS.X();
    Y = RPS.Y();
    Heading = RPS.Heading();
    float radians = RPS.Heading() * PI/180.0;
    float dx = cos(radians);
    float dy = sin(radians);
    X -= 6.5 * dx;
    Y -= 6.5 * dy;
    CdSCellVallue = CdSCell.Value();
}
