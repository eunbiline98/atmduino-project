#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "46cfcffb810d409abc329ca1d92693d6";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IoT_smartHome";
char pass[] = "robotics";

#include <Servo.h>

Servo myservo;  // create servo object to control a servo

BLYNK_WRITE(V3) 
{
myservo.write(param.asInt()); 
}


void setup() {

  myservo.attach(D3);  // attaches the servo on pin 9 to the servo object

   Serial.begin(115200);

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

