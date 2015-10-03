#ifndef FRED_H
#define FRED_H

#include "Arduino.h"
#include <Servo.h> //it has to be included in the main .ino file
#include "PidController.h"

class FRED//TODO: translation of FRED
{

	private:
	Servo gripper_servo;
	Servo lift_motor;
	Servo turn_gripper_servo;
	
	//PidController lift_speed_pid;
	//PidController lift_pos_pid;
	
	public:
	
	void lift();
	void turnGripper();
	void closeGripper();
	void openGripper();
};

#endif
