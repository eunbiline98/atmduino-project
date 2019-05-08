#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

int sensorGetar = 2;
int led1 = 3; // Set Pin 3 untuk LED Hijau
int led2 = 4; // Set Pin 4 untuk LED Merah
int buzzer = 5; // Set Pin 5 untuk Buzzer

void setup() {
  lcd.begin(16, 2);
  pinMode(sensorGetar, INPUT); // Jadikan Vibration sensor sebagai input
  pinMode(led1, OUTPUT); // Jadikan indikatorHijau sebagai Output
  pinMode(led2, OUTPUT); // Jadiikan indikatorMerah sebagai Output
  pinMode(buzzer, OUTPUT); // Jadikan indikatorBuzzer sebagai Output
}

void loop() {
  if ( digitalRead(sensorGetar) == HIGH) { // Jika ada getaran di sensor = HIGH
    digitalWrite(led1, HIGH); // Aktifkan indikator Hijau
    digitalWrite(led2, LOW); // Matikan indikator Merah
    digitalWrite(buzzer, HIGH); // // Aktifkan indikator Buzzer
    lcd.setCursor(0, 0);
    lcd.print("bergetar gan !!!");
    delay(5000); // Tunda 5 detik
    digitalWrite(led1, LOW); // Matikan indikator Hijau
    digitalWrite(led2, HIGH); // Aktifkan indikator Merah
    delay(100); // Delay untuk menunggu getaran selanjutnya
  } 
  else 
 {
    digitalWrite(led1, LOW); // Matikan indikator Hijau
    digitalWrite(led2, HIGH); // Aktifkan indikator Merah
    digitalWrite(buzzer, LOW); // Matikan indikator Buzzer
    lcd.setCursor(0, 0);
    lcd.print("Menunggu getaran");
    delay(1000);
  }
}
