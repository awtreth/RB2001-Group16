#include <Event.h>
#include <Timer.h>
#include <Servo.h>

#define RIGHT_SERVO_PIN 4
#define LEFT_SERVO_PIN  5

Servo left_motor;
Servo right_motor;

Timer ln_track_timer;

bool LT = HIGH;

unsigned long currentTime;

void setup_motors()
{
  left_motor.attach(LEFT_SERVO_PIN);
  right_motor.attach(RIGHT_SERVO_PIN);
}

#define LEFT_LN_SENSOR_PIN  A10
#define RIGHT_LN_SENSOR_PIN A11
#define TURN_LN_SENSOR_PIN  A9
#define PID_REF 56//WHITE. Both sensors see white

float kp = .02;
float kd = .05;

#define KP .1
#define KI  0
#define KD  0
#define LEFT_MOTOR_REF 25  
#define RIGHT_MOTOR_REF 40//right motor turns faster than the left   

void setup() {
  // put your setup code here, to run once:
  setup_motors();
  ln_track_timer.every(50, set_LT);
  Serial.begin(9600);
}

String str;

void loop() {

  if(analogRead(A9) > 60){
    turn_right();
    turn_left();
  }

  while(LT == HIGH){
    ln_track_isr();
  }

  

/*
  if(Serial.available())
  {
    str = Serial.readString();
    switch (str.charAt(0))
    {
      case 'p': kp = str.substring(1).toFloat(); break;
      case 'd': kd = str.substring(1).toFloat(); break;
    }
    
    Serial.println(str);
  }
  */
}

void run_motors(int left_value, int right_value)//-90~+90
{
  left_value = constrain(left_value, -90,90);
  right_value = constrain(right_value, -90,90);
    
  left_value = map(left_value, -90,90,180,0);
  right_value = map(right_value, -90,90,0,180);

  right_motor.write(right_value);
  left_motor.write(left_value);
}

int last_error = 0;

void ln_track_isr()
{
  int left_ln_sensor = analogRead(LEFT_LN_SENSOR_PIN);
  int right_ln_sensor = analogRead(RIGHT_LN_SENSOR_PIN);;

  //positive - right
  //negative - left
  int error = (left_ln_sensor - right_ln_sensor);

  int delta_signal = error*kp + (error-last_error)*kd;

  last_error = error;

  int left_signal = LEFT_MOTOR_REF + delta_signal;
  int right_signal = RIGHT_MOTOR_REF - delta_signal;

  //Serial.print("LEFT = ");
  //Serial.println(left_ln_sensor);
  //Serial.print("RIGHT = ");
  //Serial.println(right_ln_sensor);
    //delay(1000);
  run_motors(LEFT_MOTOR_REF+delta_signal, RIGHT_MOTOR_REF - delta_signal);
  LT = LOW;
}

void set_LT(){
  LT = HIGH;
}

void turn_right(){
  currentTime = millis();
  while(millis() < (currentTime + 500)){
    left_motor.write(180);
    right_motor.write(0);
    }
    while(analogRead(TURN_LN_SENSOR_PIN) < PID_REF){
      left_motor.write(100);
      right_motor.write(80);
    }
}
void turn_left(){
 currentTime = millis();
  while(millis() < (currentTime + 500)){
    left_motor.write(0);
    right_motor.write(180);
    }
    while(analogRead(TURN_LN_SENSOR_PIN) < PID_REF){
      left_motor.write(80);
      right_motor.write(100);
    }
}
