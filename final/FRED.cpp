#include "Arduino.h"
#include "FRED.H"

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
	return 0;
}

int FRED::moveGripperUp()
{
	//TODO
	return 0;
}

int FRED::moveGripperDown()
{
	//TODO
	return 0;
}

//TurnGripper
int FRED::turnGripper(GripperOrientation orientation)
{
	//TODO
	return 0;
}

int FRED::turnGripperHorizontal()
{
	//TODO
	return 0;
}

int FRED::turnGripperVertical()
{
	//TODO
	return 0;
}

//gripperOpenClose
int FRED::gripper(GripperPosition state)
{
	//TODO
	return 0;
}

int FRED::openGripper()
{
	//TODO
	return 0;
}

int FRED::closeGripper()
{
	//TODO
	return 0;
}
