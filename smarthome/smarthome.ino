const int sensorApi = 2;     
const int kipas = 3;
const int buzz = 5;
const int sensorGas = 6;

int deteksiApi = 0; 
int deteksiGas=0;
int kadarGas = 100;  
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(sensorApi,INPUT);
pinMode(sensorGas,INPUT);
pinMode(kipas,OUTPUT);
pinMode(buzz,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  deteksiApi = digitalRead(sensorApi);
deteksiGas = digitalRead(sensorGas);
Serial.println(sensorGas);
  if ((deteksiApi)==HIGH) {
    digitalWrite(kipas, HIGH);
    digitalWrite(buzz, HIGH);
  //  Serial.println("Bahaya...!!!");
  } 
  if (deteksiGas ==HIGH)
  {
     digitalWrite(kipas, HIGH);
    digitalWrite(buzz, HIGH);}
  else {
    digitalWrite(kipas, LOW);
      digitalWrite(buzz, LOW);
   // Serial.println("Bahaya...!!!");

  }
  delay(100);
}
