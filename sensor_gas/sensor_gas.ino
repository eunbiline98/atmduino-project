#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

int redLed = 13;
int greenLed = 11;
int buzzer = 12;
int smokeA0 = A2;
// Your threshold value
int sensorThres = 100;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  lcd.setCursor(0,0);
  lcd.print("kadar Gas :");
  lcd.print(analogSensor);
  lcd.print("%");
  lcd.print("   ");
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000, 200);
    lcd.setCursor(0,1);
  lcd.print("Gas Bocor Gan..!");
    
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
    lcd.setCursor(0,1);
  lcd.print("Kondisi Aman..  ");
  }
  delay(500);
}
