#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);
int progressBari = 0;  
int i = 0;

// Kararter progress bar untuk LCD
byte progressBar[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

#include <Servo.h>
#include <NewPing.h>
#include <AFMotor.h>
#define echo    A2
#define trigger A3
#define pinServo  9

AF_DCMotor motor1(3); 
AF_DCMotor motor2(4); 
Servo servo;
NewPing sonar(trigger,echo); 
int x=160; //kecepatan;

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.createChar(0, progressBar);
  servo.attach(pinServo);
  servo.write(90);
  //delay(1000);
  lcd.setCursor(3,0);
  lcd.print("Eunbi Line");
  delay(2000);
  lcd.clear();

  lcd.setCursor(0,0); 
  lcd.print("Loading:"); 

  progressBari= 16;
  
 for (i=0; i<progressBari; i++)
  {
    lcd.setCursor(i, 1);  
    lcd.write(byte(0)); 
    delay(250);
  }
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("   STMIK ASIA");
  lcd.setCursor(1,1);
  lcd.print(" Robo-Avoider");
  delay(2500);
  lcd.clear();
}

int pos, jarak;
boolean kiri = false;
boolean kanan = false;

void loop() { 
  
  int sensorValue = analogRead(A0);
  float Voltage = sensorValue * (5.00 /1023) * 2;
  lcd.setCursor(11,0);
  lcd.print(Voltage);
  lcd.print("V    "); 

  lcd.setCursor(6,1);
  lcd.print("Eunbi Line"); 

  awal:
  jarak = sonar.ping_cm();
  Serial.print(jarak);
  lcd.setCursor(0,1);
  lcd.print(jarak);
  lcd.print("cm  ");
  
  if(jarak <= 20 &&jarak >0)
  {
    while(1)
    {
      mundur();
      delay(200);
      berhenti();
      delay(1500);
      servo.write(0);
      delay(1000);
      jarak = sonar.ping_cm();
      if(jarak > 20)
      {
        kanan = true;
      }
      servo.write(180);
      delay(1000);
      jarak = sonar.ping_cm();
      if(jarak > 20)
      {
        kiri = true;
        servo.write(90);
        delay(1000);
      }
      else
      {
        servo.write(90);
        delay(1000);
      }
      while(kanan == true && kiri == false)
      {
        jarak = sonar.ping_cm();
        if(jarak < 50)
        {
          belokkiri();
        }
        else
        {
          kanan = false; kiri = false;
          goto awal;
        }
      }
      while(kanan == false && kiri == true)
      {
        jarak = sonar.ping_cm();
        if(jarak < 50)
        {
          belokkanan();
        }
        else
        {
          kanan = false; kiri = false;
          goto awal;
        }
      }
      while(kanan == true && kiri == true)
      {
        jarak = sonar.ping_cm();
        if(jarak < 50)
        {
          belokkanan();
        }
        else
        {
          kanan = false; kiri = false;
          goto awal;
        }
      }
      while(kanan == false && kiri == false)
      {
        jarak = sonar.ping_cm();
        if(jarak < 50)
        {
          belokkanan();
        }
        else
        {
          kanan = false; kiri = false;
          goto awal;
        }
      }
    }
  }
  else
  {
    maju();
  }
}

void maju()
{
  motor1.setSpeed(x); 
  motor1.run(FORWARD); 
  motor2.setSpeed(x); 
  motor2.run(FORWARD);
  Serial.println("maju");
  lcd.setCursor(0,0);
  lcd.print("Maju ");
  
}
void mundur()
{
  motor1.setSpeed(x); 
  motor1.run(BACKWARD);
  motor2.setSpeed(x); 
  motor2.run(BACKWARD); 
}
void belokkiri()
{
  motor1.setSpeed(x-30);
  motor1.run(BACKWARD); 
  motor2.setSpeed(x);
  motor2.run(FORWARD);
  Serial.println("kiri");
  lcd.setCursor(0,0);
  lcd.print("Kiri ");
  
}
void belokkanan()
{
  motor1.setSpeed(x); 
  motor1.run(FORWARD); 
  motor2.setSpeed(x-30);
  motor2.run(BACKWARD); 
  Serial.println("kanan");
  lcd.setCursor(0,0);
  lcd.print("Kanan");
  
}
void berhenti()
{
   motor1.setSpeed(0);
  motor2.run(RELEASE); 
  motor2.setSpeed(0);
  motor2.run(RELEASE);
  Serial.println("Stop");
  lcd.setCursor(0,0);
  lcd.print("Stop ");
}


