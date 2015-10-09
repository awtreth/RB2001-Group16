#include "Arduino.h"
#include "Potentiometer.h"

Potentiometer::Potentiometer()
{
	this->ref = 0;
	this->last_pos = 0;
	this->last_speed = 0;
	this->setTimeSample(75);
}

Potentiometer::Potentiometer(int pin_number)
{
	this->attachPin(pin_number);
	this->ref = 0;
	this->last_pos = 0;
	this->last_speed = 0;
	this->setTimeSample(75);
}

void Potentiometer::attachPin(int pin_number)
{
	pin = pin_number;
}

void Potentiometer::setRef(int new_ref)
{
	ref = new_ref;
}

int Potentiometer::read()
{
	last_pos = analogRead(pin);
	return last_pos;
}

int Potentiometer::get()
{
	return last_pos;
}

void Potentiometer::setTimeSample(int time_sample)
{
	this->sample_time = time_sample;
}

/*int getSpeed()
{
	return last_speed;
}

int readSpeed()
{
	last_pos - 
}*/
