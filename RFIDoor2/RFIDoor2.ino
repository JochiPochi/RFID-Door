/*******************************************************
 * Code for the RFID door lock Mechanism
 * Author: John R Aleman
 * Version: 2.0
 * Notes: This piece of code loads the EEprom data into an array and displays in on screen
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
  addr = 0;
  int numberOfCards = EEPROM.read(addr);
  addr++;
  //if (numberOfCards > 0){
    CardUnit accessTable[numberOfCards];
  //}
  for (int i=0;i<numberOfCards;i++){
    uint8_t payload[7];
    for (int j=0;j<7;j++){            // Here we read all the values for one entry of a card
      payload[j]=EEPROM.read(addr);
      addr++;
      Serial.print(payload[j],HEX);
      Serial.print(" ");
    }
    CardUnit tempcard;                // the new card data is assembled into a temp card and will be stored in the Table if the checksum passes
    uint8_t checksum = 0;
    for (int j=0;j<5;j++){
      tempcard.hexID[j]=payload[j+1]; // The first byte in the payload is just an identifier, no worries
      checksum += tempcard.hexID[j];
    }
    if (checksum+payload[6]== 0xFF){
      accessTable[i]=tempcard;
      Serial.println("Success!!!!");
    }
  }
  
  Serial.print(numberOfCards);
  Serial.print("     ");
  Serial.print(accessTable[0].hexID[0],HEX);
  Serial.print(" ");
  Serial.print(accessTable[0].hexID[1],HEX);
  Serial.print(" ");
  Serial.print(accessTable[0].hexID[2],HEX);
  Serial.print(" ");
  Serial.print(accessTable[0].hexID[3],HEX);
  Serial.print(" ");
  Serial.print(accessTable[0].hexID[4],HEX);
  Serial.println(" ");
  delay(2000);  

}






