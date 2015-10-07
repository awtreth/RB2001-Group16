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

void RobotController::setAlarmPin(int pin_number)
{
	alarm_pin = pin_number;
	pinMode(pin_number, OUTPUT);
}

void RobotController::alarmOn()
{
	
} 

void RobotController::alarmOff()
{
	
}

