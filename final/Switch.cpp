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
	return !digitalRead(pin);//just for pull-up
}

bool Switch::waitOn(int how_long)
{
  long int last_time = millis();
  long int count = 0;
	while(!this->isPressed())
  {
    if(how_long)
    {
      if(((millis()-last_time)>how_long)) return false;
      last_time = millis();
    }
    delay(50);
  }
	return true;
}

bool Switch::waitOff(int how_long)
{
	long int last_time = millis();
  long int count = 0;
  while(this->isPressed())
  {
    if(how_long)
    {
      if(((millis()-last_time)>how_long)) return false;
      last_time = millis();
    }
    delay(50);
  }
  return true;
}

bool Switch::waitChange(int how_long)
{
  bool state = this->isPressed();
	long int last_time = millis();
  long int count = 0;
  
  while(this->isPressed() == state)
  {
    if(how_long)
    {
      if(((millis()-last_time)>how_long)) return false;
      last_time = millis();
    }
    delay(50);
  }
  return true;
}

