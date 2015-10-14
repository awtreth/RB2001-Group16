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


//#define PID_TUNE

#ifdef PID_TUNE
ParamParser parser;
double kp = 0.014;
double kd = 15;
double ki = 0;
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  mySetup();
  Switch starter_switch(STARTER_SWITCH_PIN);

  Serial.println("Wait Connection");
    while(!Serial1.available());
  Serial.println("Connected");
    while(!starter_switch.isPressed())
      robot.update();

#ifdef PID_TUNE
  parser.add('p', &kp);
  parser.add('i', &ki);
  parser.add('d', &kd);
#else       
  starter_switch.waitOn();
#endif
}

int current_action = 0;
void loop()
{
  robot.update();//take care of all the communication stuffs
  current_action += robot.execute(action_sequence[current_action]);

  //#ifdef PID_TUNE
}
