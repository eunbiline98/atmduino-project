#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F ,2,1,0,4,5,6,7,3, POSITIVE);


int motorKanan = 8;
int motorKiri = 9;

int switchUpPin = 13;
int switchDownPin = 12;
int counter = 0;
int buttonUpState = 0;
int lastButtonUpState = 0;
int buttonDownState = 0;
int lastButtonDownState = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin (16,2);

  pinMode(motorKanan, OUTPUT);
  pinMode(motorKiri, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Arah Motor :");
  
  buttonUpState = digitalRead(switchUpPin);
  buttonDownState = digitalRead(switchDownPin);

  if (buttonUpState != lastButtonUpState)
  {
    if (buttonUpState == HIGH)
    {
      if (counter == 100)
      {
        counter = -1;
      }
      counter++;
      Serial.println(counter);
      changeNumber(counter);
      delay(300);
    }
    else
    {
      Serial.println("OFF");
    }
    delay(50);
  }


  if (buttonDownState != lastButtonDownState)
  {
    if (buttonDownState == HIGH)
    {
      if (counter == 0)
      {
        counter = 100;
      }
      counter--;
      Serial.println(counter);
      changeNumber(counter);
      delay(300);
    }
    else
    {
      Serial.println("OFF");
    }
    delay(50);
  }
  changeNumber(counter);
}
 
           
void changeNumber(int buttonPress)
{
  switch (buttonPress)
  {
    //start
    case 0:
     digitalWrite(motorKanan, LOW);
     digitalWrite(motorKiri, LOW); 
      lcd.setCursor(0,1);
      lcd.print("Ready            ");
      break;
    //arah motor ke kanan
    case 1:
     digitalWrite(motorKanan, HIGH);
     digitalWrite(motorKiri, LOW); 
      lcd.setCursor(0,1);
      lcd.print("Kanan             ");
      break;
    //arah motor ke kiri
    case 2:
      digitalWrite(motorKanan, LOW);
     digitalWrite(motorKiri, HIGH); 
      lcd.setCursor(0,1);
      lcd.print("Kiri              ");
      break;
    //motor Stop
    case 3:
      digitalWrite(motorKanan, LOW);
     digitalWrite(motorKiri, LOW); 
      lcd.setCursor(0,1);
      lcd.print("Stop              ");
      break;
      //berakhir
      case 4:
      digitalWrite(motorKanan, LOW);
     digitalWrite(motorKiri, LOW); 
      lcd.setCursor(0,1);
      lcd.print("Ojok tekan Lagi");
    }
}
