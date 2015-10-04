#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "Arduino.h"
#include <Servo.h> //it has to be included in the main .ino file

#define DEFAULT_SPEED 		50
#define MOTOR_COMPENSATION 	.1

class DriveTrain
{

	private:
	Servo left_motor;
	Servo right_motor;
	
	public:
	
	DriveTrain(){}
	DriveTrain(int left_motor_pin, int right_motor_pin);//This constructor didn't work with global variable
	
	void attachMotors(int left_motor_pin, int right_motor_pin);
	void drive(int left_value, int right_value);

	void stop();
  
	void goStraight(int speed = DEFAULT_SPEED);
	void turnLeft(int speed = DEFAULT_SPEED/2);
	void turnRight(int speed = DEFAULT_SPEED/2);
	void turn(int speed);
};

#endif
