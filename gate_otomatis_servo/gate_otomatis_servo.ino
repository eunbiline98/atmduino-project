#include <Servo.h> 

//#define Up     40
//#define Down   0

#define trigPin   10
#define echoPin   13
#define Servo1    9   // Sinyal Servo1
#define Bright    11  // Anoda 7Segment

#define Kapasitas 9   // Jumlah Maks yang bisa di masuk
#define Light     10  // Pengaturan Terang 7 Segment (%)
  
#define A 2     
#define B 3     
#define C 4     
#define D 5     // Pin Arduino To 7Segment ABCDEFG
#define E 6
#define F 7
#define G 8

long duration, distance;
int i=0;
int Tersedia=5;   // Variabel Menentukan yang tersedia saat ini
int penuh;
const int buzzer = 12;

byte segmen [10] = {   // Array untuk urutan Tampilan angka 7Segment
// PGFEDCBA <--- Urutan 7segment
  B00111111, // number 0
  B00000110, // number 1
  B01011011, // number 2
  B01001111, // number 3
  B01100110, // number 4
  B01101101, // number 5
  B01111101, // number 6
  B00000111, // number 7
  B01111111, // number 8
  B01101111  // number 9
};

byte Full [] = {
  B01110001      // Tampilan Kapasitas Penuh (F)
};

Servo servo1;

void setup(){
  Serial.begin(9600);
  servo1.attach(9);  // turn on servo1
  servo1.write(0);   // Set 0 servo1
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(E,OUTPUT);
  pinMode(F,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(Bright,OUTPUT);
  pinMode(buzzer, OUTPUT);
  tone(buzzer, 2000); // Send 2KHz sound signal...
  delay(1000);         
  noTone(buzzer);     // Stop sound...
  analogWrite(Bright,255*Light/100);
  }

void loop(){
  analogWrite(Bright,255*Light/100);
  Display(Tersedia);
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print("Jarak: ");
  Serial.println(distance);

  if (distance < 16) 
  {
    delay (500);
    if(Tersedia == 0){
      if(distance < 16){
        analogWrite(Bright,255*Light/100);
        Tampil(penuh);
        tone(buzzer, 2000); // Send 2KHz sound signal...
        delay(1500);     
        noTone(buzzer);     // Stop sound...
        //delay(1000);      // ...for 1sec}
        //delay(200);
        analogWrite(Bright,255*Light/100);
        Tampil(penuh);;
        delay(1000);}
    }
    if (Tersedia != 0){
      Tersedia--;
      for (i=0; i<=40; i++){
        servo1.write(i);
        delay(15);}
    delay(3000);
    for (i=40; i>=0; i--){
      servo1.write(i);
      delay(10);}
    }
  }
}

void Display(int number){
  byte seg =  ~segmen[number];        //"~" is used for commom anode.
  digitalWrite(A, bitRead(seg, 0) );
  digitalWrite(B, bitRead(seg, 1) );
  digitalWrite(C, bitRead(seg, 2) );
  digitalWrite(D, bitRead(seg, 3) );
  digitalWrite(E, bitRead(seg, 4) );
  digitalWrite(F, bitRead(seg, 5) );
  digitalWrite(G, bitRead(seg, 6) );
  }
  
void Tampil(int number){
  byte seg =  ~Full[number];          //"~" is used for commom anode.
  digitalWrite(A, bitRead(seg, 0) );
  digitalWrite(B, bitRead(seg, 1) );
  digitalWrite(C, bitRead(seg, 2) );
  digitalWrite(D, bitRead(seg, 3) );
  digitalWrite(E, bitRead(seg, 4) );
  digitalWrite(F, bitRead(seg, 5) );
  digitalWrite(G, bitRead(seg, 6) );
}

