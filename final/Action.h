#ifndef ACTION_H
#define ACTION_H

#include "FRED.h"
#include "DriveTrain.h"

/** Everything related to Actions
 * 
 * Class Action and enum of ActionsType
 */



///Name of the actions
enum ActionType {
	///simple actions
	TURN,
  MOVE_FORWARD,
  MOVE_BACKWARD,
  GRIPPER,
  TURN_GRIPPER,
  MOVE_GRIPPER,
	STOP,
  SET_ALARM,
  WAIT,

  ///macroActions (include more than one simple action
  REACTOR_TO_STORAGE,
  STORAGE_TO_SUPPLY,
  SUPPLY_TO_REACTOR,
  REACTOR_TO_REACTOR,
  STARTUP,
  PLACE_IN_REACTOR,
  GRAB_ROD,
  TAKE_GRIPPER,
  PUT_GRIPPER,
  
	N_ACTION_TYPE
};

/** Represents the possible actions that the robot can do
 * 
 * This class doesn't have any method. Only the constructor and parameters are important
 */
class Action
{
  public:
  ActionType type;
  
  Action(){}
  
  ///Initialize the 
  Action(ActionType type, int param1 = 0, int param2 = 0) ///If there isn't a param passed, defaults to 0 and therefore ignores it
  {
    this->type = type; //The type is the general action, see above table for type list
    this->param1 = param1; //params are modifiers for the action. Direction to turn, speed, etc. See param1 union for specifics
    this->param2 = param2; //see param2 union for specifics
  }
  
  ///Param 1
    union
    {//param1 has many names
        int param1;

        int n_line_crossings;;///<for MOVE_FORWARD AND MOVE_BACKWARD movements
        TurnDirection direction;///<for turn (LEFT_TURN or RIGHT_TURN)
        GripperPosition position;///<for gripper itself (OPEN or CLOSE)
        LifterAction movement;///<for lifter (MOVE_UP or MOVE_DOWN) 
        GripperOrientation orientation;///<for lifter (MOVE_UP or MOVE_DOWN)
        int duration;///< for WAIT action 
        int rad_level;///< for SET_ALARM action
    };

    ///Param 2
    union
    {//param2 has less names, but still important
        int param2;
        
        int speed;//for MOVE_FORWARD and MOVE_BACKWARD
    };

};

//typedef Action[] MacroAction;

#endif
