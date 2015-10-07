#ifndef SETUP_H
#define SETUP_H

//Let's put initial setup configuration here

//PIN NUMBERS
#define LN_TRACK_KP .017
#define LN_TRACK_KD 45
#define LN_TRACK_KI 0

#define LEFT_MOTOR_PIN 4
#define RIGHT_MOTOR_PIN 5

#define LEFT_LN_SENSOR_PIN 	A11
#define RIGHT_LN_SENSOR_PIN A10
#define SIDE_LN_SENSOR_PIN 	A9
#define BACK_LN_SENSOR_PIN 	A8

#define FRONT_SWITCH_PIN 6

RobotController robot;

void mySetup()
{
  //SETUP DRIVE_TRAIN
  DriveTrain dtrain;
  dtrain.attachMotors(LEFT_MOTOR_PIN, RIGHT_MOTOR_PIN);
  dtrain.attachLnSensors(LEFT_LN_SENSOR_PIN, RIGHT_LN_SENSOR_PIN, SIDE_LN_SENSOR_PIN, BACK_LN_SENSOR_PIN);//at first we'll try without back_pin
  dtrain.attachStopper(FRONT_SWITCH_PIN);//at first we'll try without back_pin
  //dtrain.pid.setConstants();
  //dtrain.pid.setLimits();

  //SETUP FRED
  FRED fred;
  //fred.attachPins(...);

  robot.drive_train = dtrain;
  robot.fred= fred;
  //robot.setAlarmPin(...);

  //...
}

/*MacroAction aproxTakeRodTurn = {
	Action(MOVE_GRIPPER, )
	Action(MOVE_FORWARD, SLOW_SPEED),
	Action(MOVE_GRIPPER, ),
};
MacroAction return


Action action_sequence[] = 
{//examples
  Action(TURN, LEFT_TURN, BACK_LS),
  Action(GO_STRAIGHT, 20, 2),
  Action(GO_STRAIGHT, 20)//has to be specified
  //...
};*/

#endif
