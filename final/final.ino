
#include "DriveTrain.h"
#include "Servo.h"
#include "LineSensor.h"
#include "FRED.h"
#include "PidController.h"
#include "Action.h"
#include "RobotController.h"

#include "setup.h"


PidController pid;
LineSensor left_ls(A1);
LineSensor right_ls(A0);
LineSensor side_ls(A3);
DriveTrain dtrain;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*//Initialize robot (we can create a simple function
   robot.drive_train = DriveTrain(LEFT_MOTOR_PIN, RIGHT_MOTOR_PIN);
   ...
  */
  pid.setConstants(.017, 0, 50);
  pid.setLimits(-90,+90);
  dtrain.attachMotors(LEFT_MOTOR_PIN,RIGHT_MOTOR_PIN);
}

int current_action = 0;

int delay_time = 50;

bool passed_black = false;
bool turn = true;

void loop() 
{
  if(Serial.available())
  {
    String str = Serial.readString();
    switch(str.charAt(0))
    {
      case 'p': pid.kp = str.substring(1).toFloat();break;
      case 'd': pid.kd = str.substring(1).toFloat();break;
      case 'i': pid.ki = str.substring(1).toInt(); break;
      case 'l': delay_time = str.substring(1).toInt(); break;
      case 'r': pid.reset(); break;
      default: Serial.println("Undefined");;
    }
    Serial.println(str);
  }
  
  //Serial.println("********");
  //Serial.println(right_ls.read()-left_ls.read());
  //Serial.println(pid.calc(left_ls.read()-right_ls.read()));
  int value = pid.calc(right_ls.read()-left_ls.read());
  
  //dtrain.drive(45 + value, 45 - value);
  //dtrain.turnLeft(45);
  //if(side_ls.isBlack()) dtrain.stop();

  if(side_ls.isWhite()) passed_black = true;

  if(turn) dtrain.turnLeft(45);

  if(passed_black)
  {
      if(side_ls.isBlack()){ turn =false; dtrain.stop(); passed_black = false; }
  }
  //dtrain.drive(30,30);
  //Serial.println("************");
  //Serial.println(turn);
  //Serial.println(passed_black);
  //Serial.println(side_ls.read());
  
  delay(delay_time);
  
   //current_action += robot.execute(action_sequence[current_action]);
}
