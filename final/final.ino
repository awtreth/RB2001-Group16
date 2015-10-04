#include "DriveTrain.h"
#include "Servo.h"
#include "LineSensor.h"
#include "FRED.h"
#include "PidController.h"
#include "Action.h"
#include "RobotController.h"

#define LEFT_MOTOR_PIN 4
#define RIGHT_MOTOR_PIN 5

RobotController robot;

//we can put that declaration in a separated file (maybe we can create a "Action.h")
Action action_sequence[] = 
{//examples
  Action(TURN, LEFT_TURN, BACK_LS),
  Action(GO_STRAIGHT, 20, 2),
  Action(GO_STRAIGHT, 20)//has to be specified
  //...
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*//Initialize robot (we can create a simple function
   robot.drive_train = DriveTrain(LEFT_MOTOR_PIN, RIGHT_MOTOR_PIN);
   ...
  */
}

int current_action = 0;

void loop() 
{
    current_action += robot.execute(action_sequence[current_action]);
}
