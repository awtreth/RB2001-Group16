#ifndef FRED_H
#define FRED_H

#include "Arduino.h"
#include <Servo.h> //it has to be included in the main .ino file
#include "PidController.h"

class FRED//TODO: translation of FRED
{

	private:
	int gripper_servo_pin;
	Servo lift_motor;
	Servo turn_gripper;
	
	//PidController lift_speed_pid;
	//PidController lift_pos_pid;
	
	public:
	
	FRED();
	FRED(int gripper_servo_pin, int lift_motor_pin, int turn_gripper_pin);
	
	void attachPins(int gripper_servo_pin, int lift_motor_pin, int turn_gripper_pin);
	void lift();
	void turnGripper();
	void closeGripper();
	void openGripper();
};

#endif
