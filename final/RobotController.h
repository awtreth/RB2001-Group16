#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "Switch.h"
#include "DriveTrain.h"
#include "LineSensor.h"
#include "Action.h"
#include "PidController.h"
#include "Bluetooth.h"

#define HEARTBEAT_PERIOD 2000 //in miliseconds
#define SEND_STATUS_PERIOD 1000
#define RADIATION_ALARM_PERIOD 1000

class RobotController
{
	public:
	
	RobotController();
	
	DriveTrain drive_train;
	FRED fred;

  //Bluetooth will update these variables automatically
	StorageTube storageTube;
	SupplyTube supplyTube;
	bool stop;
	
	void printTubes();
	
	
	int radLevel;
	
	//int macro_action_i;
	
	Bluetooth bluetooth;
	
	int execute(Action action);
	void update();
	//int execute(MacroAction action_seq);
	//int stop();
	//int resume();

	void setAlarmPin(int pin_number);
	void alarmOn(); 
	void alarmOff();

	int reactor2storage(int from_reactor, int storage_dest);
  //int storage2supply(int from_storage, int supply_dest, int goal_reactor);
  //int supply2reactor(int from_supply, int reactor_dest);

	private:
  
	int alarm_pin;
};

#endif
