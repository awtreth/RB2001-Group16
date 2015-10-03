#ifndef FRED_H
#define FRED_H

#include "Arduino.h"
#include <Servo.h> //it has to be included in the main .ino file

class FRED//TODO: translation of FRED
{

	private:
	Servo gripper_servo;
	Servo lift_motor;
	Servo turn_gripper_servo;
	
	public:
	
	void lift();
	void turnGripper();
	void closeGripper();
	void openGripper();
};

#endif
