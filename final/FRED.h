#ifndef FRED_H
#define FRED_H

#include "Arduino.h"
#include <Servo.h> //it has to be included in the main .ino file
#include "PidController.h"

enum GripperPosition{OPEN, CLOSE};
enum LifterAction{MOVE_UP, MOVE_DOWN};
enum GripperOrientation{HORIZONTAL, VERTICAL};

//Just basic movments of fred
class FRED//TODO: translation of FRED
{

	private:
	int gripper_servo_pin;
	Servo lift_motor;
	Servo turn_gripper;
	//Switch fred_stopper; //TODO: implement it if it's necessary
	
	//PidController lift_speed_pid;
	
	public:
	
	FRED();
	FRED(int gripper_servo_pin, int lift_motor_pin, int turn_gripper_pin);
	
	void attachPins(int gripper_servo_pin, int lift_motor_pin, int turn_gripper_pin);


	//the next functions return DONE(=1) or NOT_DONE_YET(=0)
	//constants defined in "util.h"
	int moveGripper(LifterAction movement);
	int moveGripperUp();
	int moveGripperDown();

	int turnGripper(GripperOrientation orientation);
	int turnGripperHorizontal();
	int turnGripperVertical();
	
	int gripper(GripperPosition state);
	int openGripper();
	int closeGripper();
};

#endif
