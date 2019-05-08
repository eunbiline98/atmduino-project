 
#include <SoftwareSerial.h>
SoftwareSerial SIM800L(2, 3); // RX | TX
// Hubungkan TXD untuk Arduino pin 2 
// Hubungkan RXD untuk Arduino pin 3
char c = ' ';
void setup() 
{
    Serial.begin(9600); //Menggunakan komunikasi serial pada 9600bps
    while(!Serial);
    Serial.println("Arduino with Module GSM is ready");
 
    // memulai komunikasi dengan
    SIM800L.begin(9600);  
    Serial.println("Module GSM started at 9600");
    delay(1000); //nilai tunda 1 second
    Serial.println("Setup Complete! SIM800 is Ready!");
}
 
void loop()
{
 
     // memastikan pembacaan dari SIM800 dan dikirim datanya ke Arduino(Serial Monitor)
    if (SIM800L.available())
    { c = SIM800L.read();
      Serial.write(c);}
 
    // memastikan pembacaan dari SIM800 dan dikirim datanya ke Arduino(Serial Monitor)
    if (Serial.available())
    { c = Serial.read();
      SIM800L.write(c);  
       }
 
}
