// out1 & in1 = button
// in & out   = sensor IR
#define out1  22
#define in1   24
#define in    26
#define out   28
#include <Stepper.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);
// Number of steps per internal motor revolution 
const float STEPS_PER_REV = 32; 
 
//  Amount of Gear Reduction
const float GEAR_RED = 64;
 
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;

// Number of Steps Required
int StepsRequired;
 
Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);
 
int state=0;
int lastState=0;
int counter=0;
int value = 0;
int kondisi=0;

// slot parkir
#define s1  A6
#define s2  A7
#define s3  A8
#define s4  A9
#define s5  A10
#define s6  A11
#define s7  A12
#define s8  A13
#define s9  A14
#define s10 A15
// indikator
#define Led1  53
#define Led2  51
#define Led3  49
#define Led4  47
#define Led5  45
#define Led6  43
#define Led7  41
#define Led8  39
#define Led9  37
#define Led10 35

int nilait=350;

int slot1=0;
int slot2=0;
int slot3=0;
int slot4=0;
int slot5=0;
int slot6=0;
int slot7=0;
int slot8=0;
int slot9=0;
int slot10=0;

void setup() {
  // put your setup code here, to run once:
lcd.begin(16,2);
pinMode(in , INPUT_PULLUP);
pinMode(out, INPUT_PULLUP);
pinMode(in1,INPUT);
pinMode(out1,INPUT);

// led 
pinMode(Led1,OUTPUT);
pinMode(Led2,OUTPUT);
pinMode(Led3,OUTPUT);
pinMode(Led4,OUTPUT);
pinMode(Led5,OUTPUT);
pinMode(Led6,OUTPUT);
pinMode(Led7,OUTPUT);
pinMode(Led8,OUTPUT);
pinMode(Led9,OUTPUT);
pinMode(Led10,OUTPUT);

  // Print a message to the LCD.
  lcd.backlight();
  // Print a message to the LCD.
  lcd.backlight();
    lcd.setCursor(9, 1);
  delay(1500);
lcd.clear();
Serial.begin(9600);
}

void loop() {
// portal sensor IR Plus button
  if(digitalRead(in)==LOW){
    state=1;
  }
  else if(digitalRead(out)==LOW){
    state=2;
  }
    else if(digitalRead(in1)==LOW){
    state=3;
  }
    else if(digitalRead(out1)==LOW){
    state=4;
  }
  
if(state != lastState){
  if(value!=10){
    //angkat portal
  if(state==1 && kondisi==0){
   // value++;
    StepsRequired  =  - STEPS_PER_OUT_REV / 4; 
    steppermotor.setSpeed(500);   
    steppermotor.step(StepsRequired);
    kondisi=1;
  }}
  if(value!=0){
  if(state==2 && kondisi == 0){
    
    StepsRequired  =  - STEPS_PER_OUT_REV / 4; 
    steppermotor.setSpeed(500);   
    steppermotor.step(StepsRequired);
    kondisi=2;
  }}
  
  //tutup portal
  if(state==3 && kondisi==1) {
    value++;
   StepsRequired  =   STEPS_PER_OUT_REV / 4;   
  steppermotor.setSpeed(500);  
  steppermotor.step(StepsRequired); 
   //delay(100);
   kondisi=0;
  }
    if(state==4 && kondisi==2) {
      value--;
   StepsRequired  =   STEPS_PER_OUT_REV / 4;   
  steppermotor.setSpeed(500);  
  steppermotor.step(StepsRequired); 
   //delay(100);
   kondisi=0;
  }  
  

 if(value==10 && state==1){
        lcd.setCursor(0, 1);
        lcd.print("parkir penuh");
        delay(1500);
        lcd.clear();
          lcd.setCursor(0, 0);
  lcd.print("PARLING LOT");
    lcd.setCursor(0, 1);
  lcd.print("Sisa Parkir:");
  }
  
  
  lastState=state;

// slot parkir
}
 if(slot1>=nilait){
    digitalWrite(Led1,HIGH);
   
 }
 else if(slot1<=nilait){
    digitalWrite(Led1,LOW);  
 }
 if(slot2>=nilait){
     digitalWrite(Led2,HIGH);
      
 }
 else if(slot2<=nilait){
    digitalWrite(Led2,LOW);
 }
 
 if(slot3>=200){
    digitalWrite(Led3,HIGH);  
 }
 else if(slot3<=200){
      digitalWrite(Led3,LOW);
 }
 
 if(slot4>=nilait){
     digitalWrite(Led4,HIGH); 
 }
 else if(slot4<=nilait){
      digitalWrite(Led4,LOW);
 }
 
 if(slot5>=nilait){
      digitalWrite(Led5,HIGH);
 }
 else if(slot5<=nilait){
      digitalWrite(Led5,LOW);
 }
 
 if(slot6>=nilait){
      digitalWrite(Led6,HIGH);
 }
 else if(slot6<=nilait){
      digitalWrite(Led6,LOW);
 }
 
 if(slot7>=nilait){
      digitalWrite(Led7,HIGH);
 }
 else if(slot7<=nilait){
      digitalWrite(Led7,LOW);
 }
 
 if(slot8>=nilait){
      digitalWrite(Led8,HIGH);
 }
 else if(slot8<=nilait){
     digitalWrite(Led8,LOW);
 }
 
 if(slot9>=nilait){
      digitalWrite(Led9,HIGH);
 }
 else if(slot9<=nilait){
     digitalWrite(Led9,LOW);
 }
 
 if(slot10>=nilait){
    digitalWrite(Led10,HIGH);
 }
 else if(slot10<=nilait){
   digitalWrite(Led10,LOW);
 }
}

