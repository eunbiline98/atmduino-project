#include<ESP8266WiFi.h>
#include<WiFiClientSecure.h>
#include<UniversalTelegramBot.h>

char ssid[] = "Pkm_asia"; 
char password[] = "sistemkomputer";
#define BOTtoken "872146786:AAFqUC58J3mU5eNv271lfjYEozV_dj_qdzQ"
String chatid = "661147716";

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  Serial.begin(9600);
  WifiStatus();

  bot.sendMessage(chatid, "Hello Buddy, Aku Sinb");
  Serial.println("Pesan Terkirim ke Telegram");
}

void loop() {

}

void WifiStatus() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
