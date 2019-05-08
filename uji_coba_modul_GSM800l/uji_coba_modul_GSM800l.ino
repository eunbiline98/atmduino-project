#include <SoftwareSerial.h>
SoftwareSerial SIM800L(2, 3); // RX | TX
// Connect the SIM800L TX to Arduino pin 2 RX. 
// Connect the SIM800L RX to Arduino pin 3 TX. 
void setup() {
 // start th serial communication with the host computer
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Arduino with SIM800L is ready");
 
    // start communication with the SIM800L in 9600
    SIM800L.begin(9600);  
    Serial.println("SIM800L started at 9600");
    delay(1000);
    Serial.println("Setup Complete! SIM800L is Ready!");
   
  Serial.println("Set format SMS ke ASCII");
  SIM800L.write("AT+CMGF=1\r\n");
  delay(1000);
 
  Serial.println("SIM800L Set SMS ke Nomor Tujuan");
  SIM800L.write("AT+CMGS=\"08973234445\"\r\n");
  delay(1000);
   
  Serial.println("SIM800L Send SMS content");
  SIM800L.write("Testing Kirim SMS via SIM800L, Siap Maju Tugas Akhir");
  delay(1000);
   
  Serial.println("Mengirim Char Ctrl+Z / ESC untuk keluar dari menu SMS");
  SIM800L.write((char)26);
  delay(1000);
     
  Serial.println("SMS Selesai Dikirim!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
