
#include "PidController.h"
#include "Arduino.h"

PidController::PidController()
{
	this->kp = 1;
	this->kd = 0;
	this->ki = 0;
	this->setLimits(-1023, 1023);//default values
	this->reset();
}

PidController::PidController(double Kp, double Ki, double Kd)
{//TODO: check the limits
	this->setConstants(Kp, Ki, Kd);
}

double PidController::calc(double target, double sensor_value)
{
	error = target - sensor_value;
	sum += error;
	
	now = millis();
	dt = now-last_time;
	
	double output = kp*error + kd*(error-last_error)/dt + ki*sum*dt;
	
	output = constrain(output, min_output, max_output);
	
	last_error = error;
	last_time = now;
	
	return output;
}
  
void PidController::reset()
{
	last_error = 0;
	last_time = millis();
	sum = 0;
}

void PidController::setLimits(double min, double max)
{//TODO: check values
	min_output = min;
	max_output = max;
}

void PidController::setConstants(double Kp, double Ki, double Kd)
{
	this->kp = Kp;
	this->kp = Ki;
	this->kp = Kd;
}
