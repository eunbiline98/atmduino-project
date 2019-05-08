#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F ,2,1,0,4,5,6,7,3, POSITIVE);

const int bt = 5;
const int bt2 = 6;
int st = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(bt, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  int bt = 0;
  int bt2 = 0;
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:
    if(digitalRead(bt)==0 && st == 0){
       // lcd.clear();
        delay(100);
        digitalWrite(8, HIGH);
        digitalWrite(9, LOW); 
        
        st =1;
        lcd.setCursor(0, 0);
        lcd.print("Arah putaran : ");
        lcd.setCursor(0, 1);
        lcd.print("kanan");
        
      }
      if(digitalRead(bt)==0 && st == 1){
       // lcd.clear();
        delay(100);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW); 
        st =0;
        lcd.setCursor(0, 0);
        lcd.print("Arah putaran : ");
        lcd.setCursor(0, 1);
        lcd.print("Stop  ");
      }
      
      if(digitalRead(bt2)==0 && st == 0){
       // lcd.clear();
       delay(100);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW); 
        
        st =1;
        lcd.setCursor(0, 0);
        lcd.print("Arah putaran : ");
        lcd.setCursor(0, 1);
        lcd.print("Kiri  ");
      }

      if(digitalRead(bt2)==0 && st == 1){
       // lcd.clear();
        delay(100);
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH); 
        st =0;
        lcd.setCursor(0, 0);
        lcd.print("Arah putaran : ");
        lcd.setCursor(0, 1);
        lcd.print("Stop  ");
      }
    }
