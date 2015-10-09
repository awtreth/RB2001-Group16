#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class Potentiometer
{
	private:

	int pin;
	int ref;
	int last_pos;
	int last_speed;
	int sample_time;
	//int dir;

	public:
	
	Potentiometer();
	Potentiometer(int pin_number);
	
	void attachPin(int pin_number);
	void setRef(int new_ref);
	
	int read();
	int get();
	
	void setTimeSample(int time_sample);
	
	//int getSpeed();
	//int readSpeed();
	
	//void reverse();
};

#endif
