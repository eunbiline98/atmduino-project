#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define relay D0
//#define button2 D7

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "silahkan di isi auth";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IoT_smartHome";
char pass[] = "robotics";

#define DHTPIN D2          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  //pembacaan sensor membutuhkan waktu 250ms
 
  //Pembacaan untuk data kelembaban
  float humidity_1 = dht.readHumidity();
  //Pembacaan dalam format celcius (c)
  float celcius_1 = dht.readTemperature();
  //pembacaan dalam format Fahrenheit
  float fahrenheit_1 = dht.readTemperature(true);
 
  //mengecek pembacaan apakah terjadi kegagalan atau tidak
  if (isnan(humidity_1) || isnan(celcius_1) || isnan(fahrenheit_1)) {
    Serial.println("Pembacaan data dari module sensor gagal!");
    return;
  }
 
  float htof = dht.computeHeatIndex(fahrenheit_1, humidity_1); 
  //Prosedur pembacaaan data indeks panas dalam bentuk fahreheit
  float htoc = dht.computeHeatIndex(celcius_1, humidity_1, false);
 //Prosedur pembacaaan data indeks panas dalam bentuk celcius
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, humidity_1);
  Blynk.virtualWrite(V6, celcius_1);
  Blynk.virtualWrite(V7, fahrenheit_1);
  Blynk.virtualWrite(V8, htof);

  Blynk.virtualWrite(V2, HIGH);

  //pembacaan nilai pembacaan data kelembaban
  Serial.print("Kelembaban: ");
  Serial.print(humidity_1);
  Serial.print(" %\t");
  
  //pembacaan nilai pembacaan data suhu
  Serial.print("Suhu : ");
  Serial.print(celcius_1); //format derajat celcius
  Serial.print(" 'C ");
  Serial.print(fahrenheit_1); //format derajat fahrenheit
  Serial.print(" 'F\t");
 
  Serial.print("Indeks Panas: ");
  Serial.print(htof); 
  Serial.println(" *F"); 
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  pinMode(relay,OUTPUT);
  //pinMode(button2, INPUT_PULLUP); 
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();

  float humidity_1 = dht.readHumidity();

  if (humidity_1 >=70){
     digitalWrite(relay, HIGH);
     delay(4000);
  } else {
     digitalWrite(relay, LOW);
     delay(4000);
  }

}


