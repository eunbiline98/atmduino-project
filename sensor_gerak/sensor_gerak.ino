#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

int led = 3; 
int sensor = 2;                
int pirState = LOW;             
int val = 0;                    
int speaker = 10;   

void setup() {
  pinMode(led, OUTPUT);     
  pinMode(sensor, INPUT);     
  pinMode(speaker, OUTPUT);
  lcd.begin(16,2);
}
void loop(){
  val = digitalRead(sensor);  
  if (val == HIGH) {            
    digitalWrite(led, HIGH);
           
    if (pirState == LOW) {
      lcd.setCursor(0,0);
      lcd.print("   Terdeksi!!   ");
      pirState = HIGH;
    }
  } else {
      digitalWrite(led, LOW); 
      playTone(0, 0);
      delay(300);  
      if (pirState == HIGH){
            lcd.setCursor(0,0);
            lcd.print("tidak terdteksi!");
      pirState = LOW;
    }
  }
}
// Durasi msecs dalam, hertz Frekuensi
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(speaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(speaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}
