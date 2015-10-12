#include "LineSensor.h"

#define BLACK_THRESHOLD 700//Values greater than this are considered black 
#define WHITE_THRESHOLD 100//Values smaller than this are considered white

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
		
	return (value > BLACK_THRESHOLD);
}

bool LineSensor::isWhite(bool take_last)
{
	int value = 0;
	
	if(take_last)
		value = last_read;
	else
		value = this->read();
		
	return (value < WHITE_THRESHOLD);
}

int LineSensor::get()
{
	return last_read;
}
