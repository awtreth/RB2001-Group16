#ifndef ACTION_H
#define ACTION_H

enum ActionType{TURN, GO_STRAIGHT, GRIPPER, TURN_GRIPPER, LIFT_GRIPPER, STOP, ALARM};

enum TurnDirection{LEFT_TURN, RIGHT_TURN};
enum GripperPosition{OPEN, CLOSE};
enum LifterAction{MOVE_UP, MOVE_DOWN};

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
  
  union//Other parameters
  {
    int param1;
    int speed;//we can create constants for default values of speed
    TurnDirection direction;//for turn (LEFT_TURN or RIGHT_TURN)
    GripperPosition position;//for gripper itself (OPEN or CLOSE)
    LifterAction movment;//for lifter (MOVE_UP or MOVE_DOWN) 
  };
  
  union
  {
    int param2;
    LineSensorIndex stopper_sensor; //for turn (SIDE_LS or BACK_LS)
    int n_line_crossings;
  };
};

#endif
