#include "Arduino.h"
#include "RobotController.h"

int RobotController::execute(Action action)
{
  switch(action.type)
  {
    case MOVE_FORWARD: return this->drive_train.moveForward(action.n_line_crossings); break;
    case TURN: return this->drive_train.turn90(action.direction); break;
    
    default: Serial.println("Default case in RobotController::execute(action)");
  }

  
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

