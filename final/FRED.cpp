#include "Arduino.h"
#include "FRED.H"
#include "util.h"

#define DEFAULT_FRED_SPEED 0 //TODO: calibrate

FRED::FRED()
{
	
}

FRED::FRED(int lift_motor_pin, int turn_gripper_pin, int gripper_pin, int sw_pin)
{
	lift_motor.attach(lift_motor_pin);
  turn_gripper.attach(turn_gripper_pin);
  gripper.attach(gripper_pin);
  this->fred_stopper.setPin(sw_pin);//Internal Pull-up by default
}

//MoveGrippper
int FRED::moveGripper(LifterAction movement)
{
	int control_signal = lifter_pid.calc(DEFAULT_FRED_SPEED, CALCULATED_SPEED);
  if
	return NOT_DONE_YET;
}

int FRED::moveGripperUp()
{
	
	return NOT_DONE_YET;
}

int FRED::moveGripperDown()
{
	lift_motor.write(/*TODO: Tune this value*/);
  if (fred_stopper.isPressed()) return DONE;
  else return NOT_DONE_YET;  
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
