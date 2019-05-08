#include <LiquidCrystal_I2C.h>

#define echoPin 7 // echo
#define trigPin 8 // trig

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
 lcd.begin(16,2);
}

void loop()
{
  long durasi, inches, cm, jarak;
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 
 digitalWrite(trigPin, LOW);
 
 durasi = pulseIn(echoPin, HIGH);
 jarak = durasi/58.2;

  lcd.setCursor(0,0);
  lcd.print("Jarak =");
  lcd.print(jarak);
  lcd.print("cm   ");
  delay(500);

  }

