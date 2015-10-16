#include "Arduino.h"
#include "RobotController.h"
#include "util.h"
/**
 * @brief Creates the Robot controller object
 * @details Sets up and adds inputs to the bluetooth, creates the default values for the starting reactor and position
 */
RobotController::RobotController()
{
  bluetooth.setup();
  bluetooth.setInputPointers(&this->storageTube, &this->supplyTube, &stop);
  stop = false;
  radLevel = 0;
  my_position = 0; //0-3
  goal_reactor = 1;//1 or 2
}
/**
 * @brief The main execution function
 * @details Checks if it should stop, then executes the actions based on what the action name is mapped to
 * 
 * @param action Which action it shoudl execute
 * @return 1 for DONE, 0 for NOT_DONE_YET
 */
int RobotController::execute(Action action)
{
  if (this->stop) //Checks if it's stopped
  {
    this->drive_train.stop(); //If so it stops the motors
    moveStat = STOPPED; //and changes what it's doing
  } else
  {
    moveStat = MOVINGAUTO; 
    switch (action.type) //chooses the action based on the given parameter
    {
      //SIMPLE ACTIONS
      case MOVE_FORWARD:
        return this->drive_train.moveForward(action.n_line_crossings);
        break;
      case TURN:
        return this->drive_train.turn90(action.direction);
        break;
      case MOVE_BACKWARD:
        return this->drive_train.moveBackward(action.n_line_crossings);
        break;
      case GRIPPER:
        if (action.position == OPEN)
        {
          gripStat = NOROD;
          opStat = GRIPATTEMPT;
        } else
        {
          gripStat = ROD;
          opStat = GRIPRELEASE;
        }
        return this->fred.gripper(action.position);
        break;
      case TURN_GRIPPER: 
        return this->fred.turnGripper(action.orientation); 
        break;
      case MOVE_GRIPPER: 
        return this->fred.moveGripper(action.movement); 
        break;
      case WAIT: 
        return waitDuration(action.duration); 
        break;
      case SET_ALARM: 
        return this->setAlarm(action.rad_level);
        break;

      //MACRO_ACTIONS
      case REACTOR_TO_STORAGE:
        opStat = DRIVINGSTORAGE;
        return this->reactor2storage();
        break;
      case STORAGE_TO_SUPPLY:
        opStat = DRIVINGSUPPLY;
        return this->storage2supply();
        break;
      case SUPPLY_TO_REACTOR:
        opStat = DRIVINGREACTOR;
        return this->supply2reactor();
        break;
      case REACTOR_TO_REACTOR:
        opStat = DRIVINGREACTOR;
        return this->reactor2reactor();
        break;
      case STARTUP:
        opStat = DRIVINGREACTOR;
        return this->startup();
        break;
      case PLACE_IN_REACTOR:
        return this->placeReactor();
        break;
      case GRAB_ROD:
        return this->grabRod();
        break;

      default: 
        Serial.println("Default case in RobotController::execute(action)");
        break;
    }
  }

  return NOT_DONE_YET;
}

/**
 * @brief Macro Action for startup
 * @return 1 for DONE, 0 for NOT_DONE_YET
 */
int RobotController::startup()
{
  static int current_action = 0; //Stores the current action
  static Action action_seq[] = //This is the sequence of actions to complete
  {
    Action(MOVE_GRIPPER, MOVE_UP),
    Action(WAIT, 1000),
    Action(GRIPPER, OPEN),
    Action(TURN_GRIPPER, VERTICAL),
    Action(MOVE_FORWARD, -1)
  };

  current_action += this->execute(action_seq[current_action]); //Moves on when action is done

  //is the last action?
  if (current_action == (sizeof(action_seq) / sizeof(Action)))
  { //if YES
    current_action = 0;
    return DONE;
  }
  return NOT_DONE_YET;

}
/**
 * @brief Macro Action for Grabbing the rod
 * @return 1 for DONE, 0 for NOT_DONE_YET
 */
int RobotController::grabRod()
{
  static int current_action = 0;
  static Action action_seq[] =
  {
    Action(MOVE_GRIPPER, MOVE_DOWN),
    Action(WAIT, 1000),
    Action(GRIPPER, CLOSE),
    Action(WAIT, 1000),
    Action(SET_ALARM, 1),
    Action(MOVE_GRIPPER, MOVE_UP),
    Action(WAIT, 2000),
    Action(TURN_GRIPPER, HORIZONTAL),
  };

  current_action += this->execute(action_seq[current_action]);

  //is the last action?
  if (current_action == (sizeof(action_seq) / sizeof(Action)))
  {
    current_action = 0;
    return DONE;
  }
  return NOT_DONE_YET;

}
/**
 * @brief Macro Action for moving from reactor to storage
 * @return 1 for DONE, 0 for NOT_DONE_YET
 */
int RobotController::reactor2storage()
{
  static bool new_move = true;
  static int current_action = 0;

  static Action action_seq[] =
  {
    Action(MOVE_BACKWARD, -1),//to be decided
    Action(WAIT, 250),
    Action(TURN, RIGHT),//to be decided
    Action(WAIT, 250),
    Action(MOVE_FORWARD, -1, DEFAULT_SPEED )
  };

  if (new_move)
  {
    //decide
    int i = 0;

    //CONSIDER BACKWARD MOVMENT
    if (goal_reactor == 1) //Determines which tube to go to and sets the number of lines and direction to turn
    {
      for (i = 0; i < 4; i++)
        if (!storageTube.tube[i]) break;

      action_seq[0].n_line_crossings = i + 1;
      action_seq[2].direction = RIGHT;
    } else if (goal_reactor == 2)
    {
      for (i = 3; i >= 0; i--)
        if (!storageTube.tube[i]) break;

      action_seq[0].n_line_crossings = 4 - i;
      action_seq[2].direction = LEFT;
    }

    my_position = i;

    new_move = false;
    current_action = 0;
  }


  current_action += this->execute(action_seq[current_action]);

  //is the last action?
  if (current_action == (sizeof(action_seq) / sizeof(Action)))
  {
    current_action = 0;
    new_move = true;
    return DONE;
  }

  return NOT_DONE_YET;
}

/**
 * @brief Macro Action for moving from the storage to supply tube
 * @return 1 for DONE, 0 for NOT_DONE_YET
 */
int RobotController::storage2supply()
{
  static bool new_move = true;
  static int current_action = 0;

  static Action action_seq[] =
  {
    Action(MOVE_BACKWARD, 1, DEFAULT_SPEED),//return to center
    Action(WAIT, 250),
    Action(TURN, LEFT),//to be decided
    Action(WAIT, 250),
    Action(MOVE_FORWARD, 0, DEFAULT_SPEED),//to be decided
    Action(WAIT, 250),
    Action(TURN, LEFT),//to be decided
    Action(WAIT, 250),
    Action(MOVE_FORWARD, -1, DEFAULT_SPEED)
  };

  if (new_move)
  {
    //decide
    int i = 0;

    if (goal_reactor == 1)
    {
      for (i = 0; i < 4; i++)
        if (supplyTube.tube[i]) break;
    } else if (goal_reactor == 2)
    {
      for (i = 3; i >= 0; i--)
        if (supplyTube.tube[i]) break;
    }

    if (i <= my_position)
    {
      action_seq[2].direction = LEFT;
      action_seq[6].direction = LEFT;
    } else
    {
      action_seq[2].direction = RIGHT;
      action_seq[6].direction = RIGHT;
    }

    action_seq[4].n_line_crossings = abs(my_position - i);

    my_position = i;
    new_move = false;
    current_action = 0;
  }

  current_action += this->execute(action_seq[current_action]);

  //is the last action?
  if (current_action == (sizeof(action_seq) / sizeof(Action)))
  {
    current_action = 0;
    new_move = true;
    return DONE;
  }
  return NOT_DONE_YET;
}
/**
 * @brief Macro Action for supply to reactor
 * @return 1 for DONE, 0 for NOT_DONE_YET
 */
int RobotController::supply2reactor()
{
  static int current_action = 0;

  Action action_seq[] =
  {
    Action(MOVE_BACKWARD, 1, DEFAULT_SPEED),//return to center
    Action(WAIT, 250),
    Action(TURN, (goal_reactor == 1) ? RIGHT : LEFT),
    Action(WAIT, 250),
    Action(MOVE_FORWARD, -1, DEFAULT_SPEED),//to be decided
  };

  current_action += this->execute(action_seq[current_action]);

  //is the last action?
  if (current_action == (sizeof(action_seq) / sizeof(Action)))
  {
    current_action = 0;
    return DONE;
  }
  return NOT_DONE_YET;
}
/**
 * @brief Prints the tubes so that we can debug Bluetooth
 */
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
/**
 * @brief Macro Action for moving from reactor 1 to reactor 2
 * @return 1 for DONE, 0 for NOT_DONE_YET
 */
int RobotController::reactor2reactor() {
  static int current_action = 0;

  static Action action_seq[] =
  {
    Action(MOVE_GRIPPER, MOVE_UP),
    Action(MOVE_BACKWARD, 1, DEFAULT_SPEED),//return to center
    Action(WAIT, 250),
    Action(TURN, LEFT),
    Action(WAIT, 250),
    Action(TURN, LEFT),
    Action(WAIT, 250),
    Action(MOVE_FORWARD, -1, DEFAULT_SPEED),

  };

  current_action += this->execute(action_seq[current_action]);

  //is the last action?
  if (current_action == (sizeof(action_seq) / sizeof(Action)))
  {
    current_action = 0;
    this->goal_reactor = 2;
    return DONE;
  }
  return NOT_DONE_YET;
}
/**
 * @brief Macro Action for placing the rod in the reactor
 * @return 1 for DONE, 0 for NOT_DONE_YET
 */
int RobotController::placeReactor() {
  static int current_action = 0;

  static Action action_seq[] =
  {
    Action(TURN_GRIPPER, SPECIAL_VERT),
    Action(WAIT, 500),
    Action(MOVE_GRIPPER, MOVE_DOWN),
    Action(SET_ALARM, 0),
    Action(WAIT, 500),
    Action(GRIPPER, OPEN),
    Action(WAIT, 500),
    Action(MOVE_GRIPPER, MOVE_UP),

    Action(WAIT, 2000)


  };

  current_action += this->execute(action_seq[current_action]);

  //is the last action?
  if (current_action == (sizeof(action_seq) / sizeof(Action)))
  {
    current_action = 0;
    return DONE;
  }
  return NOT_DONE_YET;
}
/**
 * @brief This is the bluetooth update function
 * @details This is a non blocking and non ISR based incremental function
 * 
 * When it is called, it ALWAYS updates the information held with what it reads from the packets if packets are available
 * Then, depending on what time it is, it sends the status, heartbeat, or raditaion alarm packets
 * The parameter(s) for the packets are pulled from private variables held in this class 
 * 
 */
void RobotController::update()
{
  static unsigned int last_hb_time = millis();
  static unsigned int last_update_time = millis();
  static unsigned int last_rad_alarm_time = millis();

  bluetooth.update();

  unsigned int current_time = millis();

  if ((current_time - last_hb_time) > HEARTBEAT_PERIOD)
  {
    bluetooth.sendHB();
    Serial.println("Send HB");
    last_hb_time = current_time;
  }
  if ((current_time - last_update_time) > SEND_STATUS_PERIOD)
  {
    bluetooth.sendStatus(this->moveStat, this->gripStat, this->opStat);
    last_update_time = current_time;
  }
  if ((current_time - last_rad_alarm_time) > RADIATION_ALARM_PERIOD)
  {
    bluetooth.sendRadiation(this->radLevel);
    last_rad_alarm_time = current_time;
  }
}
/**
 * @brief Sets the radiatin alarms and also sends the signal to the UNO to trigger the visible alarm
 * 
 * @param level_to_set 0 for no rad, 1 for low, 2 for high, and 3 for celebration 
 * NOTE: Celebration is only to show the visible flag, not intended to happen when field needs valid packets
 * @return only returns done for sequencing. No way to fail
 */
int RobotController::setAlarm(int level_to_set) {
  this->radLevel = level_to_set;
  digitalWrite(alarm_pin_low, HIGH);
  digitalWrite(alarm_pin_high, HIGH);
  if (level_to_set == 1) {
    digitalWrite(alarm_pin_low, LOW);
  } else if (level_to_set == 2) {
    digitalWrite(alarm_pin_high, LOW);
  } else if (level_to_set == 3) {
    digitalWrite(alarm_pin_low, LOW);
    digitalWrite(alarm_pin_high, LOW);
  }
  return DONE;
}
/**
 * @brief Sets the alarm pins 
 * 
 * @param pin_number_low The low alarm pin
 * @param pin_number_high The high alarm pin
 */
void RobotController::setAlarmPins(int pin_number_low, int pin_number_high)
{
  alarm_pin_low = pin_number_low;
  alarm_pin_high = pin_number_high;
  pinMode(pin_number_low, OUTPUT);
  pinMode(pin_number_high, OUTPUT);
  digitalWrite(pin_number_low, HIGH);
  digitalWrite(pin_number_high, HIGH);
}
