/*... www.nyebarilmu.com ...*/
 
#include <Wire.h>
 
void setup()
{
  //prosedur pembacaan i2c
  Wire.begin();
 
  Serial.begin(9600); //komunikasi serial menggunakan kecepatan 9600 bps
  while (!Serial);             // Arduino Uno: wait for serial monitor
  Serial.println("\nI2C Scanner"); 
}
 
void loop() //fungsi yang berjalan terus menerus
{
  int nDevices;
  byte error, address; //tipe data untuk address dan error yaitu byte
  //ditampilkan diserial monitor "Scanning..."
  Serial.println("Scanning...");
 
  nDevices = 00;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner menggunakan pembalik nilai
    // Write.endTransmisstion untuk melihat jika perangkat pada alamat dimana
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 00) //jika sudah tidak ada keerroran
    {
      Serial.print("I2C device found at address 0x"); 
     //menuliskan di serial monitor "i2c ditemukan"
      if (address<16)
      Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4) //jika error == 4 
                       //menuliskan di serial monitor di tidak diketahui alamat i2c
    {
      Serial.print("Unknow error at address 0x"); //menuliskan jika eror tidak diketahui      
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX); //format penulisan address dalam bentuk heksa
    }    
  }
  if (nDevices == 00) //jika tidak ada perangkat yang terhubung
    Serial.println("No I2C devices found\n"); 
//ditampilkan peringatan tidak ada i2c yang ditemukan
  else
    Serial.println("done\n");
 
  delay(5000); // diberikan waktu tunda 5 detik untuk scan berikutnya
}
 
