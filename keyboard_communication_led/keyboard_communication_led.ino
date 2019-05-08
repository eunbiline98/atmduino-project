int lamp1 = 12,lamp2 = 13,lamp3 = 10,databaca;

void setup() {
Serial.begin(9600);
pinMode(lamp1, OUTPUT);
pinMode(lamp2, OUTPUT);
pinMode(lamp3, OUTPUT); 
}
 
void loop()
{
if (Serial.available())
{
int bacadata = Serial.read();
if (bacadata =='a') {databaca=1;}
if (bacadata =='b') {databaca=2;}
if (bacadata =='c') {databaca=3;}
if (bacadata =='d') {databaca=4;}

 
if(databaca==1)
runn:
{
digitalWrite(lamp1, HIGH);
delay(100);
digitalWrite(lamp1, LOW);
delay(100);
digitalWrite(lamp2, HIGH);
delay(100);
digitalWrite(lamp2, LOW);
delay(100);
digitalWrite(lamp3, HIGH);
delay(100);
digitalWrite(lamp3, LOW);
delay(100);
Serial.println("LED mode running");
loop();
goto runn;
}
 
if(databaca==2)
flipflop: 
{
digitalWrite(lamp1, LOW);
digitalWrite(lamp2, LOW);
digitalWrite(lamp3, LOW);
delay(500);
digitalWrite(lamp1, HIGH);
digitalWrite(lamp2, HIGH);
digitalWrite(lamp3, HIGH);
delay(500);
Serial.println("LED mode flip flop");
loop();
goto flipflop;
}

if(databaca==3)
mix:
{
digitalWrite(lamp1, HIGH);
digitalWrite(lamp2, LOW);
digitalWrite(lamp3, HIGH);
delay(500);
digitalWrite(lamp1, LOW);
digitalWrite(lamp2, HIGH);
digitalWrite(lamp3, LOW);
delay(500);
Serial.println("LED mode mix");
loop();
goto mix;
}
 
if(databaca==4)
modeoff:
{
digitalWrite(lamp1,LOW);
digitalWrite(lamp2,LOW);
digitalWrite(lamp3,LOW);
delay(1000);
Serial.println("LED mode off");
loop();
goto modeoff; }
}
}
