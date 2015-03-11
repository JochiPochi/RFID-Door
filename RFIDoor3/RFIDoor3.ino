/*******************************************************
 * Code for the RFID door lock Mechanism
 * Author: John R Aleman
 * Version: 3.0
 * Notes: Full blown thing maybe
 *        only works with 1 card
 *
 *******************************************************/

#include <SPI.h>
#include <RFID.h>
#include <EEPROM.h>
#include <Servo.h> 

#define SS_PIN 10
#define RST_PIN 9
#define delayTime 3000

RFID rfid(SS_PIN, RST_PIN);

//One card:
struct CardUnit {
  uint8_t hexID[5];
  uint8_t checksumByte;
};

//Last card read
uint8_t serNum[4];

Servo DoorServo;
int servoPos;
int dummy = 0;
unsigned long timer1;
boolean DoorIsClosed = true;
boolean personGoingOut = true;
int proximitySwitch = 7;
int doorSwitch = 8;



void setup(){
  Serial.begin(9600);
  DoorServo.attach(2);
  SPI.begin();
  rfid.init();
  pinMode(doorSwitch, INPUT);
  pinMode(proximitySwitch, INPUT);
}

void loop(){
  Serial.println("Loop Begins");
  DoorIsClosed = digitalRead(doorSwitch);
  personGoingOut = digitalRead(proximitySwitch);
  if (dummy == 1){
    //Something Happnes
  }
  else{
    //Serial.println("inside else");
    if ((Allowed() || personGoingOut == true) && DoorIsClosed == true){  
      Serial.println("Door should be opening");  
      OpenDoor();
      timer1 = millis();
    }
    if (timer1+delayTime < millis() && DoorIsClosed == true){
      Serial.println("Door closing");
      LockDoor();
    }
  }
  Serial.println("Data Summary of last loop");
  Serial.println(millis());
  Serial.println(DoorIsClosed);
  Serial.println(personGoingOut);
  Serial.println("...............");


}


void OpenDoor() {
  DoorServo.write(5);  
}

void LockDoor(){
  DoorServo.write(84);
}

boolean Allowed(){
  if (rfid.isCard()){
    CardUnit requestor;
    if (rfid.readCardSerial()){
      requestor.hexID[0]= rfid.serNum[0];
      requestor.hexID[1]= rfid.serNum[1];
      requestor.hexID[2]= rfid.serNum[2];
      requestor.hexID[3]= rfid.serNum[3];
      requestor.hexID[4]= rfid.serNum[4];
      uint8_t checksum = 0;
      for (int i=0;i<5;i++){
        checksum += requestor.hexID[i];
      }
      requestor.checksumByte = 0xff-checksum;
      Serial.print("Hex: ");
      Serial.print(requestor.hexID[0],HEX);
      Serial.print(", ");
      Serial.print(requestor.hexID[1],HEX);
      Serial.print(", ");
      Serial.print(requestor.hexID[2],HEX);
      Serial.print(", ");
      Serial.print(requestor.hexID[3],HEX);
      Serial.print(", ");
      Serial.print(requestor.hexID[4],HEX);
      Serial.print("### ");
      Serial.print(requestor.checksumByte,HEX);
      Serial.println(" ");
    } 
    uint8_t addr = 0;
    int numberOfCards = EEPROM.read(addr);
    addr++;
    for (int i=0;i<numberOfCards;i++){
      uint8_t payload[7];
      for (int j=0;j<7;j++){            // Here we read all the values for one entry of a card
        payload[j]=EEPROM.read(addr);
        addr++;
      }
      CardUnit tempcard;                // the new card data is assembled into a temp card and will be stored in the Table if the checksum passes
      uint8_t checksum = 0;
      for (int j=1;j<6;j++){
        tempcard.hexID[j-1]=payload[j]; // The first byte in the payload is just an identifier, no worries
        checksum += tempcard.hexID[j-1];
      }
      tempcard.checksumByte = payload[6];

      Serial.print("Hex: ");
      Serial.print(tempcard.hexID[0],HEX);
      Serial.print(", ");
      Serial.print(tempcard.hexID[1],HEX);
      Serial.print(", ");
      Serial.print(tempcard.hexID[2],HEX);
      Serial.print(", ");
      Serial.print(tempcard.hexID[3],HEX);
      Serial.print(", ");
      Serial.print(tempcard.hexID[4],HEX);
      Serial.print("### ");
      Serial.print(tempcard.checksumByte,HEX);
      Serial.println(" ");      

      if (structCompare(requestor,tempcard)){
        structNull(requestor);
        return 1;
      }
      structNull(requestor);
    }
  }
  return 0;
}

boolean structCompare(struct CardUnit a, struct CardUnit b)
{
  if (a.hexID[0] == b.hexID[0]
    && a.hexID[1] == b.hexID[1]
    && a.hexID[2] == b.hexID[2]
    && a.hexID[3] == b.hexID[3]
    && a.hexID[4] == b.hexID[4]
    && a.checksumByte == b.checksumByte
    ){
    return 1;
  }
  else{
    return 0;
  }
}


void structNull(struct CardUnit a)
{
  a.hexID[0] = 0;
  a.hexID[1] = 0;
  a.hexID[2] = 0;
  a.hexID[3] = 0;
  a.hexID[4] = 0;
  a.checksumByte = 0xFA;
}












