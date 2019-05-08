const int analogInPin = A0;  // pin potensiometer
const int analogOutPin = 13; // pin indikator

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

void setup() {
  
  Serial.begin(9600);
}

void loop() {

  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(analogOutPin, outputValue);

// keluaran Vout dari sensor
   int nilai = analogRead (A0);
   float tegangan_hasil = 5.0 * nilai / 1024;
  //tampilan hasil output nilai analog
  Serial.print ("Vout=");
  Serial.print (tegangan_hasil);
  Serial.print (" V");
  
// tampilan hasil nilai digital sensor
  Serial.print("\t sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);

// waktu data masuk
  delay(1000);
}
