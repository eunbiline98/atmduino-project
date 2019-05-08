/*ParkingL02.pde
Arduining.com 08 JUL 2012
Code used in the production of the Youtube material.
*/

#include <Servo.h>
Servo myservo;  // create servo object to control a servo

#define ServoM    12        //Connected to the servo motor.
#define Bright    11        //servo library disable PWM on pins 9 and 10.
#define Exit      9         //Pin connected to the EXIT button.
#define In        8         //Pin connected to the IN button.

#define BarLow    177       //Low position of the barrier.
#define BarUp     95        //Up position of the barrier.
#define CAPACITY  8         //Capacity of the parking lot.
#define INTEN     80        //Display intensity %

//Pins conections to segments (cathodes).
#define  segA  0
#define  segB  1
#define  segC  2
#define  segD  3
#define  segE  4
#define  segF  5
#define  segG  6

//Array with the segments to represent the decimal numbers (0-9).
byte segments[10] = {
// pgfedcba  <--- segments
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

void setup(){
  myservo.attach(ServoM);          // attaches the servo.

  pinMode(Exit, INPUT);           // set "EXIT" button pin to input
  pinMode(In, INPUT);             // set "IN" button pin to input
  digitalWrite(Exit, HIGH);       // Connect Pull-Up resistor.
  digitalWrite(In, HIGH);         // Connect Pull-Up resistor.
  pinMode(segA,OUTPUT);
  pinMode(segB,OUTPUT);
  pinMode(segC,OUTPUT);
  pinMode(segD,OUTPUT);
  pinMode(segE,OUTPUT);
  pinMode(segF,OUTPUT);
  pinMode(segG,OUTPUT);
  pinMode(Bright,OUTPUT);
  analogWrite(Bright,255*INTEN/100);
  myservo.write(BarLow);          //Barrier in the low position
//  delay(1000);
}

int  Available= 9;                    // Number of places available.

//================================================================
void loop(){
Display(Available);
if(digitalRead(In)==0)
{
  if(Available != 0){
    Available--;
    myservo.write(BarUp);
    delay(3000);
    myservo.write(BarLow);
    }
  }
if(digitalRead(Exit)==0)
{
  if(Available != CAPACITY){
    Available++;
    myservo.write(BarUp);
    delay(3000);
    myservo.write(BarLow);
    }
  }
}

/*-------------------------------------------------------------------
Put the segments according to the number.
--------------------------------------------------------------------*/
void Display(int number){
byte segs =  ~segments[number];        //"~" is used for commom anode.

digitalWrite(segA, bitRead(segs, 0) );
digitalWrite(segB, bitRead(segs, 1) );
digitalWrite(segC, bitRead(segs, 2) );
digitalWrite(segD, bitRead(segs, 3) );
digitalWrite(segE, bitRead(segs, 4) );
digitalWrite(segF, bitRead(segs, 5) );
digitalWrite(segG, bitRead(segs, 6) );
}
