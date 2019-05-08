#include "FirebaseESP8266.h"
#include "DHT.h"
#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "smarthomeasia1.firebaseio.com"
#define FIREBASE_AUTH "HYv6JMXLZP2PSKZTZFvcyiQssQw2d6SZ8gxKESjK"
#define WIFI_SSID "ggwp" // Change the name of your WIFI
#define WIFI_PASSWORD "sksaturasa" // Change the password of your WIFI
FirebaseData firebaseData;
#define DHTPIN D5    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14
#define lamp D6
#define kipa D7
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
int kip,lam;

void setup() {
  Serial.begin(9600);
  pinMode(D4,OUTPUT);
  pinMode(lamp,OUTPUT);
  pinMode(DHTPIN,INPUT);
  pinMode(kipa,OUTPUT);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  
}

void loop() {

kip=Firebase.getInt(firebaseData,"lampu22");
lam=Firebase.getInt(firebaseData,"lampu12"); 
if(kip==1){
  digitalWrite(kipa,HIGH);
  digitalWrite(D4,HIGH);
  Firebase.setInt(firebaseData,"k",3);
}
if(kip==0){
  digitalWrite(D4,LOW);
  digitalWrite(kipa,LOW);
  Firebase.setInt(firebaseData,"k",2);
}
if(lam==1){
  digitalWrite(lamp,HIGH);
}
if(lam==0){
  digitalWrite(lamp,LOW);
}

}
