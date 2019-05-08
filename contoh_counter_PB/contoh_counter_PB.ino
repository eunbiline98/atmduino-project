/*
*Simulasi Penghitung Jumlah Kendaraan Parkir di Mall
*Created by Muhamad Andi Prasetyo
*30 Juni 2015
*Email : muhandi.prasetyo@gmail.com
*www.boarduino.blogspot.com
*/

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int  buttonMasuk = 6;
const int  buttonKeluar = 7;
const int  buttonReset = 8;
int Penghitung = 0;
int statusMasuk = 0;
int statusKeluar = 0;
int statusReset = 0;
int statusTerakhir = 0;
int led = 13;
int maksimal = 20;

void setup() { 
   pinMode(buttonMasuk, INPUT);  
   pinMode(buttonKeluar, INPUT);
   pinMode(buttonReset, INPUT);
   pinMode(led, OUTPUT);    
   lcd.begin(16,2); 
   lcd.setCursor(1,0);
   lcd.print("Selamat Datang");
   lcd.setCursor(2,1);
   lcd.print("Di Boarduino");
   delay(5000);
   lcd.clear();
   lcd.setCursor(1,0);  
   lcd.print("Total :");
   lcd.setCursor(9,0);
   lcd.print("KOSONG");
   lcd.setCursor(1,1);
   lcd.print("Sisa  : ");
   lcd.setCursor(9,1);
   lcd.print(maksimal);
}

void loop() {
    statusReset = digitalRead(buttonReset);
    if (statusReset == HIGH) {
      Penghitung = 0;
      maksimal = 20;
      lcd.clear();
      delay(50);
      lcd.setCursor(1,0);  
      lcd.print("Total :");  
      lcd.setCursor(1,1);
      lcd.print("Sisa  : ");
      lcd.setCursor(9,0);
      lcd.print("KOSONG");
      lcd.setCursor(9,1);
      lcd.print(maksimal);
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
    }
   statusMasuk = digitalRead(buttonMasuk);
   if (statusMasuk != statusTerakhir) {
     if (statusMasuk == HIGH)
     {
      Penghitung++;
      maksimal--;
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      lcd.setCursor(9,0);  
      lcd.print(Penghitung);
      lcd.setCursor(9,1);
      lcd.print(maksimal);
     }
      delay(50);

   }
   statusTerakhir = statusMasuk;
   statusKeluar = digitalRead(buttonKeluar);
   if (statusKeluar != statusTerakhir) {
     if (statusKeluar == HIGH)
     {
      Penghitung-=1;
      maksimal++;
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
      lcd.setCursor(9,0);
      lcd.print(Penghitung);
     }
         delay(50); 
         if (Penghitung > 0)
         {
            lcd.clear();
            delay(3);
            lcd.setCursor(1,0);  
            lcd.print("Total :");  
            lcd.setCursor(1,1);
            lcd.print("Sisa  : ");
            lcd.setCursor(9,0);
            lcd.print(Penghitung);
            lcd.setCursor(9,1);
            lcd.print(maksimal);
         }

         if (Penghitung <= 0)
         {         
            Penghitung = 0;
            maksimal = 20;
            lcd.setCursor(1,1);
            lcd.print("Sisa  : ");
            lcd.setCursor(9,1);
            lcd.print(maksimal);
            lcd.setCursor(9,0);
            lcd.print("KOSONG");
         }
         if (Penghitung >= maksimal)
         {
           Penghitung = 20;
           maksimal = 0;
           lcd.setCursor(9,0);
           lcd.print(Penghitung);
           lcd.setCursor(9,1);
           lcd.print("KOSONG");
           digitalWrite(led, HIGH);
           delay(5000);
           digitalWrite(led, LOW);
           delay(1000);
         } 
   }
   statusTerakhir = statusKeluar;
}
