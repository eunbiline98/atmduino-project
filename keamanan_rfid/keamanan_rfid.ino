#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define kontak 3 // kontak sepeda motor
#define hijau 4 // lampu ok
#define merah 5 // lampu error


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600); 
  SPI.begin();
  lcd.begin(16,2);     
  mfrc522.PCD_Init();

  pinMode(hijau, OUTPUT);
  pinMode(merah, OUTPUT);
  pinMode(kontak, OUTPUT);

  lcd.setCursor (0,0);
  lcd.print("   Pengamanan ");
  lcd.setCursor (0,1);
  lcd.print("  Sepeda Motor");
  delay (4000);
  lcd.clear();

}
void loop(){
  lcd.setCursor (0,0);
  lcd.print("Please scan card");
  lcd.setCursor (0,1);
  lcd.print("  ...<<< Here  ");;
 
  // membaca ID card
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // memilih salah satu card yang terdeteksi
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
// clear lcd
  lcd.setCursor(0,0);
  lcd.print("                 ");
  lcd.setCursor(0,1);
  lcd.print("                 ");
  //tampilkan ID card di serial monitor

Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "2F 7D 68 68") //ganti dengan ID RFID tag kalian
   {
    lcd.setCursor(0,0);
    lcd.print("Access Accepted");
    lcd.setCursor(0,1);
    lcd.print("Start Engine  ");
    
    delay(2000);
    digitalWrite(kontak,HIGH);  
    digitalWrite(hijau,HIGH);
    delay(1000);
    digitalWrite(hijau,LOW);
   
    lcd.clear();
  }
 
 else   
 {
    lcd.setCursor(0,0);
    lcd.print(" Access Denied ");
    digitalWrite(merah,HIGH);
    delay(3000);
    digitalWrite(merah,LOW);
    digitalWrite(kontak,LOW); 
    lcd.clear();
  }
}
