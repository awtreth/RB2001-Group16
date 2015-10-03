#ifndef ACTIONS_H
#define ACTIONS_H

#include "Switch.h"
#include "DriveTrain.h"
#include "LineSensor.h"

enum ActionType{TURN, GO_FORWARD, GRIPPER, TURN_GRIPPER, LIFT_GRIPPER, STOP, ALARM};

enum TurnDirection{LEFT_TURN, RIGHT_TURN};
enum GripperPosition{OPEN, CLOSE};
enum LifterAction{MOVE_UP, MOVE_DOWN};

enum LineSensorIndex{LEFT_LS, RIGHT_LS, SIDE_LS, BACK_LS, N_LINE_SENSORS};
enum SwitchIndex{FRONT_SW, N_SWITCHES};

struct Action
{
	ActionType type;
	
	Switch stopper;
	int n_times;
	
	union//Other parameters
	{
		TurnDirection direction;
		GripperPosition position;
		LifterAction movment;
	}
};

class ActionExecuter
{
	public:
	DriveTrain drive_train;
	
	LineSensor line_sensors[N_LINE_SENSORS];
	Switch switches[N_SWITCHES];
	
	bool execute(Action action);
	bool stop();
	bool resume();

	private:
	bool turn(TurnDirection dir, LineSensorIndex ls_id, int n_times);
	bool moveForward(TurnDirection dir, Switch stopper, int n_times);
};


bool turn(TurnDirection dir, Switch stopper, int n_times)
{
	//TODO
	return false;
}

bool moveForward(TurnDirection dir, Switch stopper, int n_times)
{
	//TODO
	return false;
}

bool moveGripper(GripperPosition pos)
{
	//TODO
	return false;
}

bool lift(LifterAction dir)
{
	//TODO
	return false;
}
#endif
