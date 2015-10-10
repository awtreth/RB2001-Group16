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
			case MOVE_FORWARD: return this->drive_train.moveForward(action.n_line_crossings, action.speed); break;
			case TURN: return this->drive_train.turn90(action.direction); break;
			case MOVE_BACKWARD: return this->drive_train.moveForward(action.n_line_crossings, action.speed); break;
      //GRIPPER, TURN_GRIPPER, MOVE_GRIPPER,
      //STOP, ALARM,
			//TODO: others
			default: Serial.println("Default case in RobotController::execute(action)");
		}
	}
	
	return NOT_DONE_YET;
}

int RobotController::reactor2storage(int from_reactor, int storage_dest)
{
	static bool new_move = true;
	static int current_action = 0;
	
	static Action action_seq[]
	{
		Action(MOVE_BACKWARD, 0, DEFAULT_SPEED),//to be decided
		Action(TURN, RIGHT),//to be decided
		Action(MOVE_FORWARD, 0, DEFAULT_SPEED)
	};
	
	if(new_move)
	{
		//decide
		if(from_reactor == 1)
		{
			action_seq[0].n_line_crossings = storage_dest;
			action_seq[1].direction = RIGHT;
		}else if(from_reactor == 2)
		{			
			action_seq[0].n_line_crossings = 4-storage_dest;
			action_seq[1].direction = LEFT;
		}
		
		new_move = false;
		current_action = 0;
	}
	
	
	current_action += this->execute(action_seq[current_action]);
	
	//is the last action?
	if(current_action == (sizeof(action_seq)/sizeof(Action)))
	{
		current_action = 0;
		new_move = true;
		return DONE;
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

