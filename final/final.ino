#include "DriveTrain.h"
#include "Servo.h"
#include "LineSensor.h"
#include "FRED.h"
#include "PidController.h"
#include "Action.h"
#include "RobotController.h"
#include "TimerOne.h"
#include "ReactorProtocol.h"
#include "BluetoothMaster.h"
#include "BluetoothClient.h"
#include "Bluetooth.h"

#include "util.h"

#include "setup.h"

double a = 0, b = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  mySetup();
}

int current_action = 0;

void loop() 
{
  static long int last_time = millis();
	
	robot.update();//take care of all the communication stuffs
	//current_action += robot.execute(action_sequence[current_action]);
	
	if((millis() - last_time)>1000)
 {
		robot.printTubes();
    last_time = millis();
 }
}
