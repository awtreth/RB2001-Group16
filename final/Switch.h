#ifndef SWITCH_H
#define SWITCH_H

//maybe we can put this constants as enum inside the class
#define INTERNAL_PULL_UP 	0
#define EXTERNAL_PULL_UP				1
#define EXTERNAL_PULL_DOWN			2 //not implemented yet

class Switch
{
	private:

	//int polling_period;
  int pin;
  
	public:
	
	Switch();
	Switch(int pin_number, int pull_type = INTERNAL_PULL_UP);
	
	void setPin(int pin_number, int pull_type = INTERNAL_PULL_UP);
	bool isPressed();
	
	//FORGET THESE FUNCTIONS
	//#define DEFAULT_POLLING_PERIOD  50 //milliseconds
	//bool waitOn(int how_long = 0); //0 - forever
	//bool waitOff(int how_long = 0); //0 - forever
	//bool waitChange(int how_long = 0); //0 - forever
	
	//void setPollingPeriod(int time = DEFAULT_POLLING_PERIOD);
};

#endif
