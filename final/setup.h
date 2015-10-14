#ifndef SETUP_H
#define SETUP_H

#include "FRED.h"

//Let's put initial setup configuration here

#define LEFT_MOTOR_PIN  6
#define RIGHT_MOTOR_PIN 7

// Line trackers
#define LN_TRACK_KP .015
#define LN_TRACK_KD 14
#define LN_TRACK_KI 0
#define LEFT_LN_SENSOR_PIN 	A3
#define RIGHT_LN_SENSOR_PIN A4
#define RIGHT_SIDE_LN_SENSOR_PIN 	A5
#define LEFT_SIDE_LN_SENSOR_PIN 	A2

#define REACTOR_SWITCH_PIN  29
#define WALL_SWITCH_PIN     28
#define STARTER_SWITCH_PIN  27

// FRED
#define GRIPPER_PIN 4
#define ANGLE_PIN   5
#define LIFT_PIN    8
#define HI_PIN      25
#define LO_PIN      26

///
#define ALARM_PIN_LOW  16
#define ALARM_PIN_HIGH 17

RobotController robot;
Action action_sequence[] = {

  //we can put this in a MacroAction
  Action(STARTUP),
/*
  //Action(SET_ALARM_,1),
  Action(REACTOR_TO_STORAGE),


  Action(GRIPPER, OPEN),
  Action(WAIT, 1000),
  Action(TURN_GRIPPER, SPECIAL_GRAB),
  Action(SET_ALARM, 0),
  Action(WAIT, 1000),

  Action(STORAGE_TO_SUPPLY),

  Action(WAIT, 1000),
  Action(GRIPPER, CLOSE),
  Action(WAIT, 1000),

  Action(SET_ALARM, 2),
  Action(SUPPLY_TO_REACTOR),
  Action(PLACE_IN_REACTOR),
  Action(SET_ALARM, 0),*/


  Action(REACTOR_TO_REACTOR),
  Action(GRAB_ROD),

  Action(SET_ALARM, 1),
  Action(REACTOR_TO_STORAGE),
  Action(GRAB_ROD),
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
  Action(PLACE_IN_REACTOR),
  Action(SET_ALARM, 3),
  Action(WAIT, 100000000)
};

void mySetup()
{
  //DriveTrain setup
  robot.drive_train.attachMotors(LEFT_MOTOR_PIN, RIGHT_MOTOR_PIN);
  robot.drive_train.attachLnSensors(LEFT_LN_SENSOR_PIN, RIGHT_LN_SENSOR_PIN, RIGHT_SIDE_LN_SENSOR_PIN, LEFT_SIDE_LN_SENSOR_PIN);//at first we'll try without back_pin
  robot.drive_train.attachStoppers(REACTOR_SWITCH_PIN, WALL_SWITCH_PIN);//at first we'll try without back_pin
  robot.drive_train.pid.setConstants(LN_TRACK_KP, LN_TRACK_KI, LN_TRACK_KD);
  robot.drive_train.pid.setLimits(-90, +90);

  //SETUP FRED
  robot.fred = FRED(LIFT_PIN, ANGLE_PIN, GRIPPER_PIN, HI_PIN, LO_PIN);
  robot.setAlarmPins(ALARM_PIN_LOW, ALARM_PIN_HIGH);
}

#endif
