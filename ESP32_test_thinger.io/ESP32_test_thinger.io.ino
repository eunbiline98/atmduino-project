#include <WiFi.h>
#include <ThingerESP32.h>

#define USERNAME "sesuaikan nama username"
#define DEVICE_ID "sesuaikan nama device id"
#define DEVICE_CREDENTIAL "sesuaikan"

#define SSID "sesuaikan ssid"
#define SSID_PASSWORD "sesuaikan ssid pass"

// define your board pin here
#define LED_PIN 15

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  pinMode(LED_PIN, OUTPUT);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_PIN);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
}
