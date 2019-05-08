int led = 1 ;
int sensor = 2 ;
void setup() {
  // put your setup code here, to run once:
pinMode(led, OUTPUT);
pinMode(sensor, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

if (digitalRead(sensor)==HIGH){
  digitalWrite(led, HIGH);
}
else {
  digitalWrite(led, LOW);
}
}
