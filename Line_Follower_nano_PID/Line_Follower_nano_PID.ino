#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

#define eepromKp 0
#define eepromSpeed 1
#define eepromKd  2

#define button1 13
#define button2 12
#define button3 1
#define button4 0
#define echo    10
#define trigger 11
#define pwmOne  5
#define inAOne  4
#define inBOne  9
#define pwmTwo  6
#define inATwo  8
#define inBTwo  7
int sensorVal[6];

void setup() {
  // put your setup code here, to run once:
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);  
  pinMode(pwmOne, OUTPUT);
  pinMode(inAOne, OUTPUT);
  pinMode(inBOne, OUTPUT);
  pinMode(pwmTwo, OUTPUT);
  pinMode(inATwo, OUTPUT);
  pinMode(inBTwo, OUTPUT);
  Serial.begin(9600);
  delay(1000);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  lcd.begin(16,2); 
  
  lcd.setCursor(0,0);
  lcd.print("Automaton");
  lcd.setCursor(0,1);
  lcd.print("Stmik Asia Ready");
  delay(2000);
  lcd.clear();
}
unsigned char Kp = 25; 
unsigned char Kd = 9;
unsigned char Ts = 1;
unsigned char max_pwm_ref=125;
int error, last_error, MV,pid_l,pid_r,D,D1,D2,D3,P,Pd, bitSensor;
int Max_MV;
char lcdBuff[16];
void loop() {
 Kp = EEPROM.read(eepromKp);
 //max_pwm_ref = EEPROM.read(eepromSpeed);
 Kd = EEPROM.read(eepromKd);
 
  lcd.setCursor(0,0);
  lcd.print("Kp  Speed Kd");
  lcd.setCursor(0,1);
  sprintf(lcdBuff,"%3d %3d %3d",Kp, max_pwm_ref,Kd);
  lcd.print(lcdBuff);
 if(digitalRead(button3) == LOW)
 {
  
  delay(150);
  Kp++;
  EEPROM.write(eepromKp, Kp);
 }
 if(digitalRead(button2) == LOW)
 {
  
  delay(150);
  Kd++;
  EEPROM.write(eepromKd, Kd);
 }
 
 if(digitalRead(button4) == LOW)
 {
  while(1)
  {
    robotRun();
  }
 }
}
void readSens()
{
  sensorVal[0] = digitalRead(A0); sensorVal[1] = digitalRead(A1); sensorVal[2] = digitalRead(A2);
  sensorVal[3] = digitalRead(A3); sensorVal[4] = digitalRead(A5); sensorVal[5] = digitalRead(A4);
}
void robotRun()
{
  readSens();
  bitSensor = ((sensorVal[0]*1)+(sensorVal[1]*2)+(sensorVal[2]*4)+(sensorVal[3]*8)+(sensorVal[4]*16)+(sensorVal[5]*32));
  switch(bitSensor)
  {
    case 0b011111: error = -5; break;
    case 0b001111: error = -4; break;
    case 0b101111: error = -3; break;
    case 0b100111: error = -2; break;
    case 0b110111: error = -1; break;
    case 0b110011: error = 0; break;
    case 0b111011: error = 1; break;
    case 0b111001: error = 2; break;
    case 0b111101: error = 3; break;
    case 0b111100: error = 4; break;
    case 0b111110: error = 5; break; 
    case 0b111111: if(error > 3) {error=6;} 
                  if(error <- 3){error=-6;} break;
  }
  
  Max_MV = Kp*5;      //pembatasan nilai output dari hasil PID
//### rumus PID digital
  P = Kp * error;
        
  D1 = Kd*8;                         
  D2 = D1 / Ts;
  D3 = error - last_error;
  D = D2 * D3;

  last_error = error;

  MV = P + D;  
//=======================================//  
  if(MV>=-Max_MV && MV<=Max_MV)         //jika output PID tidak melebihi nilai pembatasan output PID maka robot akan berjalan
  {                                     //maju dengan pengaturan PWM kanan dan kiri
      pid_l  = max_pwm_ref - MV; 
      pid_r  = max_pwm_ref + MV; 
                          
      if (pid_l < 0) pid_l = 0;
      if (pid_l > 255) pid_l = 255;
      if (pid_r < 0) pid_r = 0;
      if (pid_r > 255) pid_r = 255;
      forward(pid_r,pid_l);  
  }  
  else if(MV<-Max_MV)                   //jika output PID lebih kecil dari nilai batasan output PID maka robot akan putar KANAN
  { 
     turnLeft(200,100);
  }   
  else if(MV>Max_MV)                    //jika output PID lebih besar dari nilai batasan output PID maka robot akan putar KIRI
  {
     turnRight(100,200); 
  }
  else
  {
     forward(pid_r,pid_l);
  } 
  lcd.setCursor(0,0);
  sprintf(lcdBuff,"%i%i%i%i%i%i", sensorVal[0],sensorVal[1],sensorVal[2],sensorVal[3],sensorVal[4],sensorVal[5]);
  lcd.print(lcdBuff);
  lcd.setCursor(0,1);
  sprintf(lcdBuff, "%2d %3d %3d", error, pid_l, pid_r);
  lcd.print(lcdBuff);
}
void forward(int valLeft, int valRight)
{
  digitalWrite(inAOne, LOW);
  digitalWrite(inBOne, HIGH);
  analogWrite(pwmOne, valLeft);
  digitalWrite(inATwo, HIGH);
  digitalWrite(inBTwo, LOW);
  analogWrite(pwmTwo, valRight);
}
void backward(int valLeft, int valRight)
{
  digitalWrite(inAOne, HIGH);
  digitalWrite(inBOne, LOW);
  analogWrite(pwmOne, valLeft);
  digitalWrite(inATwo, LOW);
  digitalWrite(inBTwo, HIGH);
  analogWrite(pwmTwo, valRight);
}
void turnRight(int valLeft, int valRight)
{
  digitalWrite(inAOne, LOW);
  digitalWrite(inBOne, HIGH);
  analogWrite(pwmOne, valLeft);
  digitalWrite(inATwo, LOW);
  digitalWrite(inBTwo, HIGH);
  analogWrite(pwmTwo, valRight);
}
void turnLeft(int valLeft, int valRight)
{
  digitalWrite(inAOne, HIGH);
  digitalWrite(inBOne, LOW);
  analogWrite(pwmOne, valLeft);
  digitalWrite(inATwo, HIGH);
  digitalWrite(inBTwo, LOW);
  analogWrite(pwmTwo, valRight);
}
void stopRun()
{
   digitalWrite(inAOne, HIGH);
  digitalWrite(inBOne, HIGH);
  analogWrite(pwmOne, 0);
  digitalWrite(inATwo, HIGH);
  digitalWrite(inBTwo, HIGH);
  analogWrite(pwmTwo, 0);
}

