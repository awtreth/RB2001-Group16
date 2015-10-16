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
/**
 * @brief Attaches the line sensor to the appropriate pin via initialization
 * 
 * @param pin_number Which Pin to attach
 */
LineSensor::LineSensor(int pin_number)
{
	this->attachPin(pin_number);
}
/**
 * @brief The Helper function to attach the pin
 * 
 * @param pin_number The pin to attach
 */
void LineSensor::attachPin(int pin_number)
{
	this->pin = pin_number;
}	
/**
 * @brief gives the value of the line sensor 
 * @return The analog value of the line sensor at that moment
 */
int LineSensor::read()
{
	this->last_read = analogRead(this->pin);
	return last_read;
}
/**
 * @brief Returns if it is on black or not
 * 
 * @param take_last bool for if we want to read the current or previous value
 * @return true if on black or false if on white
 */
bool LineSensor::isBlack(bool take_last)
{
	int value = 0;
	
	if(take_last)
		value = last_read;
	else
		value = this->read();
		
	return (value > BLACK_THRESHOLD);
}
/**
 * @brief Returns if it is on white or not
 * 
 * @param take_last bool for if we want to read the current or previous value
 * @return true if on white or false if on black
 */
bool LineSensor::isWhite(bool take_last)
{
	int value = 0;
	
	if(take_last)
		value = last_read;
	else
		value = this->read();
		
	return (value < WHITE_THRESHOLD);
}
/**
 * @brief returns the last reading
 * @return The value of last_read
 */
int LineSensor::get()
{
	return last_read;
}
