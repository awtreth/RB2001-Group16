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


//ParamParser parser;
//double kp = 0.015, kd = 15, ki = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  mySetup();
  Switch starter_switch(STARTER_SWITCH_PIN);
  
  //while(!starter_switch.isPressed())
    
  starter_switch.waitOn();
  Serial.println("GO");
  //parser.add('p', &kp);
  //parser.add('i', &ki);
  //parser.add('d', &kd);
}

int current_action = 0;
void loop()
{
  //parser.check();
  //robot.drive_train.pid.setConstants(kp, ki, kd);
  //robot.drive_train.moveBackward();
  robot.update();//take care of all the communication stuffs
  //robot.printTubes();
  current_action += robot.execute(action_sequence[current_action]);
  //Serial.println(current_action);
}
