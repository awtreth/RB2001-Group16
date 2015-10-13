#ifndef SETUP_H
#define SETUP_H

#include "FRED.h"

//Let's put initial setup configuration here

#define LEFT_MOTOR_PIN  6
#define RIGHT_MOTOR_PIN 7

// Line trackers
#define LN_TRACK_KP .015
#define LN_TRACK_KD 15
#define LN_TRACK_KI 0
#define LEFT_LN_SENSOR_PIN 	A3
#define RIGHT_LN_SENSOR_PIN A4
#define SIDE_LN_SENSOR_PIN 	A5
#define BACK_LN_SENSOR_PIN 	A2

#define REACTOR_SWITCH_PIN  29
#define WALL_SWITCH_PIN     28
#define STARTER_SWITCH_PIN 27

// FRED
#define GRIPPER_PIN 4
#define ANGLE_PIN 5
#define LIFT_PIN 8
#define HI_PIN 25
#define LO_PIN 26

///
#define ALARM_PIN_LOW  16
#define ALARM_PIN_HIGH 17

RobotController robot;
Action action_sequence[] = {
  
  //we can put this in a MacroAction
  Action(MOVE_GRIPPER, MOVE_UP),
  Action(WAIT, 2000),
  Action(GRIPPER, OPEN),
  Action(TURN_GRIPPER, VERTICAL),
  Action(MOVE_FORWARD, -1),
  Action(MOVE_GRIPPER, MOVE_DOWN),
  Action(WAIT, 1000),
  Action(GRIPPER, CLOSE),
  Action(WAIT, 1000),
  Action(SET_ALARM, 1),
  Action(MOVE_GRIPPER, MOVE_UP),
  Action(WAIT, 2000),
  Action(TURN_GRIPPER, HORIZONTAL),
  
  //Action(MOVE_BACKWARD, 2),
  //Action(TURN, RIGHT),
  //Action(MOVE_FORWARD, -1),
  //Action(WAIT, 1000),
  
  Action(MOVE_BACKWARD, 1),
  Action(REACTOR_TO_STORAGE),

  Action(SET_ALARM, 0),
  Action(WAIT, 1000),
  Action(GRIPPER, OPEN),
  Action(WAIT, 1000),
  Action(TURN_GRIPPER, SPECIAL_GRAB),

  Action(STORAGE_TO_SUPPLY),

  Action(WAIT, 1000),
  Action(GRIPPER, CLOSE),
  Action(WAIT, 1000),

  Action(SET_ALARM, 2),
  Action(SUPPLY_TO_REACTOR),

  Action(TURN_GRIPPER, SPECIAL_VERT),
  Action(WAIT, 1000),
  Action(MOVE_GRIPPER, MOVE_DOWN),
  Action(SET_ALARM, 0),
  Action(WAIT, 1000),
  Action(GRIPPER, OPEN),
  Action(WAIT, 2000),
  Action(MOVE_GRIPPER, MOVE_UP),
  Action(WAIT, 5000)
};

Action action_seq_test[] =
{
  Action(TURN_GRIPPER, HORIZONTAL),
  Action(MOVE_GRIPPER, MOVE_UP),
  Action(WAIT, 1000),
  Action(GRIPPER,OPEN),
  Action(WAIT,2000),
  Action(GRIPPER, CLOSE),
  Action(WAIT, 1000),
  Action(MOVE_FORWARD),
  Action(WAIT, 1000),
  Action(GRIPPER, OPEN),
  Action(WAIT, 1000),
  Action(MOVE_BACKWARD)
  //gripper_test   
  
  /*REACTOR_TO_STORAGE,
  STORAGE_TO_SUPPLY,
  SUPPLY_TO_REACTOR*/

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
  robot.drive_train.pid.setLimits(-90, +90);

  //SETUP FRED
  robot.fred = FRED(LIFT_PIN, ANGLE_PIN, GRIPPER_PIN, HI_PIN, LO_PIN);
  //...
  robot.setAlarmPins(ALARM_PIN_LOW, ALARM_PIN_HIGH);
}


/*MacroAction aproxTakeRodTurn = {
	Action(MOVE_GRIPPER, )
	Action(MOVE_FORWARD, SLOW_SPEED),
	Action(MOVE_GRIPPER, ),
};
MacroAction return
*/

#endif
