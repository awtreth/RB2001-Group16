#include "Arduino.h"
#include "Switch.h"

Switch::Switch()
{
	//do anything
}

Switch::Switch(int number, int type)
{
	this->setPin(number, type);
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
	return !digitalRead(pin);//just for pull-up for now
}

bool Switch::waitOn(int how_long)
{
	long int last_time = millis();//start_time at this point
  
	//polling loop
	while(!this->isPressed())//while it is not pressed
	{
		if(how_long)//if how_long is not zero
		{
			if(((millis()-last_time)>how_long)) return false; //time_limit was reached
			last_time = millis();
		}
		delay(50);
	}
	
	return true;
}

bool Switch::waitOff(int how_long)
{
	long int last_time = millis();//start_time at this point
	
	//polling loop
	while(this->isPressed())//while it is pressed
	{
		if(how_long)//if how_long is not zero
		{
			if(((millis()-last_time)>how_long)) return false;//time_limit was reached
			last_time = millis();
		}
		
		delay(50);
	}
	
	return true;
}

bool Switch::waitChange(int how_long)
{
	bool state = this->isPressed();//store the state that the switch was when we called the function
	long int last_time = millis();//start_time at this point
  
	//polling loop
	while(this->isPressed() == state)//while the switch keeps at the same state
	{
		if(how_long)//if how_long is not zero
		{
			if(((millis()-last_time)>how_long)) return false;//time_limit was reached
			last_time = millis();
		}
		
		delay(50);
	}
	
	return true;
}

