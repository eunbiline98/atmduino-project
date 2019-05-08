#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);


int pinA = 3;  // Connected to CLK on KY-040
 int pinB = 4;  // Connected to DT on KY-040
 int encoderPosCount = 0; 
 int pinALast;  
 int aVal;

 boolean bCW;


 void setup() { 
   pinMode (pinA,INPUT);
   pinMode (pinB,INPUT);
   /* Read Pin A
   Whatever state it's in will reflect the last position   
   */
   pinALast = digitalRead(pinA);   
   Serial.begin (9600);
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight

 } 

 void loop() { 

Serial.begin(9600);
 
 
//  lcd.backlight();
//  delay(250);
//  lcd.noBacklight();
//  delay(250);
//  lcd.backlight();

  int kel=18.9;
 int bag=28;

float rumus =(kel)*(encoderPosCount)/bag;
  
   aVal = digitalRead(pinA);
   if (aVal != pinALast){ 
    
     if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
       encoderPosCount ++;
       bCW = true;
     } else {// Otherwise B changed first and we're moving CCW
       bCW = false;
       encoderPosCount--;
     }
  lcd.setCursor(0,0);
  //lcd.clear();
   lcd.print ("PUTARAN:");
     // delay(1000);
     if (bCW == true){

      lcd.setCursor(0,0);
       lcd.print ("MAJU              ");
       //delay(1000);
     }
     if  (bCW == false){
      
      lcd.setCursor(0,0);
       lcd.print("MUNDUR            ");
        
     }

     if  ( rumus <= 0 ){
      lcd.setCursor(0,0);
       lcd.print("STOP           ");
      
     }

     lcd.setCursor(0,1);
     lcd.print("POSISI:");
      lcd.print(float (kel)*(encoderPosCount)/bag);;
     lcd.print("CM   ");
     //delay(100);
     
   }      
   pinALast = aVal;  
  // delay(100);
 } 

