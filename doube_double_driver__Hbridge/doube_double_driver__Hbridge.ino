int i;
void setup() {
  // put your setup code here, to run once:
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);

pinMode(10,INPUT_PULLUP);
pinMode(11,INPUT_PULLUP);
pinMode(12,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(10)==LOW){

//motor1
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
//motor2
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
//motor3
    digitalWrite(7,LOW);
    digitalWrite(6,HIGH);
//motor4
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
  }
 if (digitalRead(11)==LOW){

//motor1
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
//motor2
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
//motor3
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
//motor4
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
  }
  if (digitalRead(12)==LOW){
    analogWrite(3,100);
    analogWrite(5,100);
    analogWrite(6,100);
    analogWrite(9,100);
  }
}
