int getar =0;
int sensor = A0;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  getar = analogRead(sensor);
  Serial.println(getar);
  if ( getar >=200) { 
    Serial.println("bergetar gan!");
    delay(1000);
  } 
  else {
    Serial.println("Menunggu getaran...");
    delay(1000);
  }
}
