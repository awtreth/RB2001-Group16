#ifndef ARDUINO_H
#define ARDUINO_H
#include "Arduino.h"
#endif

#ifndef BLUETOOTHCLIENT_H
#define BLUETOOTHCLIENT_H
#include <BluetoothClient.h">
#endif

#ifndef BLUETOOTHMASTER_H
#define BLUETOOTHMASTER_H
#include <BluetoothMaster.h>
#endif

#ifndef REACTORPROTOCOL_H
#define REACTORPROTOCOL_H
#include <ReactorProtocol.h> 
#endif

#ifndef TIMERONE_H
#define TIMERONE_H
#include <TimerOne.h>
#endif

#ifndef BLUETOOTH_H
#define BLUETOOTH_H

class Bluetooth
{
public:
  Bluetooth();
  
  bool sendHB?; //Timer based bool on whether to send the heartbeat
  bool Go; //Public bool on whether to go or not. Changeable by Bluetooth command
  int teamName; //The Team name
  int radLevel; //0 for none, 1 for Low, 2 for High. ONLY called on timer flag and with radLevel > 0


  typedef struct storageTube{ //Stores the storage tube availability (Should these be objects????)
    bool tube1;
    bool tube2;
    bool tube3;
    bool tube4;
  } storageTube;

  typedef struct supplyTube{ //Stores the supply tube availability
    bool tube1;
    bool tube2;
    bool tube3;
    bool tube4;
  } supplyTube;


  enum messageType{ //Different types of message types to be recieved
    STORAGE = 0x01,
    SUPPLY = 0x02,
    RADIATION = 0x03,
    STOP = 0x04,
    RESUME = 0x05,
    STATUS = 0x06,
    HEARTBEAT = 0x07
  };

  enum movementStatus{ //Movement Status
    STOPPED = 0x01,
    MOVINGTELE = 0x02,
    MOVINGAUTO = 0x03
  };

  enum gripperStatus{ //Gripper Status
    NOROD = 0x01,
    ROD = 0x02    
  };

  enum operationStatus{ //Operation Status
    GRIPATTEMPT = 0x01,
    GRIPRELEASE = 0x02,
    DRIVINGREACTOR = 0x03,
    DRIVINGSTORAGE = 0x04,
    DRIVINGSUPPLY = 0x05,
    IDLE = 0x06
  }
  
  void BluetoothPeriodic(); //Runs every loop to update Bluetooth info
  void BluetoothSetup(); //Sets up the relevant information in the Setup

  void timerISR(); //ISR to send the heartbeat and any relevant info

  void updateStorage(byte info); //This updates the Storage struct with the availability
  void updateSupply(byte info); //This updates the Supply struct with the availability

  void sendHB(); //Sends the heartbeat
  void sendRadiation(int radLevel); //Sends the corresponding rad level
  void sendStatus(byte moveStat, byte gripStat, byte opStat); //packages and sends a byte with the given status 
  
  void sendNxtPkt(); //Sends the next packet in the queue
  Queue createQueue(int max_entries); //creates a queue 
  int enqueue(Queue Q, byte* pkt); //adds the packet to the queue
  byte* dequeue(Queue Q); //dequeues the next pointer

private:

  byte pktS[10]; //Variables for sending the packets
  int szS;
  byte dataS[3];

  byte pktR[10]; //Variables for recieving the packets
  byte dataR[3];
  byte type;

  volatile unsigned long elapsedTics; //for the ISR
};