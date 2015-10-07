#include "Arduino.h"
#include "DriveTrain.h"

//#define LEFT_MOTOR_REF 25  
//#define RIGHT_MOTOR_REF 40//right motor turns faster than the left  

//This constructor didn't work (very weird)
DriveTrain::DriveTrain(int left_motor_pin, int right_motor_pin)
{
	this->attachMotors(left_motor_pin, right_motor_pin);
  //this->stop();
}

void DriveTrain::attachMotors(int left_motor_pin, int right_motor_pin)
{
	this->left_motor.attach(left_motor_pin);
	this->right_motor.attach(right_motor_pin);
}

void DriveTrain::stop()
{
  this->drive(0,0);
}

void DriveTrain::drive(int left_value, int right_value)//-90~90
{
//	right_value += COMPENSATION/2;
//	left_value  -= COMPENSATION/2;
	
	left_value = constrain(left_value, -90,90);
	right_value = constrain(right_value, -90,90);

  right_value *= (1.-MOTOR_COMPENSATION);
  left_value *= (1.+MOTOR_COMPENSATION);

	left_value = map(left_value, -90,90,0,180);
	right_value = map(right_value, -90,90,180,0);

	this->right_motor.write(right_value);
	this->left_motor.write(left_value);
}

void DriveTrain::goStraight(int speed)//-90~90
{
	this->drive(speed, speed);
}
void DriveTrain::turnLeft(int speed)//0-90
{
	speed = constrain(speed, 0,90);
	this->turn(-speed);
}

void DriveTrain::turnRight(int speed)//0-90
{
	speed = constrain(speed, 0,90);
	this->turn(speed);
}

void DriveTrain::turn(int speed)//-90~90
{
	this->drive(speed, -speed);
}
