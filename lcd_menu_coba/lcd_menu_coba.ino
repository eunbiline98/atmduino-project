#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

#define sw1 10
#define sw2 11
#define sw3 12
#define led 13
int ok = 0;
int next = 0;
int back = 0;
void setup() {

pinMode(sw1, INPUT_PULLUP);
pinMode(sw2, INPUT_PULLUP);
pinMode(sw3, INPUT_PULLUP);
pinMode(led,OUTPUT);

lcd.begin(16,2);
lcd.setCursor(5,1);
lcd.print("Welcome");
delay(2000);
lcd.clear();

}

void loop()
{

menu:
while(1)
{
lcd.clear();
lcd.setCursor(6,0);
lcd.print("Menu");
lcd.setCursor(0,1);
lcd.print("Please Input!...");
delay(200);

ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (ok == LOW) { delay(300); goto menu1; }
if (next == LOW) { }
if (back == LOW) { }
}

menu1:
while(1)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Led");
lcd.setCursor(0,1);
lcd.print("1.Next 2.Back");
delay(200);

digitalWrite(led,LOW);
ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (ok == LOW) { delay(300); goto menu2; }
if (back == LOW) { delay(300); goto menu; }

}
menu2:
while(1)
{

lcd.clear();
lcd.setCursor(0,0);
lcd.print("1.Led Menyala");
lcd.setCursor(0,1);
lcd.print("2.Led Mati     ");

digitalWrite(led,LOW);
ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (back == LOW) { delay(300); goto menu4; }
if (next == LOW) { delay(300); goto menu3; }
if (ok   == LOW) { } 


menu3:
while(1)
{

lcd.setCursor(0,0);
lcd.print("1.Led Menyala");
digitalWrite(led,HIGH);

ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (back == LOW) { delay(300); goto menu1; }

}
menu4:
while(1)
{
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("1.Led Mati        ");
digitalWrite(led,LOW);

ok = digitalRead(sw1);
next = digitalRead(sw2);
back = digitalRead(sw3);
if (back == LOW) { delay(300); goto menu1; }

}
}
}
