#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "Servo.h"

#define DEFAULT_SPEED 		35
#define MOTOR_COMPENSATION 	15

class DriveTrain
{

	private:
	Servo left_motor;
	Servo right_motor;
	
	public:
	
	DriveTrain();
	DriveTrain(int left_motor_pin, int right_motor_pin);
	
	void attachMotors(int left_motor_pin, int right_motor_pin);
	void drive(int left_value, int right_value);
	
	void goStraight(int speed = DEFAULT_SPEED);
	void turnLeft(int speed = DEFAULT_SPEED/2);
	void turnRight(int speed = DEFAULT_SPEED/2);
	void turn(int speed);
}

#endif
