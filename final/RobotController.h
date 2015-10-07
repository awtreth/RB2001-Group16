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
	FRED fred;
	
	int execute(Action action);
	//int execute(MacroAction action_seq);
	int stop();
	int resume();

	void setAlarmPin(int pin_number);
	void alarmOn(); 
	void alarmOff();

	private:
  
	int alarm_pin;
};

#endif
