int A=8; //pin 8 - pin 11
int B=9;
int C=10;
int D=11; 
 
void setup(){
  //di deklarasikan sebagai output
pinMode(A,OUTPUT); pinMode(B,OUTPUT);
pinMode(C,OUTPUT); pinMode(D,OUTPUT);

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
}
 
void pergerakan_1(){
digitalWrite(A,0); 
digitalWrite(D,1);
digitalWrite(B,0);
digitalWrite(C,1); 
}
 
void pergerakan_2(){
digitalWrite(A,0); 
digitalWrite(D,0);
digitalWrite(B,1);
digitalWrite(C,1); 
}
 
void pergerakan_3(){
digitalWrite(A,1); 
digitalWrite(D,0);
digitalWrite(B,1);
digitalWrite(C,0);
}
 
void pergerakan_4(){
digitalWrite(A,1); 
digitalWrite(D,0);
digitalWrite(B,0);
digitalWrite(C,0);
}
 
void pergerakan(){
  pergerakan_1(); delay(1000);  
  pergerakan_2(); delay(1000);  
  pergerakan_3(); delay(1000);  
  pergerakan_4(); delay(1000);  
}
 
void loop(){
if (digitalRead(2) == LOW) {
       pergerakan_2();
}

if (digitalRead(3) == LOW) {
        pergerakan_3();
}

if (digitalRead(4) == LOW) {
        pergerakan_4();
}
}
