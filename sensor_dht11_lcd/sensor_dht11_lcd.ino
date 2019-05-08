#include "DHT.h"
//#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

#define DHTPIN A2 // pin 2
#define DHTTYPE DHT11// sesnor kelembaban dan suhu

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  lcd.begin (16,2); //LCD untuk ukuran 16x2
  dht.begin();
  
  lcd.setCursor(0,0);
  lcd.print("Pengujian DHT11");
  delay(1000);
  lcd.setCursor(4,1);
  lcd.print("Ready...!");
  delay(1000);
  lcd.clear();

}

void loop() {
 delay(100);  //menunggu beberapa detik untuk pembacaan
 
  //pembacaan sensor membutuhkan waktu 250ms
 
  //Pembacaan untuk data kelembaban
  float humidity_1 = dht.readHumidity();
  //Pembacaan dalam format celcius (c)
  float celcius_1 = dht.readTemperature();
  //pembacaan dalam format Fahrenheit
 
  //mengecek pembacaan apakah terjadi kegagalan atau tidak
  if (isnan(humidity_1) || isnan(celcius_1)) {
    lcd.setCursor(0,0);
    lcd.print(" Sensor error!!!");
    lcd.setCursor(0,1);
    lcd.print("                ");
    return;
  }
  float htoc = dht.computeHeatIndex(celcius_1, humidity_1, false);
 //Prosedur pembacaaan data indeks panas dalam bentuk celcius
 
  //pembacaan nilai pembacaan data kelembaban
  lcd.setCursor(0,0);
  lcd.print("H   :");
  lcd.print(humidity_1);
  lcd.print(" %    ");
  
  //pembacaan nilai pembacaan data suhu
  lcd.setCursor(0,1);
  lcd.print("Suhu:");
  lcd.print(celcius_1); //format derajat celcius
  lcd.print(" C ");
 
}
