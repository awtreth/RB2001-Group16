#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "Switch.h"
#include "DriveTrain.h"
#include "LineSensor.h"
#include "Action.h"
#include "PidController.h"

class RobotController
{
	public:
	DriveTrain drive_train;
	
	LineSensor line_sensors[N_LINE_SENSORS];
	Switch switches[N_SWITCHES];
	
	int execute(Action action);
	int stop();
	int resume();

	void setAlarmPin(int pin_number);
	void alarmOn(){} 
	void alarmOff(){}

	PidController ln_track_pid;

	private:
  
	int alarm_pin;
	
	//All the functions execute just 1 iteration and return
	//0 when it didn't finish yet
	//1 when it's done (go to the next action)
	
	int turn(TurnDirection dir, LineSensorIndex stopper_sensor = SIDE_LS);
	int turnRight();
	int turnLeft();
	//int turn180();
	//int turn90(TurnDirection dir);
	
	int moveForward(int n_line_crossings = 0, int speed = DEFAULT_SPEED);//we can create constants for default values of speed
	int moveBackward(int n_line_crossings = 0, int speed = DEFAULT_SPEED);
	
	//int moveBackward(int time);//maybe we will need to consider the time
	
	/*int moveGripper(LifterAction movement);
	int moveGripperUp();
	int moveGripperDown();

	int turnGripper(GripperOrientation orientation);
	int turnGripperHorizontal();
	int turnGripperVertical();
	
	int gripper(GripperPosition state);
	int openGripper();
	int closeGripper();*/
};

#endif
