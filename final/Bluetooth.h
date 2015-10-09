#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "Arduino.h"
#include "BluetoothMaster.h"
#include "ReactorProtocol.h"

union StorageTube{ //Stores the storage tube availability (Should these be objects????)
	
	struct{    
		bool tube0;
		bool tube1;
		bool tube2;
		bool tube3;
	};
	
	bool tube[4];
};

union SupplyTube{ //Stores the supply tube availability

	struct{	
		bool tube0;
		bool tube1;
		bool tube2;
		bool tube3;
	};
	
	bool tube[4];
};

class Bluetooth
{
public:
  Bluetooth();
  
  bool sendHB_flag; //Timer based bool _on whether to send the heartbeat
  bool Go; //Public bool on whether to go or not. Changeable by Bluetooth command
  int teamName; //The Team name
  int radLevel; //0 for none, 1 for Low, 2 for High. ONLY called on timer flag and with radLevel > 0

  enum MessageType{ //Different types of message types to be recieved
    STORAGE = 0x01,
    SUPPLY = 0x02,
    RADIATION = 0x03,
    STOP = 0x04,
    RESUME = 0x05,
    STATUS = 0x06,
    HEARTBEAT = 0x07
  };

  enum MovementStatus{ //Movement Status
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
  };
  
  void update(); //Runs every loop to update Bluetooth info
  void setup(); //Sets up the relevant information in the Setup

  //static void timerISR(); //ISR to send the heartbeat and any relevant info

  void updateStorage(byte info); //This updates the Storage struct with the availability
  void updateSupply(byte info); //This updates the Supply struct with the availability

  void sendHB(); //Sends the heartbeat
  void sendRadiation(int radLevel); //Sends the corresponding rad level
  void sendStatus(byte moveStat, byte gripStat, byte opStat); //packages and sends a byte with the given status 

	void setInputPointers(StorageTube* storage_tube, SupplyTube* supply_tube, bool* stop_flag){
		this->storageTube = storage_tube;
		this->supplyTube = supply_tube;
		this->stop = stop_flag;
	}

private:

  byte pktS[10]; //Variables for sending the packets
  byte dataS[3];

  byte pktR[10]; //Variables for recieving the packets
  byte dataR[3];
  byte type;

  volatile unsigned long elapsedTics; //for the ISR

	//BluetoothClient bt;
	BluetoothMaster btmaster;
	ReactorProtocol pcol;
	
	StorageTube *storageTube;
	SupplyTube *supplyTube;
  bool *stop;
};

#endif
