#include "Arduino.h"
#include "FRED.H"
#include "util.h"

#define DROP_SPEED 0 //TODO: calibrate
#define LIFT_SPEED 0 //TODO: calibrate
#define KEEP_UP_SPEED 0 //TODO: calibrate
#define STOP 90 // motor-off speed

FRED::FRED()
{
	
}

FRED::FRED(int lift_motor_pin, int turn_gripper_pin, int gripper_pin, int hi_pin, int lo_pin)
{
	lift_motor.attach(lift_motor_pin);
  turn_gripper.attach(turn_gripper_pin);
  gripper.attach(gripper_pin);
  this->hi_stop.setPin(hi_pin);//Internal Pull-up by default
  this->lo_stop.setPin(lo_pin);
}

//MoveGrippper
int FRED::moveGripper(LifterAction movement)
{
	return NOT_DONE_YET;
}

int FRED::moveGripperUp()
{
	if(hi_stopper.isPressed()) 
	{
	  lift_motor.write(KEEP_UP_SPEED);
	  return DONE;
	}
  else
  {
    lift_motor.write(LIFT_SPEED);  
  }
	return NOT_DONE_YET;
}

int FRED::moveGripperDown()
{
	if (lo_stopper.isPressed()) 
	{
	  lift_motor.write(STOP); // all stop
	  return DONE;
	}
  else 
  {
    lift_motor.write(/*TODO: Tune this value*/);
  }
  return NOT_DONE_YET;
}

//TurnGripper
int FRED::turnGripper(GripperOrientation orientation)
{
	switch (orientation)
  {
    case HORIZONTAL:  turn_gripper.write();
    case VERTICAL: turn_gripper.write();
    default: // do nothing  
  }
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
