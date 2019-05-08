#define sensorIn 6
#define sensorOut 7

int count = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(sensorIn,INPUT);
pinMode(sensorOut,INPUT);
pinMode(13,OUTPUT);
}
void IN(){
  count++;
  delay(500);
}

void OUT(){
  count--;
  delay(500);
}
void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(sensorIn))
  IN();
  if (digitalRead(sensorOut))
  OUT();

  Serial.println(count);

  if(count<=0){
    digitalWrite(13,LOW);
  }

else{
  digitalWrite(13,HIGH);
}
}
