#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

class PidController
{

  public:
	
	PidController();
	PidController(double Kp, double Ki, double Kd);

	double calc(double target, double sensor_value);
  
	void reset();
  
	void setConstants(double Kp, double Ki, double Kd);
  
	void setLimits(double min, double max);
  private:
	
	double kp, ki, kd;

	double sum;
	double last_time;
	double last_error;
	double max_output;
	double min_output;
	
	
	double error;
	double output;
	double dt;
	double now;
};

#endif

