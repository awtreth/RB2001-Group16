#ifndef SETUP_H
#define SETUP_H

//Let's put initial setup configuration here

#define LEFT_MOTOR_PIN  6
#define RIGHT_MOTOR_PIN 7

// Line trackers
#define LN_TRACK_KP .017
#define LN_TRACK_KD 40
#define LN_TRACK_KI 0
#define LEFT_LN_SENSOR_PIN 	A1
#define RIGHT_LN_SENSOR_PIN A0
#define SIDE_LN_SENSOR_PIN 	A3
#define BACK_LN_SENSOR_PIN 	A2

#define REACTOR_SWITCH_PIN  27
#define WALL_SWITCH_PIN     25
#define STARTER_SWITCH_PIN 29

// FRED 
#define GRIPPER_PIN 4
#define ANGLE_PIN 5
#define LIFT_PIN 9
#define HI_PIN 29
#define LO_PIN 28


RobotController robot;

Action action_sequence[] = 
{
  REACTOR_TO_STORAGE,
  STORAGE_TO_SUPPLY,
  SUPPLY_TO_REACTOR
  /*Action(MOVE_BACKWARD, 1),
  Action(TURN, RIGHT),
  Action(MOVE_FORWARD),
  Action(MOVE_BACKWARD,1),
  Action(TURN, LEFT),
  Action(MOVE_FORWARD)*/
  
 // Action(DECIDE_NEXT_TURN),
  //...
};


void mySetup()
{
  robot.drive_train.attachMotors(LEFT_MOTOR_PIN, RIGHT_MOTOR_PIN);
  robot.drive_train.attachLnSensors(LEFT_LN_SENSOR_PIN, RIGHT_LN_SENSOR_PIN, SIDE_LN_SENSOR_PIN, BACK_LN_SENSOR_PIN);//at first we'll try without back_pin
  robot.drive_train.attachStoppers(REACTOR_SWITCH_PIN, WALL_SWITCH_PIN);//at first we'll try without back_pin
  robot.drive_train.pid.setConstants(LN_TRACK_KP, LN_TRACK_KI, LN_TRACK_KD);
  robot.drive_train.pid.setLimits(-90,+90);

  //SETUP FRED
  robot.fred = FRED(LIFT_PIN, ANGLE_PIN, GRIPPER_PIN, HI_PIN, LO_PIN);
  //...
}


/*MacroAction aproxTakeRodTurn = {
	Action(MOVE_GRIPPER, )
	Action(MOVE_FORWARD, SLOW_SPEED),
	Action(MOVE_GRIPPER, ),
};
MacroAction return
*/

#endif
