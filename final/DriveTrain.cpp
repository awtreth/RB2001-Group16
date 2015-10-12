#include "Arduino.h"
#include "DriveTrain.h"
#include "util.h"

//This constructor didn't work (very weird)
DriveTrain::DriveTrain(int left_motor_pin, int right_motor_pin)
{
  this->attachMotors(left_motor_pin, right_motor_pin);
  this->stop();
}

void DriveTrain::attachMotors(int left_motor_pin, int right_motor_pin)
{
  this->left_motor.attach(left_motor_pin); 
  this->right_motor.attach(right_motor_pin);
}

void DriveTrain::attachLnSensors(int left_pin, int right_pin, int side_pin, int back_pin)
{
  ln_sensor[LEFT_LS].attachPin(left_pin);
  ln_sensor[RIGHT_LS].attachPin(right_pin);
  ln_sensor[SIDE_LS].attachPin(side_pin);
  ln_sensor[BACK_LS].attachPin(back_pin);
}

void DriveTrain::attachStoppers(int reactor_stopper_pin, int wall_stopper_pin)
{
  reactor_stopper.setPin(reactor_stopper_pin);
  wall_stopper.setPin(wall_stopper_pin);
}


void DriveTrain::stop()
{
  this->drive(0, 0);
}

void DriveTrain::drive(int left_value, int right_value)//-90~90
{

  left_value = constrain(left_value, -90, 90);
  right_value = constrain(right_value, -90, 90);

  right_value *= (1. - MOTOR_COMPENSATION);
  left_value *= (1. + MOTOR_COMPENSATION);

  left_value = map(left_value, -90, 90, 0, 180);
  right_value = map(right_value, -90, 90, 180, 0);

  this->right_motor.write(right_value);
  this->left_motor.write(left_value);
}

void DriveTrain::driveEqual(int speed)//-90~90
{
  this->drive(speed, speed);
}
void DriveTrain::turnLeft(int speed)//0-90
{
  speed = constrain(speed, 0, 90);
  this->turn(-speed);
}

void DriveTrain::turnRight(int speed)//0-90
{
  speed = constrain(speed, 0, 90);
  this->turn(speed);
}

void DriveTrain::turn(int speed)//-90~90
{
  this->drive(speed, -speed);
}

void DriveTrain::turn(TurnDirection dir, int speed)//-90~90
{
  if (dir == LEFT)
    this->turnLeft(speed);
  else
    this->turnRight(speed);
}


//SMART MOVEMENTS

int DriveTrain::turn90(TurnDirection dir)
{
    //Static variable are initialized just one time, at the first call
  static bool came_from_white = false;
  static bool already_turn = false;
  
  long int last_time;
  
  LineSensorIndex turn_sensor;

  if (dir == RIGHT) {
    turn_sensor = BACK_LS; //TODO: put turn_sensor as an argument
  } else if (dir == LEFT) {
    turn_sensor = SIDE_LS;
  }
  
  //This condition avoid not necessary turn commands
  if (!already_turn)
  {//Since this function is supposed to be called multiple times (in a loop). It just need to send the turn command one time
    last_time = millis();
    this->turn(dir);
    already_turn = true;
  }

    //this waiting was necessary, because sometimes the sensor starts facing the white surface in the wrong side of the line (opposite to the turn direction). In this case, the first line crossing the robot senses is the wrong line (where it was suppose to be facing at the beggining). So, the sulution is to start turning for a while and then verify if it's black (white first)
  if (!came_from_white && (millis()-last_time > 500))
  {
    //It waits the turn_sensor to sense white to start looking for black state (when it hits a crossing line)
    //it is necessary, because the sensor can start facing a black line
    if (ln_sensor[turn_sensor].isWhite())
      came_from_white = true;
  }

  if (came_from_white)
  {//It just start checking if the sensor is black when it has already sensed white once
    if (ln_sensor[turn_sensor].isBlack())
    {
      this->stop();
      came_from_white = false;
      already_turn = false;
      return DONE;
    }
  }

  return NOT_DONE_YET;
}

int DriveTrain::turn90Left()
{
  return turn90(LEFT);
}

int DriveTrain::turn90Right()
{
  return turn90(RIGHT);
}

//this function use similiar techinics as the used in DriveTrain::turn90() function
int DriveTrain::moveStraight(int n_line_crossings, int speed)
{
    //Static variable are initialized just one time, at the first call
  static bool new_move = true;
  static int missing_lines = n_line_crossings;
  static bool came_from_white = false;

    //This condition control polling
  if (new_move)
  {//Since this function is supposed to be called multiple times (in a loop). It has to reset the line counting at the first call
    if (n_line_crossings == 0) n_line_crossings = -1;
    missing_lines = n_line_crossings;
    new_move = false;
  }

  /*Another approach

  ln_sensor[RIGHT_LS].read();
  ln_sensor[LEFT_LS].read();

  if(missing_lines == 0  || stopper.isPressed(true))
  {
    this->stop();
    new_move = true;
    return DONE;
  }

  int signal_control = pid.calc(ln_sensor[RIGHT_LS].get()-ln_sensor[LEFT_LS].gets());
  */

  if (speed >= 0 )
    pid.positiveConstants();
  else
    pid.negativeConstants();

  int value = pid.calc(ln_sensor[RIGHT_LS].read() - ln_sensor[LEFT_LS].read());

    //accelerate one and desaccelerate the other so that it turns
  this->drive(speed + value, speed - value);

  //FIXME: the next 2 if statements are repeated in turn90. Maybe we can create a method for this
  if (!came_from_white)
  {
    if (ln_sensor[SIDE_LS].isWhite())
      came_from_white = true;
  }

  if (came_from_white)
  {
    if (ln_sensor[SIDE_LS].isBlack())
    {
      came_from_white = false;
      missing_lines--;
    }
  }

  if (missing_lines == 0  || ((wall_stopper.isPressed() || reactor_stopper.isPressed()) && (speed > 0)))
  {
    this->stop();
    new_move = true;
    return DONE;
  }

  return NOT_DONE_YET;
}

int DriveTrain::moveForward(int n_line_crossings, int speed)
{
  return this->moveStraight(n_line_crossings, speed);
}

int DriveTrain::moveBackward(int n_line_crossings, int speed)
{
  return this->moveStraight(n_line_crossings, -speed);
}
