#include "Bluetooth.h"
#include "TimerOne.h"

#define TEAM_NUMBER 16 //constant for our Team name

Bluetooth::Bluetooth(){ //Initializes the Bluetooth object
  
  this->setup();
  //BluetoothClient bt;
  //BluetoothMaster btmaster;
}

/** a callable function that takes care of the Bluetooth setup
 */
void Bluetooth::setup()
{
  this->pcol = ReactorProtocol(byte(TEAM_NUMBER)); //creates an instance of the ReactorProtocol class with 16 as the Team number
  //Serial.begin(38400);
  //Serial1.begin(115200); //Serial3 for the Mega
  pcol.setDst(0x00); //Always set to broadcast to everyone //FIXME
  //Serial.println("Trying to connect Bluetooth");
  //while(!Serial1.available());
  //Serial.println("Bluetooth connected");
}
/** a callable function that takes care of reading the Bluetooth and taking care of the relevant assigns
 */
void Bluetooth::update(){
  
  if(btmaster.readPacket(pktR)){ //If there is a packet to read
    if(pcol.getData(pktR, dataR, type) && (pktR[4] == TEAM_NUMBER || pktR[4] == 0x00)){ //If it's addressed to us or all
      switch (type) { //state machine for the types of packets to be read
        case STORAGE:
          updateStorage(dataR[0]); //updates the storage bools with the relevant info
          break;
        case SUPPLY:
          updateSupply(dataR[0]); //updates the supply bools with the relevant info
          break;
        case STOP:
          *stop = true; //sets flags for movement 
          break;
        case RESUME:
          *stop = false;
          break;
      }
    }
  }
}



/** Updates the storage struct with the relevant booleans
 * @param info the information byte that is read from Bluetooth
 */
void Bluetooth::updateStorage(byte info){
  storageTube->tube0 = ((info & 0x01) == 0x01); //uses a bitmask and comparison to see if the corresponding bit is on
  storageTube->tube1 = ((info & 0x02) == 0x02); //it then stores that information in a struct to be read
  storageTube->tube2 = ((info & 0x04) == 0x04);
  storageTube->tube3 = ((info & 0x08) == 0x08);
}

/** Updates the supply tubes with the relevant booleans
 * @param info the information byte that was read 
 */
void Bluetooth::updateSupply(byte info){
  supplyTube->tube0 = ((info & 0x01) == 0x01); //uses a bitmask and comparison to see if the corresponding bit is on
  supplyTube->tube1 = ((info & 0x02) == 0x02); //it then stores that information in a struct to be read
  supplyTube->tube2 = ((info & 0x04) == 0x04);
  supplyTube->tube3 = ((info & 0x08) == 0x08);
}

/** sends the Heartbeat
 *  needs to be wrapped in a timed statement so as not to spam 
 */ 
void Bluetooth::sendHB(){
  int size = pcol.createPkt(HEARTBEAT, dataS, pktS); //creates the packet, returns the size
  btmaster.sendPkt(pktS, size);  //sends the packet itself
}

/** Sends the radiation level
 * @param radLevel what radiation level needs to be sent
 */ 
void Bluetooth::sendRadiation(int radLevel){
  //create named constants instead of magic numbers 
  if(radLevel == 1){ //determines radiation and sets the data correctly
    dataS[0] = 0x2C;
  }else if(radLevel == 2){
    dataS[0] = 0xFF;
  }

  int size = pcol.createPkt(RADIATION, dataS, pktS);//creates and sizes the packet
  btmaster.sendPkt(pktS, size); //sends the packet
}

/** Creates a sends a packet with information about movement, gripper, and opstat
 * @param moveStat the movement status, reference enum
 * @param gripStat the gripper status, reference enum
 * @param opStat the operation status, reference enum
 */
void Bluetooth::sendStatus(byte moveStat, byte gripStat, byte opStat){
  dataS[0] = moveStat; //sets the correct data byte index to the information given
  dataS[1] = gripStat;
  dataS[2] = opStat;

  int size = pcol.createPkt(STATUS, dataS, pktS); //creates and sizes the info
  btmaster.sendPkt(pktS, size); //sends the packet
}

