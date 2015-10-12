#include "Arduino.h"
#include "FRED.H"
#include <Servo.h>
#include "util.h"

#define DROP_SPEED 	100 //TODO: calibrate
#define LIFT_SPEED 	52 // calibrated
#define STOP 		90 // motor-off speed
#define HOR_SET 	0
#define VERT_SET 	87

FRED::FRED()
{
	//do anything
}

FRED::FRED(int lift_motor_pin, int turn_gripper_pin, int gripper_pin, int hi_pin, int lo_pin)
{
	this->setPins(lift_motor_pin, turn_gripper_pin, gripper_pin, hi_pin, lo_pin);
}

void FRED::setPins(int lift_motor_pin, int turn_gripper_pin, int gripper_pin, int hi_pin, int lo_pin)
{
	lift_motor.attach(lift_motor_pin, 1000, 2000); // init 393 motor
	turn_gripper.attach(turn_gripper_pin);
	gripper_servo.attach(gripper_pin);
	this->hi_stopper.setPin(hi_pin);//Internal Pull-up by default
	this->lo_stopper.setPin(lo_pin);
}

//MoveGrippper
int FRED::moveGripper(LifterAction movement)
{
	if(movement == MOVE_UP)
		return this->moveGripperUp();
	else if (movement = MOVE_DOWN)
		return this->moveGripperDown();
		
	return NOT_DONE_YET;
}

int FRED::moveGripperUp()
{
	if(hi_stopper.isPressed()) 
	{
	  return DONE;
	}else lift_motor.write(LIFT_SPEED);
	
	return NOT_DONE_YET;
}

int FRED::moveGripperDown()
{
	if (lo_stopper.isPressed()) 
	{
	  lift_motor.write(STOP); // all stop
	  return DONE;
	}
	else lift_motor.write(DROP_SPEED);
  
	return NOT_DONE_YET;
}

//TurnGripper
int FRED::turnGripper(GripperOrientation orientation)
{
	switch (orientation)
	{
		case HORIZONTAL:  
		  turn_gripper.write(HOR_SET); 
		  return DONE; 
		  break;
		case VERTICAL: 
		  turn_gripper.write(VERT_SET); 
		  return DONE; 
		  break;
	}
	
	return NOT_DONE_YET;
}

//gripperOpenClose
int FRED::gripper(GripperPosition state)
{
	
	switch (state)
	{
		case OPEN:  
		  gripper_servo.write(0); 
		  return DONE; 
		  break;
		case CLOSE: 
		  gripper_servo.write(180); 
		  return DONE; 
		  break;
	}
	return NOT_DONE_YET;
}

