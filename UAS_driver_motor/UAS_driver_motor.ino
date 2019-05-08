#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

#define pb3 7 // off
#define pb1 6 // arah motor cw
#define pb2 5 // arah motor cww

int kondisi1 = 0;
int kondisi2 = 0;
int kondisi3 = 1;
  
void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
// motor dc
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
// input button
pinMode(pb1,INPUT_PULLUP);
pinMode(pb2,INPUT_PULLUP);
pinMode(pb3,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

  kondisi1 = digitalRead(pb1);// arah kanan
  kondisi2 = digitalRead(pb2);// arah kiri
  kondisi3 = digitalRead(pb3);// off
  
if(kondisi1 == 1)
  {
    digitalWrite(9,HIGH);
      lcd.setCursor(0,0);
      lcd.print("arah motor kanan");
  }

  if(kondisi2 == 1)
  {
    digitalWrite(8,HIGH);
      lcd.setCursor(0,0);
      lcd.print("arah motor kiri");
  }

  if(kondisi1 == HIGH && kondisi2 == HIGH && kondisi3 == LOW)
  {
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
      lcd.setCursor(0,0);
      lcd.print("Stop            ");
  } 
}

