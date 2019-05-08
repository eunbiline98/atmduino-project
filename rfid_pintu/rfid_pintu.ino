#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "SPI.h"
#include "MFRC522.h"

#include <Servo.h>

Servo myservo;

#define SS_PIN 10
#define RST_PIN 9


MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
myservo.attach(4);
  Serial.println("I am waiting for card...");
  lcd.begin(16,2);
  myservo.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
    lcd.clear();
    lcd.print("Tap your Card");
   
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }


  strID.toUpperCase();
  Serial.print("Tap card key: ");
  Serial.println(strID);
  delay(1000);

  if (strID.indexOf("E4:4C:33:D0") >= 0) {  //put your own tap card key;
    myservo.write(0);                  // sets the servo position according to the scaled value
    delay(1);
    Serial.println("********************");
    Serial.println("**Authorised acces**");
    Serial.println("********************");
    lcd.clear();
    lcd.print("Kartu Anda Cocok");
    delay(1500);
    myservo.write(90);
  }
  else {
    Serial.println("****************");
    Serial.println("**Acces denied**");
    Serial.println("****************");
    lcd.clear();
    lcd.print("Kartu Tk Cocok");
    delay(1500);

  }
 
}
