#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

const int sensorApi = 2;     
const int led =  13;
const int buzzer =  12;  
 
// variables will change:
int bacasensor = 0;   
 
void setup() {
  lcd.begin(16,2);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(sensorApi, INPUT);
  Serial.begin(9600);
}
 
void loop() {
  bacasensor = digitalRead(sensorApi);
 
  if ((bacasensor) == HIGH) {
    digitalWrite(led, LOW);
    noTone(buzzer);
    lcd.setCursor(0,0);
    lcd.print("Kondisi Api :");
    lcd.setCursor(0,1);
    lcd.print("Tidak Terdeteksi");
    Serial.println("tidak ada api...");
  } 
  else {
    digitalWrite(led, HIGH);
    tone(buzzer, 500 ,200);
   lcd.setCursor(0,0);
    lcd.print("Kondisi Api :");
    lcd.setCursor(0,1);
    lcd.print("Terdeteksi       ");
    delay(100);
    Serial.println("ada api...");
  }
  delay(500);
}
 
