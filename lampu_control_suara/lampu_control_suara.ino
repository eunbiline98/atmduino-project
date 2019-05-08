boolean lampON=false;
int inSensor = 8;
int lamp = 9;
void setup(){
pinMode(inSensor, INPUT);
pinMode(lamp, OUTPUT);
digitalWrite(lamp, LOW);
}
void loop(){
if (digitalRead(inSensor)==0){
if(lampON==false){
digitalWrite(lamp, HIGH);
lampON=true;
delay(2000);
}
else{
digitalWrite(lamp, LOW);
lampON=false;
delay(2000);
}
}
}
