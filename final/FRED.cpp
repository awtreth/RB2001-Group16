#include "Arduino.h"
#include "FRED.H"
#include "util.h"

#define DEFAULT_FRED_SPEED 0 //TODO: calibrate

FRED::FRED()
{
	
}

FRED::FRED(int gripper_servo_pin, int lift_motor_pin, int turn_gripper_pin, int stopper_pin)
{
	this->attachPins(gripper_servo_pin, lift_motor_pin, turn_gripper_pin, stopper_pin);
}
	
void FRED::attachPins(int gripper_servo_pin, int lift_motor_pin, int turn_gripper_pin, int stopper_pin)
{
	this->gripper_servo_pin = gripper_servo_pin;
	this->fred_stopper.setPin(stopper_pin);//Internal Pull-up by default
	lift_motor.attach(lift_motor_pin);
	turn_gripper.attach(turn_gripper_pin);
}


//MoveGrippper
int FRED::moveGripper(LifterAction movement)
{
	//int control_signal = lift_speed_pid.calc(DEFAULT_FRED_SPEED, CALCULATED_SPEED);
	return NOT_DONE_YET;
}

int FRED::moveGripperUp()
{
	
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
