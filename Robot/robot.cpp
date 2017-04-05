#define PI 3.14159265

/*
 * Conversion factors for driving specific distances and turning specific degrees.
 */
#define COUNTS_PER_INCH 34.5 //33.7408479355
#define COUNTS_PER_DEGREE 2.09055555556
#define REGRESSION1 -1.6912
#define REGRESSION2 19.354


/*
 * Left and right wheel power multipliers.
 */
#define RM -1
#define LM 1.060 //1.060 //1.25

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

#include "robot.h"

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

    /*if (inches > 3)
    {
        inches -= 0.04 * abs(percent) - 0.4065;
    }*/

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

void Robot::DriveArc(float inches, float percent, float l_ratio, float r_ratio)
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
    int r_counts = RightEncoder.Counts() * RCM * r_ratio;
    int l_counts = LeftEncoder.Counts() * LCM * l_ratio;

    /*
     * While average of counts is less than calculated counts.
     */
    while (r_counts + l_counts < counts * 2)
    {
        /*
         * Update count variables.
         */
        r_counts = RightEncoder.Counts() * RCM * r_ratio;
        l_counts = LeftEncoder.Counts() * LCM * l_ratio;

        /*
         * Calculate corrected percentages.
         */
        float r_percent = percent;
        float l_percent = percent;

        if (r_counts < l_counts)
        {
            l_percent *= CURVE_MULTIPLIER;
        }
        else if (l_counts < r_counts)
        {
            r_percent *= CURVE_MULTIPLIER;
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


float Robot::Accelerate(float percent)
{
    RightEncoder.ResetCounts();
    LeftEncoder.ResetCounts();

    /*float PowerR = 0.1;
    SetRightPercent(-percent);

    while(PowerR < 1.0)
    {
        Sleep(0.008);
        PowerR += 0.05;
        SetLeftPercent(-PowerR*percent);
    }
    SetLeftPercent(-percent);*/

    float r_power = 0;
    float l_power = 0;
    int mult = -percent/abs(percent);

    LCD.Clear(RED);

    SetRightPercent(r_power * mult);
    SetLeftPercent(l_power * mult);

    while (r_power < abs(percent) && l_power < abs(percent))
    {
        Sleep(.001);
        SetRightPercent(r_power * mult);
        SetLeftPercent(l_power * mult);

        if (RightEncoder.Counts() < LeftEncoder.Counts())
        {
            r_power += .2;
            if (r_power > abs(percent))
            {
                r_power = abs(percent);
            }
        }
        else
        {
            l_power += .2;
            if (l_power > abs(percent))
            {
                l_power = abs(percent);
            }
        }
    }

    LCD.Clear(GREEN);

    LCD.WriteLine(l_power);
    LCD.WriteLine(r_power);


    return (RightEncoder.Counts() + LeftEncoder.Counts())/2.0;
}

void Robot::DriveFast(float inches)
{
    /*
     * Calculate the number of counts to drive a given distance.
     */
    inches -= 2;
    int counts = COUNTS_PER_INCH * abs(inches);

    float percent = 50;

    if (inches >= 0)
    {
        counts -= Accelerate(percent);
        DriveStraight(counts/COUNTS_PER_INCH, percent);
    }
    else
    {
        counts -= Accelerate(-percent);
        DriveStraight(counts/COUNTS_PER_INCH, -percent);
    }
}

/*
 * Basic functionality for driving straight a certain number of inches at a given power level.
 */
float Robot::DriveStraightReadLight(float inches, float percent)
{
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

void Robot::PIDDrive(float distance, float velocity)
{
    int negative = 1;
    if (velocity < 0)
    {
        velocity *= -1;
        negative *= -1;
    }

    if (distance < 0)
    {
        distance *= -1;
        negative *= -1;
    }

    float P = 1.5; //0.75;
    float I = 0.001; //0.05;
    float D = 0.15; //0.25;

    float r_errorSum = 0;
    float l_errorSum = 0;

    float last_time = TimeNow();
    RightEncoder.ResetCounts();
    LeftEncoder.ResetCounts();

    float pr_counts = 0;
    float pl_counts = 0;
    float r_counts = 0;
    float l_counts = 0;

    float r_power = 0;
    float l_power = 0;

    float r_previous_error = 0;
    float l_previous_error = 0;

    float total_counts = distance * COUNTS_PER_INCH * 2;

    float target_velocity = 2;
    if (target_velocity > velocity)
    {
        target_velocity = velocity;
    }

    float current_distance = 0;

    float ACCELERATION = 20;

    float DECEL_POINT = .75;
    float DECELERATION = ACCELERATION;

    float MIN_VELOCITY = 3;

    //Sleep(.05);

    //while (r_counts + l_counts < total_counts)
    while (current_distance < distance)
    {
        Sleep(.05);
        r_counts = RightEncoder.Counts() * RCM;
        l_counts = LeftEncoder.Counts() * LCM;

        float delta_r_counts = r_counts - pr_counts;
        float delta_l_counts = l_counts - pl_counts;

        float current_time = TimeNow();
        float delta_time = current_time - last_time;
        last_time = current_time;

        if (delta_time < .001)
        {
            delta_time = .001;
        }

        float r_velocity = (delta_r_counts/delta_time)/COUNTS_PER_INCH;
        float l_velocity = (delta_l_counts/delta_time)/COUNTS_PER_INCH;

        if (current_distance < distance * DECEL_POINT)
        {
            target_velocity = sqrt(2*current_distance*ACCELERATION);
        }
        else
        {
            target_velocity = sqrt(2*(distance-current_distance)*DECELERATION);
        }
        if (target_velocity > velocity)
        {
            target_velocity = velocity;
        }
        if (target_velocity < MIN_VELOCITY)
        {
            target_velocity = MIN_VELOCITY;
        }

        LCD.WriteLine(target_velocity);

        /*if (r_velocity + l_velocity > target_velocity * 2 - .5)
        {
            target_velocity += 1;
            if (target_velocity > velocity)
            {
                target_velocity = velocity;
            }
            LCD.WriteLine(target_velocity);
        }*/

        float r_error = target_velocity - r_velocity;
        float l_error = target_velocity - l_velocity;

        r_errorSum += r_error;
        l_errorSum += l_error;

        //LCD.Write(r_error);
        //LCD.Write(" ");
        //LCD.WriteLine(l_error);

        float r_PTerm = r_error * P;
        float r_ITerm = r_errorSum * I;
        float r_DTerm = (r_error - r_previous_error) * D;

        float l_PTerm = l_error * P;
        float l_ITerm = l_errorSum * I;
        float l_DTerm = (l_error - l_previous_error) * D;

        r_power += r_PTerm + r_ITerm + r_DTerm;
        l_power += l_PTerm + l_ITerm + l_DTerm;

        pr_counts = r_counts;
        pl_counts = l_counts;

        r_previous_error = r_error;
        l_previous_error = l_error;

        SetRightPercent(-r_power * negative);
        SetLeftPercent(-l_power * negative);

        current_distance = ((r_counts + l_counts)/2.0)/COUNTS_PER_INCH;
    }

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

void Robot::LogReport()
{
    char logRow[] = "%f, %d, %f, %f, %f, %f, %c\n";

    // Write row out to the log
    SD.Printf(logRow,
              TimeNow(), ArmBumper.Value(), CdSCellVallue, X, Y, Heading, RegionLetter);
}
