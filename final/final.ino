
#include "DriveTrain.h"
#include "Servo.h"
#include "LineSensor.h"
#include "FRED.h"
#include "PidController.h"
#include "Action.h"
#include "RobotController.h"

#include "util.h"

#include "setup.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  mySetup();
  
}

int current_action = 0;

void loop() 
{
  current_action = += robot.execute(action_sequence[current_action]);
}
