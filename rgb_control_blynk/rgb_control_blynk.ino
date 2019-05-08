/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define RedPin D1  // Set RED RGB pin
#define GrnPin D2  // Set GREEN RGB pin
#define BluPin D3  // Set BLUE RGB pin


#define zeRGBa V0  // Set virtual RGB widget
#define rSlide V1  // Set virtual RGB widget
#define gSlide V2  // Set virtual RGB widget
#define bSlide V3  // Set virtual RGB widget

int rrr, ggg, bbb;  // Set RED BLUE GREEN channels

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "6f0ab9c206aa4dc2ab16232d83ca5672";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "smarthome";
char pass[] = "smarthomes";

void setup()
{
  // Debug console
  Serial.begin(115200);

  pinMode(RedPin, OUTPUT);  // Set RED pinMode
  pinMode(GrnPin, OUTPUT);  // Set GREEN pinMode
  pinMode(BluPin, OUTPUT);  // Set BLUE pinMode

  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  Blynk.begin(auth, ssid, pass,"blynk-cloud.com", 8442);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  Blynk.run();
}
  //===== RED slider =====
BLYNK_WRITE(rSlide) { // START Blynk Function
  rrr = param.asInt(); // get a RED channel value
 // Blynk.virtualWrite(vRed, rrr);  // Red LED intensity
  Blynk.virtualWrite(zeRGBa, rrr, ggg, bbb);  // Sync zeRGBa position
}  // END Blynk Function


//===== GREEN slider =====
BLYNK_WRITE(gSlide) { // START Blynk Function
  ggg = param.asInt(); // get a GREEN channel value
 // Blynk.virtualWrite(vGreen, ggg);  // Green LED intensity
  Blynk.virtualWrite(zeRGBa, rrr, ggg, bbb);  // Sync zeRGBa position
}  // END Blynk Function


//===== BLUE slider =====
BLYNK_WRITE(bSlide) { // START Blynk Function
  bbb = param.asInt(); // get a BLUE channel value
 // Blynk.virtualWrite(vBlue, bbb);  // Blue LED intensity
  Blynk.virtualWrite(zeRGBa, rrr, ggg, bbb);  // Sync zeRGBa position
 }  // END Blynk Function



//===== zeRGBa Widget  =====
BLYNK_WRITE(zeRGBa) { // START Blynk Function
  rrr = param[0].asInt(); // get a RED channel value
  ggg = param[1].asInt(); // get a GREEN channel value
  bbb = param[2].asInt(); // get a BLUE channel value
}


