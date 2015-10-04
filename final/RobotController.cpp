#include "Arduino.h"
#include "RobotController.h"

int RobotController::execute(Action action)
{
	//TODO
	return 0;
}

int RobotController::stop()
{
	//TODO
	return 0;
}

int RobotController::resume()
{
	//TODO
	return 0;
}


//All the functions execute just 1 iteration and return
//0 when it didn't finish yet
//1 when it's done (go to the next action)
int RobotController::turn(TurnDirection dir, LineSensorIndex stopper_sensor)
{
	//TODO
	return 0;
}

int RobotController::goStraight(int speed, int n_line_crossings)
{
	//TODO
	return 0;
}

int RobotController::moveGripper(LifterAction movement)
{
	//TODO
	return 0;
}

int RobotController::gripper(GripperPosition state)
{
	//TODO
	return 0;
}
