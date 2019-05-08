
#include <Servo.h> //Library untuk Servo
#define trigPin 12 //Set Trigger HCSR04 di Pin digital 6
#define echoPin 13 //Set Echo HCSR04 di Pin digital 7
#define MAX_DISTANCE 500 //Set jarak maksimal

int LEDhijau = 3, LEDmerah = 2; //Set Pin LEDhijau dan LEDmerah
Servo myservo; //Buat object 1 buah motor servo

void setup() {
 Serial.begin (9600); //Kecepatan komunikasi serial
 pinMode(trigPin, OUTPUT); //Set pin Trigger sebagai output
 pinMode(echoPin, INPUT); //Set pin Echo sebagai input
 pinMode(LEDmerah, OUTPUT); //Set LEDmerah sebagai output
 pinMode(LEDhijau, OUTPUT); //Set LEDhijau sebagai output
 myservo.attach(9); //Set servo pada pin PWM 9
}

void loop() {
int duration, jarak,posisi=0,i;
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 jarak = (duration/2) / 29.1;
  Serial.print(jarak);
  Serial.println(" cm");

if(jarak<=15) // Jarak (Cm) dapat anda sesuaikan

 {
   digitalWrite(LEDhijau, LOW); //LEDhijau mati
   digitalWrite(LEDmerah, HIGH); //LEDmerah hidup
   myservo.write(90); //Posisi servo pada 180 derajat
   delay(450); //Delay
   digitalWrite(LEDmerah, LOW); //LEDmerah mati
   myservo.write(0); //Posisi servo pada 90 derajat
   delay(450); //Delay
   digitalWrite(LEDmerah, HIGH); //LEDmerah hidup
  
}

 else{ //Jika jarak lebih dari yang ditentukan
   digitalWrite(LEDmerah, LOW); //LEDmerah mati
   digitalWrite(LEDhijau, HIGH); //LEDhijau hidup
   myservo.write(90); //Posisi servo pada 90 derajat
 }
delay(450); //Delay
}
