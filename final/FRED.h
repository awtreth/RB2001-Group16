#ifndef FRED_H
#define FRED_H

#include "Arduino.h"
#include <Servo.h> //it has to be included in the main .ino file
#include "PidController.h"
#include "Switch.h"

enum GripperPosition{OPEN, CLOSE};
enum LifterAction{MOVE_UP, MOVE_DOWN};
enum GripperOrientation{HORIZONTAL, VERTICAL};

///Fuel Rod Extractor Device
/**
 * Do all the basic movements needed to take/place the rod
 */
class FRED
{

	private:
  
	Servo lift_motor;
	Servo turn_gripper;
	Servo gripper_servo;
  
	public:

	Switch lo_stopper;
	Switch hi_stopper;
  
	FRED(); // unused constructor
	FRED(int lift_motor_pin, int turn_gripper_pin, int gripper_pin, int hi_pin, int lo_pin);

  void setPins(int lift_motor_pin, int turn_gripper_pin, int gripper_pin, int hi_pin, int lo_pin);

	//the next functions return DONE(=1) or NOT_DONE_YET(=0)
	//constants defined in "util.h"
	int moveGripper(LifterAction movement);
	int moveGripperUp();///lift gripper
	int moveGripperDown();///put gripper down
  
	int turnGripper(GripperOrientation orientation);
	int	gripper(GripperPosition state);

};

#endif
