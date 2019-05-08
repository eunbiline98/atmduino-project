#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
 //type lcd
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);// kordinat karakter
  lcd.print("sistem komputer"); //tampilan lcd
}
