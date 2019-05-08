#include <Servo.h> 
// membuat nama objek servo untuk pengontrolan servo 
Servo servo1;         
// variable untuk menyimpan posisi servo 
int awal = 0;
int buttonStatus = 1;

int sensorPin = A0;
int sensorValue = 0;
#define button 7          
void setup() 
{ 
 Serial.begin(9600);
 servo1.attach(8); // data di pin 9   
 pinMode(button,INPUT_PULLUP); 
} 
void loop() 
{ 
   sensorValue = analogRead(sensorPin); // read the value from the sensor
Serial.println(sensorValue);
  buttonStatus = digitalRead(button);
   if (buttonStatus == LOW) {
 // start dari 0 derajar sampai 90 derajat 
 for(awal = 0; awal < 180;)  
 {
  // pada posisi 1 derajat
  // memberitahu servo untuk pergi ke posisi awal
  servo1.write(awal);
  // tunggu untuk pencapaian posisi servo    
  delay(10);                  
 } 
 }
 else{
  
 }
}

