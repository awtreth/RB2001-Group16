#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

class LineSensor
{
	private:
	int pin;
	int last_read;

	public:
	
	LineSensor();
	
	LineSensor(int pin_number);
	
	void attachPin(int pin_number);
	
	int read();
	int get();
	
	bool isWhite(bool take_last = false);
	bool isBlack(bool take_last = false);
};

#endif
