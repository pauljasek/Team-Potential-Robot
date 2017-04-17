#include "robot.h"

/*
 * Value of pi.
 */
#define PI 3.14159265

/*
 * Conversion factors for driving specific distances and turning specific degrees.
 */
#define COUNTS_PER_INCH 34.5
#define COUNTS_PER_DEGREE 2.09055555556

/*
 * Regressional constants used in calculating more accurate drives and turns
 */
#define REGRESSION1 -1.6912
#define REGRESSION2 19.354
#define TURNREG1 2.1165
#define TURNREG2 -23.336

/*
 * Left and right wheel power multipliers.
 */
#define RM -1
#define LM 1.060

/*
 * Encoder count adjustmnet factors.
 */
#define LCM 1.01
#define RCM 1

/*
 * Motor power multiplier to correct when in the case of a count discrepency.
 */
#define CORRECTION_MULTIPLIER 0.75
#define CURVE_MULTIPLIER 0.6

/*
 * Servo calibration constants.
 */
#define SERVOMIN 500
#define SERVOMAX 2286

Robot::Robot()
    : RightMotor(FEHMotor::Motor1, 12.0),
      LeftMotor(FEHMotor::Motor0, 12.0),
      Servo(FEHServo::Servo5),
      RightEncoder(FEHIO::P0_6),
      LeftEncoder(FEHIO::P0_7),
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

    RegionLetter = RPS.CurrentRegionLetter();

    SD.OpenLog();

    SD.Printf("Time, Arm Bumper Value, CdS Cell Value, X, Y, Heading, Region\n");
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
    float offset = REGRESSION1*abs(percent) + REGRESSION2;
    if (offset > 0)
    {
        offset = 0;
    }
    int counts = COUNTS_PER_INCH * inches + offset;
    if (counts < 5)
    {
        counts = 5;
    }

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
 * Drives straight and returns the minimum CdS Cell value read during the drive
 */
float Robot::DriveStraightReadLight(float inches, float percent)
{
    /*
     * Sets the initial minimum value to the current CdS Cell value.
     */
    float minLightValue = CdSCell.Value();

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
        // Updates the minimum CdS Cell Value
        float cds_value = CdSCell.Value();
        if (cds_value < minLightValue)
        {
            minLightValue = cds_value;
        }

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

    /*
     * Returns the minimum CdS Cell value.
     */
    return minLightValue;
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

    /*
     * Time counter
     */
    float t = 0;

    /*
     * While the time counter is less than the desired time counter value
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

        /*
         * Increments the time counter
         */
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
     * Calculate counts to turn given amount, using a linear regression on collected data
     */
    float counts = degrees * TURNREG1 + TURNREG2;
    if (counts < 1)
    {
        counts = 1;
    }

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

void Robot::WaitForRPS()
{
    /*
     * Variables for previous RPS values
     */
    float px = RPS.X();
    float py = RPS.Y();
    float ph = RPS.Heading();

    /*
     * Maximum and minimum end times
     */
    float end_time = TimeNow() + 1.5;
    float diff_time = TimeNow() + .1;

    /*
     * While the current time is less than the time out time and the minimum end time
     */
    while (TimeNow() < end_time && TimeNow() < diff_time)
    {
        /*
         * Read the new RPS values
         */
        float x = RPS.X();
        float y = RPS.Y();
        float h = RPS.Heading();

        /*
         * If the RPS values are different from the previous values by .1 or in the RPS zone,
         * the RPS values are not stable, so increase the minimum end time.
         */
        if (abs(x - px) > .1 || abs(y - py) > .1 || abs(h - ph) > .1 || x == -1)
        {
            diff_time = TimeNow() + .08;
        }

        /*
         * Update the previous RPS values
         */
        px = x;
        py = y;
        ph = h;
    }
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
    return CdSCellValue;
}

/*
 * Update state variables from sensory inputs.
 */
void Robot::Update()
{
    // RPS values
    X = RPS.X();
    Y = RPS.Y();
    Heading = RPS.Heading();
    // Translates coordinates over the center of the axel
    float radians = RPS.Heading() * PI/180.0;
    float dx = cos(radians);
    float dy = sin(radians);
    X -= 6.5 * dx;
    Y -= 6.5 * dy;

    // CdS Cell value
    CdSCellValue = CdSCell.Value();
}

void Robot::LogReport()
{
    return;
    char logRow[] = "%f, %d, %f, %f, %f, %f, %c\n";

    // Write row out to the log
    SD.Printf(logRow,
             TimeNow(), ArmBumper.Value(), CdSCellValue, X, Y, Heading, RegionLetter);
}
