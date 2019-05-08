#include <ArduinoRobotx.h>
#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>

long startTime ;
int secTime;

int randTurn;
/*
 *1. kanan
 *2. lurus
 *3. kiri
 */

int waktu[20];
int T=0;

int tengah=500;
int sen[5];
unsigned char sensor;
int PV;
int error,P,D1,D3,last_error;
float D2,Pd,D,pwmL,pwmR;

void setup() {
  // initialize the robot
  Robot.begin();

  // initialize the serial port
  Serial.begin(9600);

  randomSeed(analogRead(0));

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
}
void convertLogic(){
  Robot.updateIR();
  for(int i=0;i<5;i++){
    if(Robot.IRarray[i]>=tengah){
      sen[i]=0;
    }else{
        sen[i]=1;
     }
  }
}

void convertBiner(){
  sensor=(sen[4]*1)+(sen[3]*2)+(sen[2]*4)+(sen[1]*8)+(sen[0]*16);
}
void PID(){
        convertLogic();
        convertBiner();
        switch(sensor){       
              //deteksi 1 sensor pergaris
              case 0b00001:
                      PV = -4;
                      break;
              case 0b00011:
                      PV = -3;
                      break;
              case 0b00010:
                      PV = -2;
                      break;
              case 0b00110:
                      PV = -1;
                      break;
              case 0b00100:
                      PV = 0;
                      break;
              case 0b01100:
                      PV = 1;
                      break;
              case 0b01000:
                      PV = 2;
                      break;
              case 0b11000:
                      PV = 3;
                      break;
              case 0b10000:
                      PV = 4;
                      break;
                   
              case 0b00000:        // loss
                          if (PV <= -3) 
                          {
                              PV = -5;
                          } 
                          else if(PV >= 3)
                          {
                              PV = 5;
                          }   
                          else
                          {
                            Robot.motorsStop();
                            delay(100);
                            PV = 5;  
                          }
                          break;
              
          }
          error = 0 - PV;
          P = (5 * error);
        
          D1 = 50 * 8;                         
          D2 = D1 / 15;
          D3 = error - last_error;
          D = D2 * D3;
        
          last_error = error;
          
          Pd = P + D;
          
          if(Pd==0){
            //Serial.println("0");
            pwmL=pwmR=150;
            Robot.motorsWrite(pwmL,pwmR);
            }
          else if(Pd>0 && Pd<=20){
            //Serial.println("1");
            pwmL=150-Pd;
            pwmR=150+Pd;
            if(pwmL > 250)  pwmL=250;
            if(pwmL < 10)   pwmL=0;
            if(pwmR > 250)  pwmR=250;
            if(pwmR < 10)   pwmR=0;
            Robot.motorsWrite(pwmL,pwmR);
            }
          else if(Pd<0 && Pd>=-20){
            //Serial.println("2");
            pwmL=150-Pd;
            pwmR=150+Pd;
            if(pwmL > 250)  pwmL=250;
            if(pwmL < 10)   pwmL=0;
            if(pwmR > 250)  pwmR=250;
            if(pwmR < 10)   pwmR=0;
            Robot.motorsWrite(pwmL,pwmR);
            }
          else if(Pd>20){
            //Serial.println("3");
            Robot.motorsWrite(-100,100);
            }
          else if(Pd<20){
            //Serial.println("4");
            Robot.motorsWrite(100,-100);
            }
          else{
            //Serial.println("5");
            Robot.motorsWrite(pwmL,pwmR);
            }
          
          //Serial.print(error);
          
          //delay(500);
           
          for (int i = 0; i < 5; i++) {
          Serial.print(Robot.IRarray[i]);
          Serial.print(" ");
        }
        Serial.println("");
      
}
void loop() {
  
 //read the pushbutton value into a variable
  int tDown   = digitalRead(A0);
  int tRight  = digitalRead(A1);
  int tOK     = digitalRead(A2);
  int tLeft   = digitalRead(A3);
  int tUp     = digitalRead(A4);  

mulai:
  if(tDown == LOW)
  {
    while(1)
    {
      convertLogic();
      convertBiner();
      PID();
      if ( sensor!=0b11111){
        PID();
      }
      goto mulai;
    }
  }
}
