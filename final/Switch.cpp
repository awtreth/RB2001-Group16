#include "Arduino.h"
#include "Switch.h"

Switch::Switch()
{
	//do anything
}

Switch::Switch(int number, int type)
{
	
}

void Switch::setPin(int pin_number, int pull_type)
{
  pin = pin_number;
  if(pull_type == INTERNAL_PULL_UP)
	  pinMode(pin, INPUT_PULLUP);
  else
    pinMode(pin, INPUT);
}

bool Switch::isPressed()
{
	return !digitalRead(pin);//just for pull-up
}

//FORGET THESE FUNCTIONS
/*bool Switch::waitOn(int how_long)
{
	//TODO
	return false;
}

bool Switch::waitOff(int how_long)
{
	//TODO
	return false;
}

bool Switch::waitChange(int how_long)
{
	//TODO
	return false;
}

void Switch::setPollingPeriod(int time)
{
	
}*/
