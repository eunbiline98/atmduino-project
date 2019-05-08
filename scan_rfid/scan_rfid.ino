#include <SPI.h> //library serial parallel interface
#include <Wire.h> //library untuk wire i2c
#include <RFID.h> //library RFID
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);
 
#define sda 10 //Pin Serialdata (SDA)
#define rst 9 //pin Reset
 
RFID rfid(sda,rst);

 int serNum[5];          //Variable buffer Scan Card
  int cards[][5] = {{47,125,104,104,82}}; // yang diizinkan

  bool access = false;
  
void setup(){
    Serial.begin(9600); //baud komunikasi serial monitor
    lcd.begin(16,2); //ukuran LCD 16 x 2
    SPI.begin(); //Prosedur antarmuka SPI
    rfid.init(); //Memulai inialisasi module RFID
 
   lcd.setCursor (0,0);
  lcd.print("***RFID RF522***");
  lcd.setCursor (0,1);
  lcd.print(" scan card RFID ");
  delay (4000);
  lcd.clear();
}
 
void loop(){
  lcd.setCursor (0,0);
  lcd.print("Please scan card");
  lcd.setCursor (0,1);
  lcd.print("  ...<<< Here  ");
 
if(rfid.isCard()){
if(rfid.readCardSerial()){
   lcd.setCursor (0,0);
   lcd.print("ID Card :        ");
   
   lcd.setCursor (0,1);
   Serial.print(rfid.serNum[0]); //serial no.1
   Serial.print(" ");
   lcd.print(rfid.serNum[0]);
   
   Serial.print(rfid.serNum[1]); //serial no.2
   Serial.print(" ");
   lcd.print(rfid.serNum[1]);
   
   Serial.print(rfid.serNum[2]); //serial no.3
   Serial.print(" ");
   lcd.print(rfid.serNum[2]);
    
   Serial.print(rfid.serNum[3]); //serial no.4
   Serial.print(" ");
   lcd.print(rfid.serNum[3]);
   
   Serial.print(rfid.serNum[4]); //serial no.5
   Serial.println("");
   lcd.print(rfid.serNum[4]);
 
   delay(3000);
   lcd.clear(); 
   }  
    for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }   
        } 
   if(access){
          Serial.println("Welcome!");
          lcd.setCursor (0,0);
          lcd.print(F(" Akses diterima "));
          lcd.setCursor (0,1);
          lcd.print("ID:");
          lcd.print(rfid.serNum[0]); lcd.print(rfid.serNum[1]);
          lcd.print(rfid.serNum[2]); lcd.print(rfid.serNum[3]);
          lcd.print(rfid.serNum[4]);
     // tampilan sukses
    lcd.setCursor(0,0);
    lcd.print("E Money");
    lcd.setCursor(0,1); 
    lcd.print("Mandiri");
   }
}
 
