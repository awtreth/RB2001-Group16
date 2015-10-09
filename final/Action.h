#ifndef ACTION_H
#define ACTION_H

#include "FRED.h"
#include "DriveTrain.h"

enum ActionType {
	//general actions
	TURN, MOVE_FORWARD, MOVE_BACKWARD,
	GRIPPER, TURN_GRIPPER, MOVE_GRIPPER,
	STOP, ALARM,

  //macroActions
  REACTOR_TO_STORAGE, STORAGE_TO_SUPPLY, SUPPLY_TO_REACTOR,
  TAKE_GRIPPER, PUT_GRIPPER,
  
	//specific actions
	TURN_RIGHT, TURN_LEFT, GRIPPER_ON, GRIPPER_OFF, TURN_GRIPPER_HORIZONTAL,
	TURN_GRIPPER_VERTICAL, MOVE_GRIPPER_UP, MOVE_GRIPPER_DOWN,
	
	N_ACTION_TYPE
};


class Action
{
  public:
  ActionType type;
  
  Action(){}
  
  Action(ActionType type, int param1 = 0, int param2 = 0, int param3 = 0)
  {
    this->type = type;
    this->param1 = param1;
    this->param2 = param2;
    this->param3 = param3;
  }
  
  //Other parameters
  union
  {
    int param1;
    int n_line_crossings;;//we can create constants for default values of speed
    TurnDirection direction;//for turn (LEFT_TURN or RIGHT_TURN)
    GripperPosition position;//for gripper itself (OPEN or CLOSE)
    LifterAction movment;//for lifter (MOVE_UP or MOVE_DOWN) 
    GripperOrientation orientation;//for lifter (MOVE_UP or MOVE_DOWN)
    int supply_dest;
    int from_supply;
	  int has2decide;//for turn and MOVE_FORWARD movments. RobotController checks if it's equal to DECIDE_ACTION
  };

  union
  {
    int param2;
    int storage_dest;
    int from_storage;
    LineSensorIndex stopper_sensor; //for turn (SIDE_LS or BACK_LS)
    int speed;//for MOVE_FORWARD and MOVE_BACKWARD
  };

  union
  {
    int param3;
    int goal_reactor;
  };
  
};

//typedef Action[] MacroAction;

#endif
