#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H

#include "Switch.h"
#include "DriveTrain.h"
#include "LineSensor.h"
#include "Action.h"
#include "PidController.h"
#include "Bluetooth.h"

#define HEARTBEAT_PERIOD 2000 //in miliseconds
#define SEND_STATUS_PERIOD 1000
#define RADIATION_ALARM_PERIOD 1000

class RobotController
{
  public:

  
    RobotController();

    DriveTrain drive_train; //Objects for the drivetrain, FRED, and the Bluetooth
    FRED fred;
    Bluetooth bluetooth;

    //Bluetooth will update these variables automatically
    StorageTube storageTube;
    SupplyTube supplyTube;
    bool stop;

    int my_position; //0-3
    int goal_reactor;//1 or 2

    void printTubes(); //Function for debugging Bluetooth

    int radLevel;//0-2


    int execute(Action action); //executes the action
    void update(); //updates the bluetooth and information

    void setAlarmPins(int pin_number_low, int pin_number_high);
    int setAlarm(int level_to_set);
    void alarmOn();
    void alarmOff();

    int setOpStat(int new_OpStat);
    int setGripStat(int new_GripStat);
    int setMoveStat(int new_MoveStat);

    int startup();
    int reactor2storage();
    int storage2supply();
    int supply2reactor();
    int reactor2reactor();
    int placeReactor();
    int grabRod();

  private:

    enum MovementStatus { //Movement Status
      STOPPED = 0x01,
      MOVINGTELE = 0x02,
      MOVINGAUTO = 0x03
    }moveStat;

    enum gripperStatus { //Gripper Status
      NOROD = 0x01,
      ROD = 0x02
    }gripStat;

    enum operationStatus { //Operation Status
      GRIPATTEMPT = 0x01,
      GRIPRELEASE = 0x02,
      DRIVINGREACTOR = 0x03,
      DRIVINGSTORAGE = 0x04,
      DRIVINGSUPPLY = 0x05,
      IDLE = 0x06
    }opStat;
    
    int alarm_pin_low;
    int alarm_pin_high;
};

#endif
