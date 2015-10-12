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

    RobotController();

    DriveTrain drive_train;
    FRED fred;

    //Bluetooth will update these variables automatically
    StorageTube storageTube;
    SupplyTube supplyTube;
    bool stop;

    int my_position; //0-3
    int goal_reactor;//1 or 2

    void printTubes();


    int radLevel;

    //int macro_action_i;

    Bluetooth bluetooth;

    int execute(Action action);
    void update();
    //int execute(MacroAction action_seq);
    //int stop();
    //int resume();

    void setAlarmPins(int pin_number_low, int pin_number_high);
    int setAlarm(int level_to_set);
    void alarmOn();
    void alarmOff();

    int setOpStat(int new_OpStat);
    int setGripStat(int new_GripStat);
    int setMoveStat(int new_MoveStat);

    int reactor2storage();
    int storage2supply();
    int supply2reactor();

    int waitDur(unsigned int duration);

  private:

    int alarm_pin_low;
    int alarm_pin_high;
};

#endif
