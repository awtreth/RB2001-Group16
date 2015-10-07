#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

class LineSensor
{
	private:
	int pin;

	public:
	
	LineSensor();
	
	LineSensor(int pin_number);
	
	void attachPin(int pin_number);
	
	int read();
	
	bool isWhite();
	bool isBlack();
};

#endif
