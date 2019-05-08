#define echoPin 8 //Echo Pin
#define trigPin 9 //Trigger Pin
#define LEDPin 13 //Led default dari Arduino uno
 
int maximumRange = 200; //kebutuhan akan maksimal range
int minimumRange = 0; //kebutuhan akan minimal range
long duration, distance; //waktu untuk kalkulasi jarak
 
void setup() {
Serial.begin (9600); //inisialiasasi komunikasi serial
//deklarasi pin
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(LEDPin, OUTPUT);
}
 
void loop() {
/* Berikut siklus trigPin atau echo pin yang digunakan
untuk menentukan jarak objek terdekat dengan memantulkan
gelombang suara dari itu. */
digitalWrite(trigPin, LOW);delayMicroseconds(2);
 
digitalWrite(trigPin, HIGH);delayMicroseconds(10);
 
digitalWrite(trigPin, LOW);
 
duration = pulseIn(echoPin, HIGH);
 
//perhitungan untuk dijadikan jarak
distance = duration/58.2;
 
/* Kirim angka negatif ke komputer dan Turn LED ON 
untuk menunjukkan "di luar jangkauan" * /
 
if (distance >= maximumRange || distance <= minimumRange)
{
Serial.println("-1");digitalWrite(LEDPin, HIGH);
}
else {
/*Kirim jarak ke komputer menggunakan Serial protokol, dan
menghidupkan LED OFF untuk menunjukkan membaca sukses. */
Serial.println(distance);
digitalWrite(LEDPin, LOW);
 
//waktu tunda 50mS
delay(50);
}
