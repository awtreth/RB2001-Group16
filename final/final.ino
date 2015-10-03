#include "DriveTrain.h"
#include "Servo.h"
#include "LineSensor.h"
#include "FRED.h"
#include "PidController.h"

#define LEFT_MOTOR_PIN 4
#define RIGHT_MOTOR_PIN 5

LineSensor left_lf(A11);
DriveTrain drive_train;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  drive_train.attachMotors(LEFT_MOTOR_PIN, RIGHT_MOTOR_PIN);
  //drive_train.stop();
}

void loop() {

}
