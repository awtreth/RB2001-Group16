#ifndef DRIVE_TRAIN_H
#define DRIVE_TRAIN_H

#include "Arduino.h"
#include "LineSensor.h"
#include "Switch.h"
#include "PidController.h"

#include <Servo.h> //it has to be included in the main .ino file too

#define DEFAULT_SPEED 		45	///< 0-90

/**
 * Right sensor usually turns faster than the left one.
 * This factor is proportional to the level of compensation (how much faster
 * to turn the left motor when we want to turn both equally)
 */
#define MOTOR_COMPENSATION 	.1

///To index the LineSensor array in DriveTrain
enum LineSensorIndex{LEFT_LS, RIGHT_LS, RIGHT_SIDE_LS, LEFT_SIDE_LS, N_LINE_SENSORS};

///Arguments for DriveTrain::turn(TurnDirection direction)
enum TurnDirection{LEFT, RIGHT, TURN_180};

/**
 * This class provide functions to interact more easily with the drive_train
 * 
 * It is designed specifically for RBE 2001 final project, alghough some functions
 * are quite generic.
 * 
 * It is considered that the driveTrain has:
	 * 2 ServoMotors: skid steer configuration. The servos have to be placed in symetric positions. So, sendind the same input signal for both motors, the motors will turn in opposite directions (one will try to move the drive train forward and the other will try to move the drive train backward)
	 * 
	 * 4 LineSensors: 2 for line tracking in the middle, 1 in the back and other in one side of the robot aligned with the centered line tracking sensors;
	 * 
	 * 2 Stopper Switches: 1 to sense when the robot hits the reactor and other to sense when it hits the wall of supply or storage areas
 * 
 */ 
class DriveTrain
{
	
	public:
	
	DriveTrain(){}//Not used
	
	DriveTrain(int left_motor_pin, int right_motor_pin);///< Set the pins of the motors
	
	//Attach Functions
	void attachMotors(int left_motor_pin, int right_motor_pin);
	void attachLnSensors(int left_pin, int right_pin, int side_pin = 0, int back_pin = 0);
	void attachStoppers(int reactor_stopper_pin, int wall_stopper_pin);
	
	
	/**GENERIC FUNCTIONS
	 * 
	 * Without feedback of LineSensors neither Switches
	*/
	
	/** Drive the motors separatedly
	 * 
	 * @param left_value signal sent to right Servo (Arduino Library). It is proportional to the torque and the constraint range is -90~90. Positive values make it turns in the direction that makes the drive train move forward 
	 * @param right_value signal sent to right Servo (Arduino Library). It is proportional to the torque and the constraint range is -90~90. Positive values make it turns in the direction that makes the drive train move forward 
	 */
	void drive(int left_value, int right_value);

	///Both motors stop
	void stop();
  
	/**Send same value to the motors. Move forward without LineSensors feedback
	 * 
	 * @param speed Range:0~90
	 * @see drive()
	 */
	void driveEqual(int speed = DEFAULT_SPEED);
	
	/**The robot turns around itself 
	 * 
	 * It sends opositte values for drive() function
	 * 
	 * @param speed Range:-90~90. Positive - Turn Right; Negative - Turn Left;
	 * @see drive()
	 */
	void turn(int speed);
	
	/**The robot turns around itself given the Turn Direction and speed 
	 * 
	 * @param dir RIGHT or LEFT
	 * @param speed Range:0~90
	 * @see drive()
	 */
	void turn(TurnDirection dir, int speed = DEFAULT_SPEED*2/3);
	//Especific versions of turn(TurnDirection, int)
	void turnLeft(int speed = DEFAULT_SPEED*2/3);
	void turnRight(int speed = DEFAULT_SPEED*2/3);
	
	
	/**GENERIC FUNCTIONS
	 * 
	 * With feedback of LineSensors neither Switches
	 * 
	 * All these functions return DONE (1) or NOT_DONE_YET (0)
	 * 
	 * @see util.h
	 * 
	 * It is designed to use State Machines
	 * 
	 * Actually, these functions would fit better in RobotController class. We prefered to keep them here to save code there
	 *
	 * @see RobotController
	*/
	
	
	/**PidController for for Line Tracking
	 * 
	 * Performs pid control for line tracking task
	 * 
	 * For now it is in public scope. The user has to set it before using the methods:
	 * int DriveTrain::moveStraight(int,int);
	 * int DriveTrain::moveForward(int, int);
	 * intDriveTrain::moveBackward(int,int);
	 * 
	 * @see PidController 
	 * @see moveStraight()
	 * @see moveForward()
	 * @see moveBackward()
	 */
	 PidController pid;
	
	/** Turn until an specified LineSensor (back or side) detects a line crossing
	 * 
	 * Turns in default speed
	 * 
	 * @param dir RIGHT or LEFT
	 * 
	 * 
	 */
	int turn90(TurnDirection dir);
	int turn90Left();
	int turn90Right();
	
	/** MoveForward performing LineTracking
	 * 
	 * The robot stops when it pass through n_line_crossings or when it hits a wall or a reactor
	 * 
	 * @param n_line_crossings <=0 means that the robot will not count line_crossings
	 * @param speed 0~90
	 * 
	 * n_line_crossings == 0, the robot does nothings
	 */
	int moveForward(int n_line_crossings = -1, int speed = DEFAULT_SPEED);
	/**Same as moveForward(), but backwards
	 * @see moveForward()
	*/
	int moveBackward(int n_line_crossings = -1, int speed = DEFAULT_SPEED);
	/** Generic Function for LineTracking
	 * 
	 * @param n_line_crossings
	 * @param speed -90~90. Positive: Forward; Negative: Backward
	 * 
	 * @see moveBackward()
	 * @see moveForward()
	 */ 
	int moveStraight(int n_line_crossings = -1, int speed = DEFAULT_SPEED);


	/**Indexed by LineSensorIndex
	 * 
	 * @see LineSensor Class
	 */
	LineSensor ln_sensor[N_LINE_SENSORS];
	
	private:
	
	Servo left_motor;
	Servo right_motor;
	
	Switch reactor_stopper;
	Switch wall_stopper;

};

#endif
