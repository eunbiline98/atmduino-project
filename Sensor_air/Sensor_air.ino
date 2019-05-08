#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

#define sensor 8
#define relay 9

void setup() {
  pinMode(sensor, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  lcd.begin (16,2);
  lcd.setCursor(0,0);
  lcd.print("Smart Bak Mandi");
  delay(2000);
  lcd.setCursor(4,1);
  lcd.print("Ready...!");
  delay(1000);
  lcd.clear();
}

void loop() {
  while(digitalRead(sensor) == HIGH){
    digitalWrite(relay, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Air Penuh Gan!");
    lcd.setCursor(0,1);
    lcd.print("Keran OFF");
   
  }
   digitalWrite(relay, LOW);
    lcd.setCursor(0,0);
    lcd.print("Air Kosong Gan!");
    lcd.setCursor(0,1);
    lcd.print("Keran ON ");
 
}
