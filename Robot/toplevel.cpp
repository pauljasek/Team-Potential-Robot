#include "toplevel.h"

#define PERCENT 30          // left motor power
#define TURN_PERCENT 20     // motor power used when turning
#define LOWPERCENT   15     // defaut motor speed for line follow
#define HIGHPERCENT  20     // heigher speed to make corrections when line following
#define MOTOR_RATIO 1.0     // right motor power ratio off-set
#define TIME_CONSTANT 2.2   // calibrated to conveted RPS distances into time
#define TURN_CONSTANT 0.175 // calibrated to conveted turn angle into time
#define ANGLE_OFFSET 0.0    // offset for the QR code initail angle
#define PRECISION 0.125     // percision the robot will calibrate the motors to
#define TIME 0.05

void drive_forward(float Distance, float Dirrection, Robot& robot)
{
    float Travel_Time = 0.0974*Distance + 0.0396; // emperical formula
    // Dirrection = 1 wheels forward, Dirrection = -1 skids forward
    robot.LeftMotor.SetPercent(-Dirrection * PERCENT * MOTOR_RATIO); // (-) to invert motor
    robot.RightMotor.SetPercent(Dirrection * PERCENT);
    Sleep(Travel_Time*TIME_CONSTANT);
    robot.LeftMotor.Stop(); // stop motors
    robot.RightMotor.Stop();
    LCD.Write("time driving = ");
    LCD.WriteLine(Travel_Time*TIME_CONSTANT);
}

void turn_robot(float degrees, float direction, Robot& robot)
{
    // start turning
    float turn_time = (5.9953/94.04*degrees);
    LCD.Write("turn time = ");
    LCD.WriteLine(turn_time*TURN_CONSTANT);
    robot.LeftMotor.SetPercent(direction*TURN_PERCENT*MOTOR_RATIO);// ommit (-) sign, motor already inverted
    robot.RightMotor.SetPercent(direction*TURN_PERCENT);
    Sleep(turn_time*TURN_CONSTANT);
    robot.LeftMotor.Stop(); // stop motors
    robot.RightMotor.Stop();
}

TopLevel::TopLevel()
{
}

void TopLevel::Init(Robot& robot) {

    /*Sleep(2.0);

    //while(Button_change.Value()){}
    Sleep(TIME);
    drive_forward(7.6, 1, robot);

    //while(Button_change.Value()){}
    Sleep(TIME);*/
    robot.LeftMotor.SetPercent(-40);
    robot.RightMotor.SetPercent(20);
    while(robot.ArmBumper.Value()){}
    robot.LeftMotor.Stop();
    robot.RightMotor.Stop();


    /*//while(Button_change.Value()){}
    Sleep(TIME);
    drive_forward(8, -1, robot);

    //while(Button_change.Value()){}
    Sleep(TIME);
    turn_robot(135, -1, robot);

    //while(Button_change.Value()){}
    Sleep(TIME);
    drive_forward(7.5, -1, robot);

    robot.LeftMotor.SetPercent(30);
    robot.RightMotor.SetPercent(-30);
    Sleep(5.5);
    robot.LeftMotor.Stop();
    robot.RightMotor.Stop();

    drive_forward(10, 1, robot);*/
}

bool TopLevel::Run(Robot& robot)
{
    return true;
}

void TopLevel::Finish(Robot& robot)
{

}

bool TopLevel::isEnd()
{
    return false;
}
