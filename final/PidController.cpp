#include "PidController.h"
#include "Arduino.h"

#define DEFAULT_SAMPLE_TIME 75

PidController::PidController()
{//Set default values
	this->kp = 1;
	this->kd = 0;
	this->ki = 0;
	this->setLimits(-1023, 1023);
	this->setSampleTime(DEFAULT_SAMPLE_TIME);
	this->reset();
}
/**
 * @brief Initializes the PID controller with specified tunings
 * 
 * @param Kp The constant for Proportion
 * @param Ki The constant for Integral
 * @param Kd The constant for Derivative
 */
PidController::PidController(double Kp, double Ki, double Kd)
{
	this->setConstants(Kp, Ki, Kd);
	this->reset();
}
/**
 * @brief Calculates the PID with only the error given, not goal and current
 * 
 * @param error The error value calculated
 * @return the returned PID calc value
 */
double PidController::calc(double error)
{
  return this->calc(error, 0);
}
/**
 * @brief Calculates the PID value with the target and the reading
 * @details This is your standard run of the mill PID calculation
 *
 * @param target The value the PID is trying to reach
 * @param sensor_value The current value
 * 
 * @return The speed to write the motors to best achieve that target
 */
double PidController::calc(double target, double sensor_value)
{
	now = millis();//current_time
	dt = now - last_time;
	
	if(dt >= sample_time)//try to keep dt constant in each iteration
	{
		error = target - sensor_value; //calculates the error
		sum += error; //sums the error
		//The actual calculation		
		double output = kp*error + kd*(error-last_error)/dt + ki*sum*dt;
		
		output = constrain(output, min_output, max_output);//Constrains the output
		
		last_output = output; //stores the values to reference later
		last_error = error;
		last_time = now;
	}else
		return last_output;
	
	return output;
}
/**
 * @brief Resets the controller so as to not have old entries for a new calc
 */
void PidController::reset()
{
	last_error = 0;
	last_time = millis();
	sum = 0;
	last_output = 0;
}
/**
 * @brief Sets the limits for the output. -90 to 90 for our usage
 * NOTE: range is just the usual 0 to 180 but mapped a little more sensibly
 * 
 * @param min The minimum value
 * @param max The maximum value
 */
void PidController::setLimits(double min, double max)
{
	min_output = min;
	max_output = max;
}
/**
 * @brief Helper function to set comments
 * 
 * @param Kp The constant for Proportion
 * @param Ki The constant for Integral
 * @param Kd The constant for Derivative
 */
void PidController::setConstants(double Kp, double Ki, double Kd)
{
	this->kp = Kp;
	this->ki = Ki;
	this->kd = Kd;
}
/**
 * @brief Sets the objects value
 * 
 * @param stime The time to be stored
 */
void PidController::setSampleTime(int stime)//in ms
{
	this->sample_time = stime;
}
