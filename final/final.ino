
#include "DriveTrain.h"
#include "Servo.h"
#include "LineSensor.h"
#include "FRED.h"
#include "PidController.h"
#include "Action.h"
#include "RobotController.h"

#include "setup.h"
#include "util.h"

double a = 0, b = 1, c = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  
  mySetup();
  
}

void loop() 
{
  robot.drive_train.moveForward();
}
