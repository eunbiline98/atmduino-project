

const int pin_ldr = A2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int nilai = analogRead (pin_ldr); // nilai analog dari sensor ldr
  float tegangan_hasil = 5.0 * nilai / 1024;
  //tampilan hasil output nilai analog
  Serial.print ("Vout=");
  Serial.print (tegangan_hasil);
  Serial.print (" V");
  Serial.println("");

  delay(1000);
}
