#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "Arduino.h"
#include "LineSensor.h"
#include "Switch.h"
#include "PidController.h"

#include <Servo.h> //it has to be included in the main .ino file

#define DEFAULT_SPEED 		45
#define MOTOR_COMPENSATION 	.12

enum LineSensorIndex{LEFT_LS, RIGHT_LS, SIDE_LS, BACK_LS, N_LINE_SENSORS};
enum TurnDirection{LEFT_TURN, RIGHT_TURN, TURN_180};

class DriveTrain
{
	
	public:
	
	DriveTrain(){}//may can set default values for pins
	
	//This constructor didn't work at global scope (I don't know why)
	DriveTrain(int left_motor_pin, int right_motor_pin);
	
	void attachMotors(int left_motor_pin, int right_motor_pin);
	void attachLnSensors(int left_pin, int right_pin, int side_pin, int back_pin = 0);//at first we'll try without back_pin
	void attachStopper(int stopper_pin);//at first we'll try without back_pin
	
	void drive(int left_value, int right_value);

	void stop();
  
	void driveEqual(int speed = DEFAULT_SPEED);
	
	void turn(int speed);
	void turnLeft(int speed = DEFAULT_SPEED/2);
	void turnRight(int speed = DEFAULT_SPEED/2);
	
	//SMART MOVMENTS
	
  PidController pid;
  
	void resume();
	
	//the next functions return DONE(=1) or NOT_DONE_YET(=0)
	//constants defined in "util.h"
	int turn90(TurnDirection dir);
	int turn90Left();
	int turn90Right();
	
	int moveForward(int n_line_crossings = 0, int speed = DEFAULT_SPEED);
	int moveBackward(int n_line_crossings = 0, int speed = DEFAULT_SPEED);

	private:
	
	Servo left_motor;
	Servo right_motor;
	
	LineSensor ln_sensor[N_LINE_SENSORS];
	
	Switch stopper;

	bool stop_flag;
	//I think we'll need more flags
};

#endif
