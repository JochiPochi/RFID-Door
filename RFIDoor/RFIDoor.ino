/*******************************************************
 * Code for the RFID door lock Mechanism
 * Author: John R Aleman
 * Version: 1.0
 * Notes: This piece of code saves roomates cards into the EEPROM, useful for initialization
 *
 *******************************************************/

#include <SPI.h>
#include <RFID.h>
#include <EEPROM.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

//Last card read
uint8_t serNum[4];

//One card:
struct CardUnit {
  uint8_t hexID[5];
  uint8_t checksumByte;
};

int sssss = 0;
uint32_t addr=0;


void setup(){
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop(){

  while (sssss == 0){
    CardUnit defaultcard;
    defaultcard.hexID[0]= 0xB0;
    defaultcard.hexID[1]= 0x76;
    defaultcard.hexID[2]= 0x84;
    defaultcard.hexID[3]= 0x7c;
    defaultcard.hexID[4]= 0x3e;
    uint8_t checksum = 0;
    for (int i=0;i<5;i++){
      checksum += defaultcard.hexID[i];
    }
    defaultcard.checksumByte = 0xff-checksum;

    uint8_t numberOfCards = 4;
    EEPROM.write(addr,numberOfCards);
    addr++;
    
    
    EEPROM.write(addr,0xFA);
    addr++;
    for (int i=0;i<5;i++){
      EEPROM.write(addr,defaultcard.hexID[i]);
      addr++;
    }
    EEPROM.write(addr,defaultcard.checksumByte);
    addr++;
    
    //##################################### Eke
    defaultcard.hexID[0]= 0x1a;
    defaultcard.hexID[1]= 0xD2;
    defaultcard.hexID[2]= 0x2C;
    defaultcard.hexID[3]= 0xD9;
    defaultcard.hexID[4]= 0x3D;
    checksum = 0;
    for (int i=0;i<5;i++){
      checksum += defaultcard.hexID[i];
    }
    defaultcard.checksumByte = 0xff-checksum;
    EEPROM.write(addr,0xFA);
    addr++;
    for (int i=0;i<5;i++){
      EEPROM.write(addr,defaultcard.hexID[i]);
      addr++;
    }
    EEPROM.write(addr,defaultcard.checksumByte);
    addr++;
    //##################################### Eke 2
    defaultcard.hexID[0]= 0x24;
    defaultcard.hexID[1]= 0x21;
    defaultcard.hexID[2]= 0x5F;
    defaultcard.hexID[3]= 0x23;
    defaultcard.hexID[4]= 0x79;
    checksum = 0;
    for (int i=0;i<5;i++){
      checksum += defaultcard.hexID[i];
    }
    defaultcard.checksumByte = 0xff-checksum;
    EEPROM.write(addr,0xFA);
    addr++;
    for (int i=0;i<5;i++){
      EEPROM.write(addr,defaultcard.hexID[i]);
      addr++;
    }
    EEPROM.write(addr,defaultcard.checksumByte);
    addr++;
    //##################################### Ben
    defaultcard.hexID[0]= 0xb0;
    defaultcard.hexID[1]= 0xa1;
    defaultcard.hexID[2]= 0x70;
    defaultcard.hexID[3]= 0x7f;
    defaultcard.hexID[4]= 0x1e;
    checksum = 0;
    for (int i=0;i<5;i++){
      checksum += defaultcard.hexID[i];
    }
    defaultcard.checksumByte = 0xff-checksum;
    EEPROM.write(addr,0xFA);
    addr++;
    for (int i=0;i<5;i++){
      EEPROM.write(addr,defaultcard.hexID[i]);
      addr++;
    }
    EEPROM.write(addr,defaultcard.checksumByte);
    addr++;
    //##################################### Maria
    defaultcard.hexID[0]= 0x9A;
    defaultcard.hexID[1]= 0xcd;
    defaultcard.hexID[2]= 0x7a;
    defaultcard.hexID[3]= 0x0e;
    defaultcard.hexID[4]= 0x23;
    checksum = 0;
    for (int i=0;i<5;i++){
      checksum += defaultcard.hexID[i];
    }
    defaultcard.checksumByte = 0xff-checksum;
    EEPROM.write(addr,0xFA);
    addr++;
    for (int i=0;i<5;i++){
      EEPROM.write(addr,defaultcard.hexID[i]);
      addr++;
    }
    EEPROM.write(addr,defaultcard.checksumByte);
    addr++;
    
    
    
    
    sssss = 1;
  }
}





