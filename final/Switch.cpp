#include "Arduino.h"
#include "Switch.h"

Switch::Switch()
{
	//do anything
}
/**
 * @brief Sets that switches type and which pin it uses
 * 
 * @param number The pin it's connected to
 * @param type Whether it needs an internal pullup or not
 */
Switch::Switch(int number, int type)
{
	this->setPin(number, type);
}


/**
 * @brief Attaches the pin number and enables the pullup
 * 
 * @param pin_number Which pin it uses
 * @param pull_type whether it needs a pullup resistor or not
 */
void Switch::setPin(int pin_number, int pull_type)
{
	pin = pin_number;
	if(pull_type == INTERNAL_PULL_UP)
		pinMode(pin, INPUT_PULLUP);
	else
		pinMode(pin, INPUT);
}


/**
 * @brief Returns a bool for if it has been pressed ot not
 * @return true for yes, false for not
 */
bool Switch::isPressed()
{
	return !digitalRead(pin);//just for pull-up for now
}


/**
 * @brief Blocking statement for waiting until a switch is pressed
 * 
 * @param int How long to wait
 * @return true for waiting, false for if it is complete
 */
bool Switch::waitOn(unsigned int how_long)
{
	unsigned int last_time = millis();//start_time at this point
  
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


/**
 * @brief The opposite of WaitOn
 * 
 * @param how_long how long to wait
 * @return The reverse of WaitON
 */
bool Switch::waitOff(unsigned int how_long)
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
/**
 * @brief Waits for the state to change
 * 
 * @param how_long how long to wait before looking 
 * @return true for not done, false for success
 */
bool Switch::waitChange(unsigned int how_long)
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

