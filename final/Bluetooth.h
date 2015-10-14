#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "Arduino.h"
#include "BluetoothMaster.h"
#include "ReactorProtocol.h"

union StorageTube{ //Stores the storage tube availability
	//union is used to allow us to access the bools in an array. 
  //that lets us find valid tubes easier
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
  
  enum MessageType{ //Different types of messages to be recieved and sent
    STORAGE = 0x01,
    SUPPLY = 0x02,
    RADIATION = 0x03,
    STOP = 0x04,
    RESUME = 0x05,
    STATUS = 0x06,
    HEARTBEAT = 0x07
  };

  
  
  void update(); //Runs every loop to update Bluetooth info. Looks for valid packets and sends if need be
  void setup(); //Sets up the relevant information in the Setup

  void updateStorage(byte info); //This updates the Storage struct with the availability
  void updateSupply (byte info); //This updates the Supply struct with the availability

  void sendHB(); //Sends the heartbeat
  void sendRadiation(int radLevel); //Sends the corresponding rad level
  void sendStatus(byte moveStat, byte gripStat, byte opStat); //packages and sends a byte with the given status 

  //This sets the locations of the StorageTube, SupplyTube, and stop pointers
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

	BluetoothMaster btmaster; //sets variables to store the instance of BTMaster and Protocol
	ReactorProtocol pcol;

	StorageTube *storageTube;
	SupplyTube *supplyTube;
  bool *stop;
};

#endif
