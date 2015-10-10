#include "Arduino.h"
#include "RobotController.h"
#include "util.h"

RobotController::RobotController()
{
  bluetooth.setup();
	bluetooth.setInputPointers(&this->storageTube, &this->supplyTube, &stop);
	stop = false;
	radLevel = 0;
}

int RobotController::execute(Action action)
{
	if(this->stop)
	{
		this->drive_train.stop();
		//this->fred.stop();
	}else
	{
		
		switch(action.type)
		{
			case MOVE_FORWARD: return this->drive_train.moveForward(action.n_line_crossings); break;
			case TURN: return this->drive_train.turn90(action.direction); break;
			case MOVE_BACKWARD: break;
      //GRIPPER, TURN_GRIPPER, MOVE_GRIPPER,
      //STOP, ALARM,
			//TODO: others
			default: Serial.println("Default case in RobotController::execute(action)");
		}
	}
	
	return NOT_DONE_YET;
}

void RobotController::printTubes()
{
	Serial.print("StorageArea: ");
	for (int i = 0; i < 4; i++)
	{
		Serial.print((int)storageTube.tube[i]);
		Serial.print(' ');
	}
	Serial.print('\n');
	
	Serial.print("SupplyArea:  ");
	
	for (int i = 0; i < 4; i++)
	{
		Serial.print((int)supplyTube.tube[i]);
		Serial.print(' ');
	}
	Serial.print('\n');
}

void RobotController::update()
{
	static long int last_hb_time = millis();
	static long int last_update_time = millis();
	static long int last_rad_alarm_time = millis();
	
	bluetooth.update();
	
	long int current_time = millis();
	
	if((current_time - last_hb_time) > HEARTBEAT_PERIOD)
  {
		bluetooth.sendHB();
    last_hb_time = current_time;
  }
	//if((current_time - last_update_time) > SEND_STATUS_PERIOD)
		//bluetooth.sendStatus(this->moveStat, this->gripStat, this->opStat);

  this->radLevel = 2;
	if((current_time - last_rad_alarm_time) > RADIATION_ALARM_PERIOD)
	{	
	  bluetooth.sendRadiation(this->radLevel);
	  last_rad_alarm_time = current_time;
	}
}

/*int RobotController::stop()
{
	//TODO
	return 0;
}

int RobotController::resume()
{
	//TODO
	return 0;
*/

void RobotController::setAlarmPin(int pin_number)
{
	alarm_pin = pin_number;
	pinMode(pin_number, OUTPUT);
}

void RobotController::alarmOn()
{
	//TODO
} 

void RobotController::alarmOff()
{
	//TODO
}

