#include <DS3231.h>
int stop, led1 = 12, led2= 13,menu,menit=57;

Time t;
DS3231 rtc (SDA,SCL);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  rtc.begin();
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int kode = Serial.read();
  if (kode =='a') {menu=1;}
  if (kode =='b') {menu=2;}

  if(menu==1){
Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating :)
  delay (1000);
    
     t = rtc.getTime();
    
     if (t.hour == 23 & t.min == menit & t.sec == 0){
            
            while(t.sec<33){

              if(t.sec<30)
              {
                digitalWrite(led1,HIGH);
                digitalWrite(led2,LOW);
                Serial.println("LED mode on");
                delay(1000);  
              }
              else
              {
                digitalWrite(led1,LOW);
                digitalWrite(led2,HIGH);
                delay(1000);
                digitalWrite(led2,LOW);
                delay(1000);
                Serial.println("LED mode blink");
                delay(1000);    
              }
              
              t.sec ++;
              
            }
            
      menit=menit+1;       
        
   }     

      else{
      
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
       Serial.println("LED mode off");
  }

  if(menu==2){
      while(t.sec<33){

              if(t.sec<30)
              {
                digitalWrite(led1,HIGH);
                digitalWrite(led2,LOW);
                Serial.println("LED mode on");
                delay(1000);  
              }
              else
              {
                digitalWrite(led1,LOW);
                digitalWrite(led2,HIGH);
                delay(1000);
                digitalWrite(led2,LOW);
                delay(1000);
                Serial.println("LED mode blink");
                delay(1000);    
              }
              
              t.sec ++;
              
            }
            
      menit=menit+1;       
        
   }     
  }
}
  

   
 
