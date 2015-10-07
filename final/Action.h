#ifndef ACTION_H
#define ACTION_H

enum ActionType {
	//general actions
	TURN, MOVE_FORWARD, MOVE_BACKWARD,
	GRIPPER, TURN_GRIPPER, MOVE_GRIPPER,
	STOP, ALARM,
	//specific actions
	TURN_RIGHT, TURN_LEFT, GRIPPER_ON, GRIPPER_OFF, TURN_GRIPPER_HORIZONTAL,
	TURN_GRIPPER_VERTICAL, MOVE_GRIPPER_UP, MOVE_GRIPPER_DOWN,
	
	N_ACTION_TYPE
};

enum TurnDirection{LEFT_TURN, RIGHT_TURN, TURN_180};
enum GripperPosition{OPEN, CLOSE};
enum LifterAction{MOVE_UP, MOVE_DOWN};
enum GripperOrientation{HORIZONTAL, VERTICAL};

enum LineSensorIndex{LEFT_LS, RIGHT_LS, SIDE_LS, BACK_LS, N_LINE_SENSORS};
enum SwitchIndex{FRONT_SW, N_SWITCHES};

class Action
{
  public:
  ActionType type;
  
  Action(){}
  
  Action(ActionType type, int param1 = 0, int param2 = 0)
  {
    this->type = type;
    this->param1 = param1;
    this->param2 = param2;
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
  };
  
  union
  {
    int param2;
    LineSensorIndex stopper_sensor; //for turn (SIDE_LS or BACK_LS)
    int speed;//for MOVE_FORWARD and MOVE_BACKWARD
  };
};

//typedef Action[] MacroAction;

#endif
