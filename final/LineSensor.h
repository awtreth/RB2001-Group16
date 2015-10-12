#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

/// This class represents the LineSensor
class LineSensor
{
	private:
	int pin;///< Input analogPin
	int last_read;///< Store the last read value

	public:
	
	LineSensor();///< Attachs to A0 port by default
	
	LineSensor(int pin_number);///< setPin
	
	void attachPin(int pin_number);
	
	int read();///< actually read the value of the sensor
	int get();///< get last read value
	
	/** 
	 * \param take_last If it's true, analyse last read value. Otherwise, it'll read
	 * \return True if it's black. False otherwise
	 */
	bool isWhite(bool take_last = false);
	
	/** 
	 * \param take_last If it's true, analyse last read value. Otherwise, it'll read
	 * \return True if it's black. False otherwise
	 */
	bool isBlack(bool take_last = false);
};

#endif
