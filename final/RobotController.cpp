#include "Arduino.h"
#include "RobotController.h"
#include "util.h"

RobotController::RobotController()
{
  bluetooth.setup();
	bluetooth.setInputPointers(&this->storageTube, &this->supplyTube, &stop);
	stop = false;
	radLevel = 0;
  my_position = 0; //0-3 
  goal_reactor = 1;//1 or 2
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
      //SIMPLE ACTIONS
			case MOVE_FORWARD: return this->drive_train.moveForward(action.n_line_crossings); break;
			case TURN: return this->drive_train.turn90(action.direction); break;
			case MOVE_BACKWARD: return this->drive_train.moveBackward(action.n_line_crossings); break;
      
      //GRIPPER, TURN_GRIPPER, MOVE_GRIPPER,
      //STOP, ALARM,

      //MACRO_ACTIONS
      case REACTOR_TO_STORAGE: return this->reactor2storage(); break;
      case STORAGE_TO_SUPPLY: return this->storage2supply(); break;
      case SUPPLY_TO_REACTOR: return this->supply2reactor(); break;
			//TODO: others
			
			default: Serial.println("Default case in RobotController::execute(action)");
		}
	}
	
	return NOT_DONE_YET;
}

int RobotController::reactor2storage()
{
	static bool new_move = true;
	static int current_action = 0;
	
	static Action action_seq[] = 
	{
		Action(MOVE_BACKWARD),//to be decided
		Action(TURN, RIGHT),//to be decided
		Action(MOVE_FORWARD, 0, DEFAULT_SPEED)
	};
	
	if(new_move)
	{
		//decide
    int i = 0;

    //CONSIDER BACKWARD MOVMENT
		if(goal_reactor == 1)
		{
      for(i = 0; i < 4; i++)
        if(!storageTube.tube[i]) break;
        
			action_seq[0].n_line_crossings = i+1;
			action_seq[1].direction = RIGHT;
		}else if(goal_reactor == 2)
		{	
      for(i = 3; i >= 0; i--)
        if(!storageTube.tube[i]) break;
        		
			action_seq[0].n_line_crossings = 4-i;
			action_seq[1].direction = LEFT;
		}

    my_position = i;
    
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


int RobotController::storage2supply()
{
  static bool new_move = true;
  static int current_action = 0;
  
  static Action action_seq[] = 
  {
    Action(MOVE_BACKWARD, 1, DEFAULT_SPEED),//return to center
    Action(TURN, RIGHT),//to be decided
    Action(MOVE_FORWARD, 0, DEFAULT_SPEED),//to be decided
    Action(TURN, RIGHT),//to be decided
    Action(MOVE_FORWARD, 0, DEFAULT_SPEED)
  };
  
  if(new_move)
  {
    //decide
    int i = 0;

    //CONSIDER BACKWARD MOVMENT
    if(goal_reactor == 1)
    {
      for(i = 0; i < 4; i++)
        if(!storageTube.tube[i]) break;
    }else if(goal_reactor == 2)
    { 
      for(i = 3; i >= 0; i--)
        if(!storageTube.tube[i]) break;
    }

    if(i<=my_position)
      {
        action_seq[1].direction = LEFT;
        action_seq[3].direction = LEFT;
      }else
      {
        action_seq[1].direction = RIGHT;
        action_seq[3].direction = RIGHT;
      }

     action_seq[2].n_line_crossings = abs(my_position-i);

    my_position = i;
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

int RobotController::supply2reactor()
{
  static int current_action = 0;
  
  static Action action_seq[] = 
  {
    Action(MOVE_BACKWARD, 1, DEFAULT_SPEED),//return to center
    Action(TURN, (goal_reactor==1)?RIGHT:LEFT),
    Action(MOVE_FORWARD, 0, DEFAULT_SPEED),//to be decided
  };
  
  current_action += this->execute(action_seq[current_action]);
  
  //is the last action?
  if(current_action == (sizeof(action_seq)/sizeof(Action)))
  {
    current_action = 0;
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

