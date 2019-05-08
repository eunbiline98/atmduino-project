
const int relay2 = 10;
const int relay3 = 11;
const int relay4 = 12;
void setup() {
  // put your setup code here, to run once:
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 
   digitalWrite(relay2,HIGH);
  delay(1000);
  digitalWrite(relay2,LOW);
  delay(2000);
   digitalWrite(relay3,HIGH);
  delay(1000);
  digitalWrite(relay3,LOW);
  delay(2000);
   digitalWrite(relay4,HIGH);
  delay(1000);
  digitalWrite(relay4,LOW);
  delay(2500);
}
