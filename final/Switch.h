#ifndef SWITCH_H
#define SWITCH_H


/**
 * Possible values for Switch::setPin()
 * Set the type of pull resistor to avoid floating voltage on the
 * input pin
 */
#define INTERNAL_PULL_UP 	0
#define EXTERNAL_PULL_UP	1
#define EXTERNAL_PULL_DOWN	2 //not implemented yet

class Switch
{
	private:

	int pin;
  
	public:
	
	Switch();
	Switch(int pin_number, int pull_type = INTERNAL_PULL_UP);
	
	void setPin(int pin_number, int pull_type = INTERNAL_PULL_UP);
	
	/** Check if the switch is pressed
	 * @return true if it's pressed, false otherwise
	 */ 
	bool isPressed();
	
	/** Wait the button to be pressed
	 * 
	 * It will check if the switch is on for how_long milliseconds .
	 * The functions ends if the button is pressed or the set time is elapsed.
	 * 
	 * @param how_long Waiting time in milliseconds. It has to greater than 50 0 (it will wait only until the button is pressed)
	 * @return True if it was pressed. False if the set time has elapsed first
	 */
	 
	bool waitOn(unsigned int how_long = 0);
	
	/** Wait the button to be depressed
	 * 
	 * It will check if the switch is off for how_long milliseconds.
	 * The functions ends if the button is released or the set time is elapsed.
	 * 
	 * @param how_long Waiting time in milliseconds. It has to greater than 50 or 0 (it will wait only until the button is depressed)
	 * @return True if it was depressed. False if the set time has elapsed first
	 */
	bool waitOff(unsigned int how_long = 0); //0 - forever
	
	/** Wait for a change in button state
	 * 
	 * It will check if the switch changed (since the function was called) for how_long milliseconds.
	 * The functions ends if the button's state changes or the set time is elapsed.
	 * 
	 * @param how_long Waiting time in milliseconds. It has to greater than 50 or 0 (it will wait only until a change event)
	 * @return True if it has changed. False if the set time has elapsed first
	 */
	bool waitChange(unsigned int how_long = 0); //0 - forever
	
};

#endif
