#define LN_TRACK_KP .015
#define LN_TRACK_KD 2.8
#define LN_TRACK_KI 0

#define LEFT_MOTOR_PIN 4
#define RIGHT_MOTOR_PIN 5

#define LEFT_LN_SENSOR_PIN 	A11
#define RIGHT_LN_SENSOR_PIN A10
#define SIDE_LN_SENSOR_PIN 	A9
#define BACK_LN_SENSOR_PIN 	A8

#define FRONT_SWITCH_PIN 6 //TODO: setup this

//For action approach
//we can put that declaration in a separated file (maybe we can create a "Action.h")
MacroAction aproxTakeRodTurn = {
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
};
