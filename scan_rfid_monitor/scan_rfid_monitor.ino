#include <SPI.h> //library serial parallel interface
#include <Wire.h> //library untuk wire i2c
#include <RFID.h> //library RFID
#define sda 10 //Pin Serialdata (SDA)
#define rst 9 //pin Reset
 
RFID rfid(sda,rst);
 
void setup(){
    Serial.begin(9600); //baud komunikasi serial monitor
    SPI.begin(); //Prosedur antarmuka SPI
    Serial.println(" test RFID PN 532");
    Serial.println(" tap Please....");
    rfid.init(); //Memulai inialisasi module RFID
}
 
void loop(){
 
if(rfid.isCard()){
if(rfid.readCardSerial()){

   Serial.print(rfid.serNum[0]); //serial no.1
   Serial.print(" ");
   
   Serial.print(rfid.serNum[1]); //serial no.2
   Serial.print(" ");
   
   Serial.print(rfid.serNum[2]); //serial no.3
   Serial.print(" ");
    
   Serial.print(rfid.serNum[3]); //serial no.4
   Serial.print(" ");
   
   Serial.print(rfid.serNum[4]); //serial no.5
   Serial.println("");
 
   }  
  }   
 }
