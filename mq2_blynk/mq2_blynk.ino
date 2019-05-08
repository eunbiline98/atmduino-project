#include <SPI.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <SimpleTimer.h>
#include <MQ2.h>


//change this with the pin that you use
int pin = A0;
int lpg, co, smoke;

MQ2 mq2(pin);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "********************************";
char ssid[] = "********************************";
char pass[] = "********************************";

SimpleTimer timer;

void setup() {
  Blynk.begin(auth, server, 8080);
  mq2.begin();
  timer.setInterval(2000L, gas);
}

void gas() {

  /*read the values from the sensor, it returns
    an array which contains 3 values.
    1 = LPG in ppm
    2 = CO in ppm
    3 = SMOKE in ppm
  */
  float* values = mq2.read(true); //set it false if you don't want to print the values in the Serial

  //lpg = values[0];
  lpg = mq2.readLPG();
  Blynk.virtualWrite(1, lpg);
  //co = values[1];
  co = mq2.readCO();
  Blynk.virtualWrite(2, co);
  //smoke = values[2];
  smoke = mq2.readSmoke();
  Blynk.virtualWrite(3, smoke);
}

void loop()
{
  Blynk.run();
  timer.run();
}
