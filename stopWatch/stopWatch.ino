//created by Jimmi Kardo Sitepu
//Founder of https://mikroavr.com
//make easy project seven segment with modul mikro7
//contact me any qustion to +6285207770631 --> whatsapp, SMS
#include <mikro7.h>
// Arduino pin configuration to modul mikro7
// D7 connected to Data Pin
// D8 connected to latch pin
// DS connected to clock pin
mikro7 mikro(7, 8, 9); // dis(data, latch, clock
int i;
char hold0 = 0;
char hold1 = 0;
char hold2 = 0;
char data0, data1, data2;
 
#define READY 0
#define START 1
#define STOP 2
#define RESET 3
#define TIPE_TIME 500 // speed of stop watch
 
char state = 0;
unsigned long get_time, get_time2;
unsigned long cur_time0;
unsigned long cur_time1;
unsigned long hold_time, hold_time2, run_time;
 
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  mikro.off();
}
void loop() {
  // put your main code here, to run 
  Serial.begin(9600);
  key();
  display7();
}
void key(){
  data0 = digitalRead(A0);
  data1 = digitalRead(A1);
  data2 = digitalRead(A2);
  if ( data0 == 0){
    if(hold0 == 0){
    hold0 = 1;  
    state = START;
  }
  }
  else{
    hold0 = 0;
  }
 
  if ( data1 == 0){
    if(hold1 == 0){
    hold1 = 1;  
    state = STOP;
  }
  }
  else{
    hold1 = 0;
  }
 
  if ( data2 == 0){
    if(hold2 == 0){
    hold2 = 1;  
    state = RESET;
  }
  }
  else{
    hold2 = 0;
  }
}
 
void get_clock(){
  switch(state){
    case READY:
      get_time = 0;
      hold_time = 0;
    break;
 
    case START:
      cur_time0 = millis()/TIPE_TIME;
      run_time = (cur_time0 - cur_time1);
      hold_time = run_time;
      get_time = hold_time + hold_time2;
    break;
 
    case STOP:
      cur_time1 = millis()/TIPE_TIME;  
      hold_time2 = get_time;   
    break;   
 
    case RESET:
      cur_time1 = millis()/TIPE_TIME;
      get_time = 0; hold_time = 0; hold_time2 = 0;
      //state = READY;
    break;
  }
}
 
void display7(){
  get_clock();
  switch(state){
    case READY:
      mikro.display(get_time,NOT);
    break;
 
    case START:
      mikro.display(get_time,NOT);
    break;
 
    case STOP:
      mikro.display(get_time,NOT);
    break;
 
    case RESET:
      mikro.display(get_time,NOT);
    break;
  }
}
