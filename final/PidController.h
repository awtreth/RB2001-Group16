#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "Arduino.h"

//based on the provided PID_v1 library
/** General class that compute PID control
 */
class PidController
{

  public:
	PidController();///not used
	PidController(double Kp, double Ki, double Kd);///sets Pid constants at the construction

	void setTime(int dt_ms);///Set default sample time, in milliseconds

	/** Calculate the signal control
	 * 
	 * error = target - measured_value
	 * 
	 * sum = sum(error) along time
	 * 
	 * output = kp*error + kd*(error-last_error)/dt + ki*sum*dt;
	 * 
	 * \param target Desired value to be tracked
	 * \param sensor_value Measured value to be compared with target
	 * \return signal control
	 */
	double calc(double target, double sensor_value);
	
	/** Calculate the signal control directly based on the error signal
	 * @see calc(double target, double sensor_value)
	 */
	double calc(double error);
  
	/**Reset internal variables
	 * good when you have to turn the PID off or on.
	 * Also good to avoid unstable behavior due integral part
	*/ 
	void reset();
  
	void setConstants(double Kp, double Ki, double Kd);
  
	///Limits for calc() method output (control_signal)
	void setLimits(double min, double max);
	
	///Set the period that the PID will try to compute
	void setSampleTime(int stime);//in ms

  
	void positiveConstants(){kp = abs(kp); ki = abs(ki); kd = abs(kd);}
	void negativeConstants(){kp = -abs(kp); ki = -abs(ki); kd = -abs(kd);}
  
  private:
	///PID constants
	double kp, ki, kd;
	
	double sum;///< summation of error along the time
	double last_time;
	double last_error;
	
	double max_output;
	double min_output;
	
	int sample_time;
	
	///Variables used inside calc() function
	double error;
	double output;
	double dt;
	double now;///< current_time
	double last_output;
};

#endif

