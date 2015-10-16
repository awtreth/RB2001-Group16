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

void setup() {
  Serial.begin(38400); //Opens a Serial port for Debugging purposes
  mySetup(); //This sets up all the necessary information for our robot
  Switch starter_switch(STARTER_SWITCH_PIN); //Initializes the starter switch

  Serial.println("Wait Connection"); //Prints that it is waiting for a bluetooth connection
    while(!Serial1.available()); //Waits until Serial1 is available before sending the heartbeat
                                 //Other wise it makes it harder to connect as were spamming the Bluetooth
  Serial.println("Connected"); //Prints that we have a connection
    while(!starter_switch.isPressed()) //wait on the starter switch
      robot.update(); //Sends the heartbeat in the meantime, otherwise the Field control fails
}

int current_action = 0; //Initializes what the current action is 
void loop() 
{
  robot.update(); //take care of all the communication stuff
  current_action += robot.execute(action_sequence[current_action]);
  //When execute returns DONE (1) it increments the currenct action and moves on

}
