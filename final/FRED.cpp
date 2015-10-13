#include "Arduino.h"
#include "FRED.H"
#include <Servo.h>
#include "util.h"

#define DROP_SPEED 	      100 //TODO: calibrate
#define LIFT_SPEED 	      45 // calibrated
#define STOP 		          90 // motor-off speed
#define SPECIAL_GRAB_SET  65
#define SPECIAL_VERT_SET  155
#define HOR_SET 	        58
#define VERT_SET 	        150

FRED::FRED()
{
	//do anything
}
/** When initialized it attaches the requisite pins
 * @param lift_motor_pin the pin of the lifter motor
 * @param turn_gripper_pin the pin of the gripper-angling servo 
 * @param gripper_pin the pin of the griper
 * @param hi_pin the pin of the high limit switch
 * @param lo_pin the pin of the low limit switch
 */
FRED::FRED(int lift_motor_pin, int turn_gripper_pin, int gripper_pin, int hi_pin, int lo_pin)
{
	this->setPins(lift_motor_pin, turn_gripper_pin, gripper_pin, hi_pin, lo_pin);
}
/** Actually attaches the pins
 *@param lift_motor_pin the pin of the lifter motor
 *@param turn_gripper_pin the pin of the gripper-angling servo 
 *@param gripper_pin the pin of the griper
 *@param hi_pin the pin of the high limit switch
 *@param lo_pin the pin of the low limit switch
 */
void FRED::setPins(int lift_motor_pin, int turn_gripper_pin, int gripper_pin, int hi_pin, int lo_pin)
{
	lift_motor.attach(lift_motor_pin, 1000, 2000); // init 393 motor
	turn_gripper.attach(turn_gripper_pin);
	gripper_servo.attach(gripper_pin);
	this->hi_stopper.setPin(hi_pin);//Internal Pull-up by default
	this->lo_stopper.setPin(lo_pin);
}

/* Moves the gripper in the designated direction
 * @param movement the direction to move in 
 * @return 0 if the action isn't done and 1 if it has completed
 */
int FRED::moveGripper(LifterAction movement)
{
	if(movement == MOVE_UP){
		return this->moveGripperUp();
	}
	else if (movement == MOVE_DOWN){
		return this->moveGripperDown();
	}
		
	return NOT_DONE_YET;
}
/** Moves the gripper up 
 * @return 0 if not done, 1 for done
 */
int FRED::moveGripperUp()
{
	//if(hi_stopper.isPressed()){ //if it has hit the limit switch
 	  //return DONE; //you're done
	//}else{ 
		lift_motor.write(LIFT_SPEED); //if it's not over, rewrite the speed
	//}
	return DONE;
}
/** Movees the gripper down
 * @return 0 if not done, 1 for done
 */
int FRED::moveGripperDown()
{
	if (lo_stopper.isPressed()) //if it's hit the limit switch
	{
	  lift_motor.write(STOP); // all stop
	  return DONE;
	}
	else{ 
		lift_motor.write(DROP_SPEED);
	}
	return NOT_DONE_YET;
}

/** rotates the gripper into the orientation assigned
  * @param orientation the direction to be turned in
  * @return 0 if not done, 1 for done
  */
int FRED::turnGripper(GripperOrientation orientation)
{
	switch (orientation)
	{
		case HORIZONTAL: //depending on which direciton is given, write the servo with the correct value
		  turn_gripper.write(HOR_SET); 
		  return DONE; 
		  break;
		case VERTICAL: 
		  turn_gripper.write(VERT_SET); 
		  return DONE; 
		  break;
    case SPECIAL_GRAB:
      turn_gripper.write(SPECIAL_GRAB_SET);
      return DONE;
      break;
     case SPECIAL_VERT:
     turn_gripper.write(SPECIAL_VERT_SET);
     return DONE;
     break;
	}
	
	return NOT_DONE_YET;
}

/** opens and closes the gripper
  * @param state open or closed
  * @return 0 if not done, 1 for done
  */
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

