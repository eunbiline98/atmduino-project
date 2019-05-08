#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

const int analogIn = A0;
const int analogOut =13;

int led    = 1;
int push   = 3;
int sensor ;
int output ;

int button = 0; 

void setup() {
  // put your setup code here, to run once:
// led dan push button
  pinMode(led,OUTPUT);
  pinMode(push,INPUT);

//lcd
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Ath Thaareq M");
  lcd.setCursor(0,1);
  lcd.print("16202006");
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
//data sensor

  sensor = analogRead(analogIn);
  output = map(sensor, 0, 1023, 0, 255);
  analogWrite(analogOut, analogOut);

//tampilan lcd

  lcd.setCursor(0,0);
  lcd.print("Sensor = ");
  Serial.print(analogOut);

  

   button = digitalRead(push);
if (button == HIGH) {
    // LED on:
    digitalWrite(led, HIGH);
  } else {
    //  LED off:
    digitalWrite(led, LOW);
  } 
}
