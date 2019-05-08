#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11

#define dht_dpin D5
DHT dht(dht_dpin, DHTTYPE); 

#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME " "
#define DEVICE_ID " "
#define DEVICE_CREDENTIAL " "

#define SSID " "
#define SSID_PASSWORD " "

// thinger.io config
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  dht.begin();
  pinMode(D4, OUTPUT);
  pinMode(D5, INPUT) ;
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["Stop Kontak"] << digitalPin(D6);
  thing["Lampu"] << digitalPin(D7);
  // resource output example (i.e. reading a sensor value)
  //thing["millis"] >> outputValue(millis());
  //pembacaan sensor dht11
  thing["dht11"] >>[](pson & out){
    out["humidity"] = dht.readHumidity();
    out["celsius"] = dht.readTemperature();
    out["fahrenheit"] = dht.readTemperature(true);  
  
  };

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
  digitalWrite(D4, HIGH);
}
