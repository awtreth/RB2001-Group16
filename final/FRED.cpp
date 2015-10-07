#include "Arduino.h"
#include "FRED.H"
#include "util.h"

FRED::FRED()
{
	
}

FRED::FRED(int gripper_servo_pin, int lift_motor_pin, int turn_gripper_pin)
{
	this->attachPins(gripper_servo_pin, lift_motor_pin, turn_gripper_pin);
}
	
void FRED::attachPins(int gripper_servo_pin, int lift_motor_pin, int turn_gripper_pin)
{
	this->gripper_servo_pin = gripper_servo_pin;
	lift_motor.attach(lift_motor_pin);
	turn_gripper.attach(turn_gripper_pin);
}


//MoveGrippper
int FRED::moveGripper(LifterAction movement)
{
	//TODO
	return NOT_DONE_YET;
}

int FRED::moveGripperUp()
{
	//TODO
	return NOT_DONE_YET;
}

int FRED::moveGripperDown()
{
	//TODO
	return NOT_DONE_YET;
}

//TurnGripper
int FRED::turnGripper(GripperOrientation orientation)
{
	//TODO
	return NOT_DONE_YET;
}

int FRED::turnGripperHorizontal()
{
	//TODO
	return NOT_DONE_YET;
}

int FRED::turnGripperVertical()
{
	//TODO
	return NOT_DONE_YET;
}

//gripperOpenClose
int FRED::gripper(GripperPosition state)
{
	//TODO
	return NOT_DONE_YET;
}

int FRED::openGripper()
{
	//TODO
	return NOT_DONE_YET;
}

int FRED::closeGripper()
{
	//TODO
	return NOT_DONE_YET;
}
