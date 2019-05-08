#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);


#define selA A0 
#define selB A1 
#define selC A2 
#define sensLeft  A4
#define sensRight A3
#define tombol1   2
#define tombol2   4
#define tombol3   0
#define tombol4   1
#define pwmKanan  10
#define pwmKiri   9
#define dirLA     8
#define dirLB     7
#define dirRA     5
#define dirRB     6
#define buzzer    3

int minSementara[13],maxSementara[13],minSensor[13],maxSensor[13];
int ulang,eAverage[13];
unsigned char valueLine[13],tombol[4];
char lcdBuff[16];
unsigned char Kp = 20; 
unsigned char Kd = 35;
unsigned char max_pwm_ref=180;
int rate_error, error, last_error, MV,pid_l,pid_r;
int binerLine[12],hexaSensor,turnKe;
int intersectionKe=1;
int tandaT,tandaL,mirrorIntersection,gantiBackground,countBlackWhite,jmlIntersection,cekPoinKe[10],tambahCekPoin;
int Max_MV;
byte cZero[8]=
{
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111, 
  B11111, 
};
byte cOne[8]=    
{
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.createChar (0, cZero);
  lcd.createChar (1, cOne);
  lcd.home();
  for(int out=5; out<=10; out++)
  {
  pinMode(out, OUTPUT);  
  }
  pinMode(tombol1, INPUT_PULLUP);
  pinMode(tombol2, INPUT_PULLUP);
  pinMode(tombol3, INPUT_PULLUP);
  pinMode(tombol4, INPUT_PULLUP);
  pinMode(selA, OUTPUT);
  pinMode(selB, OUTPUT);
  pinMode(selC, OUTPUT);

}


void loop(){

  awal:
  actifMux();
  lcd.setCursor(0,0);
  lcd.print(" <   ^   v    > ");
  lcd.setCursor(0,1);
  lcd.print("Set Run Sens PID");
  if(digitalRead(tombol1)==0)
  {
     delay(150); tune();lcd.clear();goto setKp;
  }       
  if(digitalRead(tombol2)==0)
  {
    delay(150); tune();lcd.clear();goto setSens;
  }
  if(digitalRead(tombol3)==0)
  {
    delay(150); tune();lcd.clear();goto freeRunning; 
  } 
  if(digitalRead(tombol4)==0)
  {    
    delay(150); tune();lcd.clear(); goto freeRunning;
  }                                      
  goto awal;
setKp:
  actifMux();           
  Kp=EEPROM.read(51);
  if(digitalRead(tombol2)==0){Kp++;delay(10);lcd.clear();}
  if(digitalRead(tombol3)==0){Kp--;delay(10);lcd.clear();}
  lcd.setCursor(0,0);
  lcd.print("Bismillah...");
  lcd.setCursor(0,1);
  sprintf(lcdBuff,"Nilai KP:%i",Kp);
  lcd.print(lcdBuff);
  EEPROM.write(51, Kp);
  delay(100);
  if(digitalRead(tombol1)==0)
  {
    delay(150);tune();lcd.clear();goto setKd;
  }
  if(digitalRead(tombol4)==0)
  {
    delay(150);tune();lcd.clear();goto awal;
  }
  goto setKp;
setKd:
  actifMux();           
  Kd=EEPROM.read(52);
  if(digitalRead(tombol2)==0){Kd++;delay(10);lcd.clear();}
  if(digitalRead(tombol3)==0){Kd--;delay(10);lcd.clear();}
  lcd.setCursor(0,0);
  lcd.print("Bismillah...");
  lcd.setCursor(0,1);
  sprintf(lcdBuff,"Nilai KD:%i",Kd);
  lcd.print(lcdBuff);
  EEPROM.write(52, Kd);
  delay(100);
  if(digitalRead(tombol1)==0)
  {
    delay(150);tune();lcd.clear();goto pwmReff;
  }
  if(digitalRead(tombol4)==0)
  {
    delay(150);tune();lcd.clear();goto setKp;
  }
  goto setKd;
pwmReff:
  actifMux();           
  max_pwm_ref=EEPROM.read(53);
  if(digitalRead(tombol2)==0){max_pwm_ref++;delay(10);lcd.clear();}
  if(digitalRead(tombol3)==0){max_pwm_ref--;delay(10);lcd.clear();}
  lcd.setCursor(0,0);
  lcd.print("Bismillah...");
  lcd.setCursor(0,1);
  sprintf(lcdBuff,"Pwm Reff:%i",max_pwm_ref);
  lcd.print(lcdBuff);
  EEPROM.write(53, max_pwm_ref);
  delay(100);
  if(digitalRead(tombol1)==0)
  {
    delay(150);tune();lcd.clear();goto awal;
  }
  if(digitalRead(tombol4)==0)
  {
    delay(150);tune();lcd.clear();goto setKd;
  }
  goto pwmReff;
setSens:
  actifMux();
  lcd.setCursor(2,0);
  lcd.print("< ^   v  >");
  lcd.setCursor(2,1);
  lcd.print("R 01 Rec L");
  if(digitalRead(tombol1)==0)
  {
   delay(150); lcd.clear();tune();
   lcd.setCursor(0,0);
   lcd.print("Read Left Sens");
   delay(1000);
   lcd.clear();
   while(1)
   {
    readLeftSensor();
   }
  }       
  if(digitalRead(tombol2)==0)
  {
    delay(150); lcd.clear();tune();
    lcd.setCursor(0,0);
    lcd.print("Record Data");
    delay(1000);
    lcd.clear();
    actifMux();
    recordBack();recordLine();
    averageLine();
  }
  if(digitalRead(tombol3)==0)
  {
    delay(150); lcd.clear();tune();
    lcd.setCursor(0,0);
    lcd.print("Convert Logic");
    delay(1000);
    lcd.clear();
    while(1)
    {
    convertLogic(); 
    }
  } 
  if(digitalRead(tombol4)==0)
  {    
    delay(150); lcd.clear();tune();
    lcd.setCursor(0,0);
    lcd.print("Read Right Sens");
    delay(1000);
    lcd.clear();
    while(1)
    {
    readRightSensor();
    }
  }    
  goto setSens;
  //eeprom untuk path planning mulai di 56

freeRunning:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Free Running");
  delay(2000);
  lcd.clear();
  while(1)
  {
  RUN();
  }
  goto freeRunning;

}
void TurnR(int pwmL, int pwmR)
{
  digitalWrite(dirLA, 1);digitalWrite(dirLB, 0);analogWrite(pwmKiri, pwmL);
  digitalWrite(dirRA, 1);digitalWrite(dirRB, 0);analogWrite(pwmKanan, pwmR); 
}
void forward(int pwmL, int pwmR)
{
  digitalWrite(dirLA, 0);digitalWrite(dirLB, 1);analogWrite(pwmKiri, pwmL);
  digitalWrite(dirRA, 1);digitalWrite(dirRB, 0);analogWrite(pwmKanan, pwmR); 
}
void TurnL(int pwmL, int pwmR)
{
  digitalWrite(dirLA, 0);digitalWrite(dirLB, 1);analogWrite(pwmKiri, pwmL);
  digitalWrite(dirRA, 0);digitalWrite(dirRB, 1);analogWrite(pwmKanan, pwmR); 
}
void stopRun()
{
  digitalWrite(dirLA, 1);digitalWrite(dirLB, 1);analogWrite(pwmKiri, 255);
  digitalWrite(dirRA, 1);digitalWrite(dirRB, 1);analogWrite(pwmKanan, 255); 
}
void switchMUX(int a, int b, int c)
{
  digitalWrite(selA, a);
  digitalWrite(selB, b);
  digitalWrite(selC, c); 
}
void actifMux()
{
  switchMUX(0,0,0);
  valueLine[2] = analogRead(4); 
  tombol[1] = analogRead(3);
  switchMUX(0,0,1);
  valueLine[4] = analogRead(4); 
  tombol[0] = analogRead(3); 
  switchMUX(0,1,0);
  valueLine[0] = analogRead(4);  
  tombol[3] = analogRead(3); 
  switchMUX(0,1,1);
  valueLine[5] = analogRead(4); 
  tombol[2] = analogRead(3);
  switchMUX(1,0,0);
  valueLine[1] = analogRead(4);  
  valueLine[10] = analogRead(3); 
  switchMUX(1,0,1);
  valueLine[7] = analogRead(4);
  valueLine[8] = analogRead(3);
  switchMUX(1,1,0);
  valueLine[3] = analogRead(4);  
  valueLine[11] = analogRead(3);
  switchMUX(1,1,1);
  valueLine[6] = analogRead(4); 
  valueLine[9] = analogRead(3);
}

void tune()
{
  analogWrite(buzzer, 100);
  delay(150);
  analogWrite(buzzer, 0);
}

void recordBack()
{
  lcd.setCursor(0,0);
  lcd.print("Record Back");
  for(int i=0; i<=11; i++)
  {
  lcd.setCursor(0,1);
  sprintf(lcdBuff, "ke: %i-->%3d",i,valueLine[i]);
  lcd.print(lcdBuff);
  EEPROM.write(i, valueLine[i]);//valueLine[i] --> baca postingan 16 channel sensor garis
  delay(250);
  }
}
void recordLine()
{
  lcd.setCursor(0,0);
  lcd.print("Record Line");
  for(int i=0; i<=11; i++)
  {
  lcd.setCursor(0,1);
  sprintf(lcdBuff, "ke: %i-->%3d",i,valueLine[i]);
  lcd.print(lcdBuff);
  EEPROM.write(i+12, valueLine[i]);//valueLine[i] --> baca postingan 16 channel sensor garis
  delay(250);
  }
}

void averageLine()
{
  for(int i=0; i<=11; i++)
  {
  lcd.setCursor(0,0);
  lcd.print(i);
  maxSensor[i] = EEPROM.read(i);
  minSensor[i] = EEPROM.read(i+12);
  eAverage[i]=(maxSensor[i]+minSensor[i])/2;
  EEPROM.write(i+24,eAverage[i]);
  }
}
void readLeftSensor()
{
  actifMux();
  lcd.setCursor(0,0);
  sprintf(lcdBuff, "%3d %3d %3d %3d", valueLine[8],valueLine[9],valueLine[10],valueLine[11]);
  lcd.print(lcdBuff);
  lcd.setCursor(0,1);
  sprintf(lcdBuff, "%3d %3d %3d %3d", tombol[0],tombol[1],tombol[2],tombol[3]);
  lcd.print(lcdBuff);
}
void readRightSensor()
{
  actifMux();
  lcd.setCursor(0,0);
  sprintf(lcdBuff, "%3d %3d %3d %3d", valueLine[0],valueLine[1],valueLine[2],valueLine[3]);
  lcd.print(lcdBuff);
  lcd.setCursor(0,1);
  sprintf(lcdBuff, "%3d %3d %3d %3d", valueLine[4],valueLine[5], valueLine[6],valueLine[7]);
  lcd.print(lcdBuff);
}
void convertLogic()
{
  for(int i=0; i<=11; i++)
  {
  actifMux();
  if(valueLine[i]<EEPROM.read(i+24))
  {
    binerLine[11-i] = 1;
    lcd.setCursor(13-i,1);
    lcd.write(byte(1)); 
  }
  else
  {
    binerLine[11-i] = 0;
    lcd.setCursor(13-i,1);
    lcd.write(byte(0)); 
  }

  }
}
void convertBiner()
{
  convertLogic();
  hexaSensor = ((binerLine[1]*1)+(binerLine[2]*2)+(binerLine[3]*4)+(binerLine[4]*8)+(binerLine[5]*16)
        +(binerLine[6]*32)+(binerLine[7]*64)+(binerLine[8]*128)+(binerLine[9]*256)+(binerLine[10]*512));
}
void RUN()
{
  Kp = EEPROM.read(51);
  Kd = EEPROM.read(52);
  max_pwm_ref = EEPROM.read(53);
  convertBiner();
  switch(hexaSensor)
  {
  case 0b0000000001: error = 9;break;//---->sensor sebelah kiri
  case 0b0000000011: error = 8;break;
  case 0b0000000010: error = 7;break;
  case 0b0000000110: error = 6;break;
  case 0b0000000100: error = 5;break;
  case 0b0000001100: error = 4;break;
  case 0b0000001000: error = 3;break;
  case 0b0000011000: error = 2;break;
  case 0b0000010000: error = 1;break;   
  case 0b0000110000: error = 0;break;
  case 0b0000100000: error = -1;break;
  case 0b0001100000: error = -2;break;
  case 0b0001000000: error = -3;break;
  case 0b0011000000: error = -4;break;
  case 0b0010000000: error = -5;break;
  case 0b0110000000: error = -6;break;
  case 0b0100000000: error = -7;break;
  case 0b1100000000: error = -8;break;
  case 0b1000000000: error = -9;break;//---->sensor sebelah kanan
  case 0b0000000000:
    if(error>=8)
    {
    error = 9;
    }
    if(error<=-8)
    {
    error = -9;
    }
  break; 

  }
  Max_MV = Kp*9;
  rate_error = error - last_error;   
  MV = (Kp*error) + (Kd*rate_error);  
  last_error = error;  
  if(MV>=-Max_MV && MV<=Max_MV)  
  {   
    pid_l  = max_pwm_ref - MV;  
    pid_r  = max_pwm_ref + MV;  

    if (pid_l < 0) pid_l = 0;
    if (pid_l > 255) pid_l = 255;
    if (pid_r < 0) pid_r = 0;
    if (pid_r > 255) pid_r = 255;
    forward(pid_r,pid_l);  
  }  
  else if(MV<-Max_MV)
  { 
   TurnR(200,100);
  }   
  else if(MV>Max_MV)
  {
   TurnL(100,200); 
  }
  else
  {
   forward(pid_r,pid_l);
  } 
  lcd.setCursor(0,0);
  sprintf(lcdBuff, "%3d %3d %2d %2d",pid_l,pid_r,intersectionKe,error);
  lcd.print(lcdBuff);
}
