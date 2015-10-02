#include "LineSensors.h"

#define BLACK_WHITE_LIMIT 600 //TODO: calibrate it

LineSensors::LineSensors()
{
	//do anything
}

LineSensors::LineSensors(int left_lf, int right_lf, int side, int back)
{
	this->setSensorsPins(int left_lf, int right_lf, int side, int back);
}
	
int LineSensors::getDiff()
{
	return (analogRead(right_pin)-analogRead(left_pin));
}

void LineSensors::setSensorsPins(int left_lf, int right_lf, int side, int back)
{
	this->left_pin = left_lf;
	this->right_pin = right_lf;
	this->side_pin = side_lf;
	this->back_pin = back_lf;
}


void LineSensors::getSensorValue(int sensor_pin)
{
	//TODO: check if it's value pin. Also, it can index the pins (1-4)
	analogRead(sensor_pin);
}

bool LineSensors::isBackSensorBlack()
{
	return (analogRead(this->back_pin) > BLACK_WHITE_LIMIT);
}

bool LineSensors::isSideSensorBlack()
{
	return (analogRead(this->side_pin) > BLACK_WHITE_LIMIT);
}
