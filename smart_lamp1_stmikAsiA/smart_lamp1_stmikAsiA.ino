#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "lamp_smart"
#define DEVICE_ID "smart_lamp1"
#define DEVICE_CREDENTIAL "NDBZj8AF3ixk"

#define SSID "Pkm_asia"
#define SSID_PASSWORD "sistemkomputer"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(D4, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["Lamp 1"] << digitalPin(D6);
  thing["Lamp 2"] << digitalPin(D7);
  digitalWrite(D4, HIGH);
  // resource output example (i.e. reading a sensor value)
  //thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}
