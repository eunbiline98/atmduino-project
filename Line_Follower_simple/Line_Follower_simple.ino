#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

int kiriA = 9;
int kiriB = 6;
int kananA = 5;
int kananB = 3;

void setup()
{
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(kiriA,OUTPUT);
  pinMode(kiriB,OUTPUT);
  pinMode(kananA,OUTPUT);
  pinMode(kananB,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);

}

void loop()
{
  int kiri = digitalRead(A0);
  int kanan = digitalRead(A1);
  int kanan = digitalRead(A2);

 //HIGH=hitam, LOW=putih

  if ((kiri==HIGH)&&(kanan==LOW))
  {
    digitalWrite(kiriA,HIGH);
    digitalWrite(kiriB,LOW);
    digitalWrite(kananA,LOW);
    digitalWrite(kananB,HIGH);

    //LCD Program
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("i=hitam a=putih");
    lcd.setCursor(0,1);
    lcd.print("BELOK KIRI");

    //Serial Program
    Serial.println("Sensor Kiri Hitam & Sensor Kanan Putih");
    Serial.println("BELOK KIRI");
  }
  else if ((kiri==LOW)&&(kanan==HIGH))
  {
    digitalWrite(kiriA,LOW);
    digitalWrite(kiriB,HIGH);
    digitalWrite(kananA,HIGH);
    digitalWrite(kananB,LOW);
    //LCD Program
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("i=putih a=hitam");
    lcd.setCursor(0,1);
    lcd.print("BELOK KANAN");

    //Serial Program
    Serial.println("Sensor Kiri Putih & Sensor Kanan Hitam");
    Serial.println("BELOK KANAN");
  }
  else if ((kiri==HIGH)&&(kanan==HIGH))
  {
    digitalWrite(kiriA,HIGH);
    digitalWrite(kiriB,LOW);
    digitalWrite(kananA,HIGH);
    digitalWrite(kananB,LOW);
    //LCD Program
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("i=hitam a=hitam");
    lcd.setCursor(0,1);
    lcd.print("MUNDUR");

    //Serial Program
    Serial.println("Sensor Kiri Hitam & Sensor Kanan Hitam");
    Serial.println("MUNDUR");
  }

  else
  {
    digitalWrite(kiriA,LOW);
    digitalWrite(kiriB,HIGH);
    digitalWrite(kananA,LOW);
    digitalWrite(kananB,HIGH);
    //LCD Program
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("i=putih a=putih");
    lcd.setCursor(0,1);
    lcd.print("MAJU");

    //Serial Program
    Serial.println("Sensor Kiri Putih & Sensor Kanan Putih");
    Serial.println("MAJU");
  }

}
