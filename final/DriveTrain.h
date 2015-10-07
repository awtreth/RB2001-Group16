#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "Arduino.h"
#include <Servo.h> //it has to be included in the main .ino file

#define DEFAULT_SPEED 		45
#define MOTOR_COMPENSATION 	.12

class DriveTrain
{

	private:
	Servo left_motor;
	Servo right_motor;
	
	public:
	
	DriveTrain(){}//may can set default values for pins
	
	//This constructor didn't work at global scope (I don't know why)
	DriveTrain(int left_motor_pin, int right_motor_pin);
	
	void attachMotors(int left_motor_pin, int right_motor_pin);
	void drive(int left_value, int right_value);

	void stop();
  
	void goStraight(int speed = DEFAULT_SPEED);
	void turnLeft(int speed = DEFAULT_SPEED/2);
	void turnRight(int speed = DEFAULT_SPEED/2);
	void turn(int speed);
};

#endif
