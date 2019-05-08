#include <LiquidCrystal.h> //mengincludekan library LCD
 
//untuk urutannya RS, E, 4, 5, 6, 7
LiquidCrystal lcd(26, 28, 30, 32, 34, 36); //pin yang disambungkan antara arduino dengan LCD
 
void setup()
{
//prosedur pemanggilan fungsi LCD
lcd.begin(16, 2);//16 = Baris, 2 = kolom
}
 
void loop() {
lcd.setCursor(2,0); //set pada baris 1 dan kolom 1
lcd.print("Robo Arduino"); //menuliskan "nyebarilmu.com"
lcd.setCursor(0,1);//set pada baris 2 dan kolom 1
lcd.print("--Siskom  Asia--");
delay(3000); //waktu tunda 3 detik
}
