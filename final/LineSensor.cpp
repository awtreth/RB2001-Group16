#include "LineSensor.h"

#define BLACK_REF 700
#define WHITE_REF 100

#include "Arduino.h"

LineSensor::LineSensor()
{
	//do anything
	this->pin = A0;
	this->last_read =0;
}

LineSensor::LineSensor(int pin_number)
{
	this->attachPin(pin_number);
}
	
void LineSensor::attachPin(int pin_number)
{
	this->pin = pin_number;
}	
	
int LineSensor::read()
{
	this->last_read = analogRead(this->pin);
	return last_read;
}

bool LineSensor::isBlack(bool take_last)
{
	int value = 0;
	if(take_last)
		value = last_read;
	else
		value = this->read();
		
	return (value > BLACK_REF);
}

bool LineSensor::isWhite(bool take_last)
{
	int value = 0;
	if(take_last)
		value = last_read;
	else
		value = this->read();
		
	return (value < WHITE_REF);
}

int LineSensor::get()
{
	return last_read;
}
