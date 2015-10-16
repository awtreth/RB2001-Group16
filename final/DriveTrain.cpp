#include "Arduino.h"
#include "DriveTrain.h"
#include "util.h"
/** @brief Initializes the Drivetrain class
 *  @details Attaches the motors to their pins, and writes STOP to all of them
 * @param left_motor_pin the pin assignment of the left motor
 * @param right_motor_pin the pin assignment of the right motor
 */
DriveTrain::DriveTrain(int left_motor_pin, int right_motor_pin)
{
  this->attachMotors(left_motor_pin, right_motor_pin);
  this->stop();
}


/** @brief Attaches the motors to the appropriate pins
 * @param left_motor_pin the pin assignment of the left motor
 * @param right_motor_pin the pin assignment of the right motor
 */
void DriveTrain::attachMotors(int left_motor_pin, int right_motor_pin)
{
  this->left_motor.attach(left_motor_pin); 
  this->right_motor.attach(right_motor_pin);
}


/**
 * @brief Attaches the Line sensors to the appropriate pins
 * @details It attaches the line sensor and then adds the pin to the array for use of access later
 * 
 * @param left_pin the pin of the left line sensor
 * @param right_pin the pin of the right line sensor 
 * @param side_pin the pin of the side sensor 
 * @param back_pin the pin of the back line sensor
 */
void DriveTrain::attachLnSensors(int left_pin, int right_pin, int side_pin, int back_pin)
{
  ln_sensor[LEFT_LS].attachPin(left_pin); 
  ln_sensor[RIGHT_LS].attachPin(right_pin);
  ln_sensor[RIGHT_SIDE_LS].attachPin(side_pin);
  ln_sensor[LEFT_SIDE_LS].attachPin(back_pin);
}


/**
 * @brief Adds the Limit Switches
 * @details These are the front limit and bumper stop switches, they are added to pin's object
 * 
 * @param reactor_stopper_pin The pin of the limit switch
 * @param wall_stopper_pin The pin of the Bumper switch
 */
void DriveTrain::attachStoppers(int reactor_stopper_pin, int wall_stopper_pin)
{
  reactor_stopper.setPin(reactor_stopper_pin);
  wall_stopper.setPin(wall_stopper_pin);
}


/**
 * @brief Stops the motors
 */
void DriveTrain::stop()
{
  this->drive(0, 0);
}


/**
 * @brief Drives the motors to the set speed 
 * 
 * @param left_value The pin of the left motor
 * @param right_value The pin of the right motor
 */
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


/**
 * @brief Drives the motors at equal speeds 
 * 
 * @param speed The speed to be driven
 */
void DriveTrain::driveEqual(int speed)//-90~90
{
  this->drive(speed, speed);
}


/**
 * @brief Drives the motors to turn the robot left
 * @details This isn't an auto stopping command, This is the helper
 * 
 * @param speed The speed at which to rotate
 */
void DriveTrain::turnLeft(int speed)//0-90
{
  speed = constrain(speed, 0, 90);
  this->turn(-speed);
}


/**
 * @brief Drives the motors to turn the robot right
 * @details This isn't an auto stopping command, This is the helper
 * 
 * @param speed The speed at which to rotate
 */
void DriveTrain::turnRight(int speed)//0-90
{
  speed = constrain(speed, 0, 90);
  this->turn(speed);
}


/**
 * @brief turns the robot with the given speed
 * @details This is the helper function to the turnleft and turnright functions 
 * 
 * @param speed The speed to turn
 */
void DriveTrain::turn(int speed)//-90~90
{
  this->drive(speed, -speed);
}


/**
 * @brief another version of turn that uses the direction and positive speed instead of comparing + -
 * 
 * @param dir direction to turn
 * @param speed the speed to turn
 */
void DriveTrain::turn(TurnDirection dir, int speed)//-90~90
{
  if (dir == LEFT)
    this->turnLeft(speed);
  else
    this->turnRight(speed);
}


//SMART MOVEMENTS

/**
 * @brief turns in the given direction
 * @details This is a smart turn. It will turn in either direction until it senses the turn is complete
 * 
 * @param dir which direction it will turn
 * @return DONE for complete, NOT_DONT_YET if still turning 
 */
int DriveTrain::turn90(TurnDirection dir)
{
    //Static variable are initialized just one time, at the first call
  static bool came_from_white = false;
  static bool already_turn = false;
  static bool left_sensor = false;
  static bool right_sensor = false;
  
  static unsigned int last_time = millis();
  
  if (!came_from_white)
  {
    if (ln_sensor[RIGHT_SIDE_LS].isWhite())
      came_from_white = true;
  }

  
  //This condition avoid not necessary turn commands
  if (!already_turn)
  {//Since this function is supposed to be called multiple times (in a loop). It just need to send the turn command one time
    last_time = millis();
    this->turn(dir);
    already_turn = true;
  }

  if (came_from_white && (millis()-last_time > 2250))
  {//It just start checking if the sensor is black when it has already sensed white once
    if (!left_sensor && ln_sensor[LEFT_SIDE_LS].isBlack())
    {
      left_motor.write(90);//stop the motor
      left_sensor = true;
    }

    if (!right_sensor && ln_sensor[RIGHT_SIDE_LS].isBlack())
    {
      right_motor.write(90);//stop the motor
      right_sensor = true;
    }

    if(left_sensor && right_sensor)
    {
      already_turn = false;
      left_sensor = false;
      right_sensor = false;
      came_from_white = false;
      return DONE;
    }
  }

  return NOT_DONE_YET;
}


/**
 * @brief Smart Turn left 
 * 
 * @return DONE for complete, NOT_DONT_YET if still turning
 */
int DriveTrain::turn90Left()
{
  return turn90(LEFT);
}


/**
 * @brief Smart Turn Right 
 * 
 * @return DONE for complete, NOT_DONT_YET if still turning
 */
int DriveTrain::turn90Right()
{
  return turn90(RIGHT);
}

//
/**
 * @brief this function use similiar techinics as the used in DriveTrain::turn90() function
 * @details This drives forward with PID controlled line following until it crosses the correct number of lines
 * 
 * @param n_line_crossings How many lines to cross
 * @param speed The speed at which to travel 
 * 
 * @return DONE for complete, NOT_DONT_YET if still turning
 */
int DriveTrain::moveStraight(int n_line_crossings, int speed)
{
    //Static variable are initialized just one time, at the first call
  static bool new_move = true;
  static int missing_lines = n_line_crossings;
  static bool came_from_white = false;

    //This condition control polling
  if (new_move)
  {//Since this function is supposed to be called multiple times (in a loop). It has to reset the line counting at the first call
    if (n_line_crossings == 0) return DONE;
    missing_lines = n_line_crossings;
    new_move = false;
  }

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
    if (ln_sensor[RIGHT_SIDE_LS].isWhite())
      came_from_white = true;
  }

  if (came_from_white)
  {
    if (ln_sensor[RIGHT_SIDE_LS].isBlack())
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


/**
 * @brief Easier funtion to call to drive forward with absolute speed
 * 
 * @param n_line_crossings How many lines to follow
 * @param speed Abosute speed to travel
 * 
 * @return DONE for complete, NOT_DONT_YET if still turning
 */
int DriveTrain::moveForward(int n_line_crossings, int speed)
{
  return this->moveStraight(n_line_crossings, speed);
}


/**
 * @brief Easier funtion to call to drive backward with absolute speed
 * 
 * @param n_line_crossings How many lines to follow
 * @param speed Abosute speed to travel
 * 
 * @return DONE for complete, NOT_DONT_YET if still turning
 */
int DriveTrain::moveBackward(int n_line_crossings, int speed)
{
  return this->moveStraight(n_line_crossings, -speed);
}
