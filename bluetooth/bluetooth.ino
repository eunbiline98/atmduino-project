/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Social networks:            http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example shows how to use Arduino with HC-06/HC-05
  Bluetooth 2.0 Serial Port Profile (SPP) module
  to connect your project to Blynk.

  Note: This only works on Android! iOS does not support SPP :(
        You may need to pair the module with your smartphone
        via Bluetooth settings. Default pairing password is 1234

  Feel free to apply it to any other example. It's simple!

  NOTE: Bluetooth support is in beta!

 *************************************************************/

#define BLYNK_USE_DIRECT_CONNECT

// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(0, 1); // RX, TX

#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>

int relay = 5;
int led   = 7;
int button = 6;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "6f0ab9c206aa4dc2ab16232d83ca5672";

void setup()
{
  // Debug console
  DebugSerial.begin(38400);

  DebugSerial.println("Waiting for connections...");

  // Blynk will work through Serial
  // 9600 is for HC-06. For HC-05 default speed is 38400
  // Do not read or write this serial manually in your sketch
  Serial.begin(38400);
  Blynk.begin(Serial, auth);

  pinMode(relay, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop()
{
  Blynk.run();

  if (digitalRead (button))
  {
    digitalWrite(relay, HIGH);
    digitalWrite(led, HIGH);
  }
  
  else
  {
    digitalWrite(relay, LOW);
    digitalWrite(led, LOW);
  }
}

