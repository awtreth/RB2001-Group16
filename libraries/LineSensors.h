#ifndef LINE_SENSORS_H
#define LINE_SENSORS_H

class LineSensors
{
	private:
	int left_pin;
	int right_pin;
	int side_pin;
	int back_pin;


	public:
	
	LineSensors();
	LineSensors(int left_lf, int right_lf, int side, int back);
	
	int getDiff();
	
	void setSensorsPin(int left_lf, int right_lf, int side, int back);
	
	void getSensorValue(int sensor_pin);
	
	bool isBackSensorBlack();
	bool isSideSensorBlack();
}

#endif
