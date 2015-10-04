#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "Switch.h"
#include "DriveTrain.h"
#include "LineSensor.h"
#include "Action.h"




class RobotController
{
	public:
	DriveTrain drive_train;
	
	LineSensor line_sensors[N_LINE_SENSORS];
	Switch switches[N_SWITCHES];
	
	int execute(Action action);
	int stop();
	int resume();

  int alarm_pin;
  void alarmOn(){} 
  void alarmOff(){}

	private:
  
  
	//All the functions execute just 1 iteration and return
	//0 when it didn't finish yet
	//1 when it's done (go to the next action)
	int turn(TurnDirection dir, LineSensorIndex stopper_sensor);
	int goStraight(int speed, int n_line_crossings = 0);//we can create constants for default values of speed
	int moveGripper(LifterAction movement);
	int gripper(GripperPosition state);
};

#endif
