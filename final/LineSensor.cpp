#include "LineSensor.h"

#define BLACK_REF 600 //TODO: calibrate it
#define WHITE_REF 100 //TODO: calibrate it

#include "Arduino.h"

LineSensor::LineSensor()
{
	//do anything
	this->pin = A0;
}

LineSensor::LineSensor(int pin_number)
{
	this->pin = pin_number;
}
	
int LineSensor::read()
{
	return analogRead(this->pin);
}

bool LineSensor::isBlack()
{
	return (this->read() > BLACK_REF);
}

bool LineSensor::isWhite()
{
	return (this->read() < WHITE_REF);
}

