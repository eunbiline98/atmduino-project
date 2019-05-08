//esp32
#include "WiFi.h"
#include "WiFiClientSecure.h"
#include "UniversalTelegramBot.h"
//esp8266
//#include <ESP8266WiFi.h> // memsaukan Library ESP8266
//#include <WiFiClientSecure.h> 
//#include <UniversalTelegramBot.h> // memasukan Library TelegramBot

char ssid[] = "Pkm_asia"; 
char password[] = "sistemkomputer";
#define BOTtoken "872146786:AAFqUC58J3mU5eNv271lfjYEozV_dj_qdzQ"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; 
long Bot_lasttime;  
bool Start = false;

const int ledPin = 15; // menggunakan LED bawaan Wemos / Nodemcu, bisa diganti dengan pin lain, misal const int ledPin = 13;
int ledStatus;

void handleNewMessages(int numNewMessages) {
  Serial.println("Pesan Baru Masuk");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) { 
    String chat_id = String(bot.messages[i].chat_id); 
    String text = bot.messages[i].text; 
    String from_name = bot.messages[i].from_name; 
    
      if (from_name == "")
        {
          from_name = "Guest"; 
        }
      if (text == "/lampon") 
        { 
          digitalWrite(ledPin, LOW); // hidupkan LED, karena untuk LED bawaan wemos / nodemcu untuk menghidpkan justru di LOW'kan 
          ledStatus = 1; 
          bot.sendMessage(chat_id, "Lampu Menyala", ""); 
        } 
      else if (text == "/lampoff") 
        { 
          ledStatus = 0; 
          digitalWrite(ledPin, HIGH); // matikan LED, karena untuk LED bawaan wemos / nodemcu untuk mematikan justru di HIGH'kan 
          bot.sendMessage(chat_id, "Lampu Mati", "");
        } 
      else if (text == "/status") 
        { 
          if(ledStatus)
            { 
              bot.sendMessage(chat_id, "Lampu Menyala", ""); 
            } 
          else 
            { 
              bot.sendMessage(chat_id, "Lampu Mati", "");
            }
         } 
       else if (text == "/start") 
         { // jika dapat pesan "/start" 
            String welcome = "hello Eunbi line,Control Lampu via Telegram, " + from_name; 
            welcome += "/lampon : untuk menghidupkan Lampu";
            welcome += "/lampoff : untuk mematikan Lampu";
            welcome += "/status : untuk memeriksa Status Lampu"; 
            bot.sendMessage(chat_id, welcome, "Markdown");
          } 
     } 
} 

void setup() { 
  Serial.begin(115200); 
  WiFi.mode(WIFI_STA); 
  WiFi.disconnect(); // putuskan koneksi wi-fi jika sebelumnya sudah tersambung 
  delay(100);  
  Serial.print("Mengkoneksikan dengan Wi-fi : "); 
  Serial.println(ssid); 
  WiFi.begin(ssid, password); 
  
  while (WiFi.status() != WL_CONNECTED) 
    { 
      Serial.print("."); 
      delay(500); 
    } 
    
  Serial.println(""); 
  Serial.println("Terhubung dengan wi-fi"); 
  Serial.print("IP address: "); 
  Serial.println(WiFi.localIP()); 
  pinMode(ledPin, OUTPUT); // set ledPin sebagai OUTPUT 
  digitalWrite(ledPin, LOW); // matikan led 
} 

void loop() 
  { 
    if (millis() > Bot_lasttime + Bot_mtbs)
      {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while(numNewMessages) 
          {
            Serial.println("Memeriksa Respon");
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
          }

        Bot_lasttime = millis();
      }
  }
