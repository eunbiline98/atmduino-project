#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);
#include <DS3231.h>

Time  t;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
#define tahun now.year()
#define bulan now.month()
#define tanggal now.day()
#define hari daysOfTheWeek[now.dayOfTheWeek()]
#define jam now.hour()
#define menit now.minute()
#define detik now.second()
#define addrmenit 0
#define addrjam 1
#define addrtanggal 2
#define addrbulan 3
#define btnmenu 2
#define btnup 3
#define btndown 4
#define pinBuzzer 13
byte sel = 0, ajam, amenit, atanggal, abulan, bjam=0, bmenit=0;
boolean state;
char buff[10];
void setup()
{
  // initialize the LCD
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode (btnmenu, INPUT_PULLUP);
  pinMode (btnup, INPUT_PULLUP);
  pinMode (btndown, INPUT_PULLUP);
  pinMode (13, OUTPUT);
}
unsigned long waktulama = 0;
int interval = 5000;
void loop()
{
//  t = rtc.now();
  if (digitalRead(btnmenu) == 0) {
    while (digitalRead(btnmenu) == 0) {}
    sel++;
    switch (sel) {
      case 0 :
        break;
      case 1 :
        break;
      case 2 :
        EEPROM.write(addrjam, ajam);
        break;
      case 3 :
        EEPROM.write(addrmenit, amenit);
        sel = 0;
        break;
        //      case 4 :
        //        EEPROM.write(addrtanggal, atanggal);
        //        break;
        //      case 5 :
        //        EEPROM.write(addrtanggal, abulan);
        //        sel = 0;
        //        break;
    }
  }
  switch (sel) {
    case 0 :
      run_alarm();
      break;
    case 1 :
      lcd.clear ();
      set_alarm_jam();
      break;
    case 2 :
      lcd.clear ();
      set_alarm_menit();
      break;
      //    case 3 :
      //      lcd.clear ();
      //      set_alarm_tanggal();
      //      break;
      //    case 4 :
      //      lcd.clear ();
      //      set_alarm_bulan();
      //      break;
  }
  if (digitalRead(btnup) == 0) {
    while (digitalRead(btnup) == 0) {}
    switch (sel) {
      case 1:
        ajam++;
        break;
      case 2:
        amenit++;
        break;
      case 3:
        atanggal++;
        break;
      case 4:
        abulan++;
        break;
    }
  }
  if (digitalRead(btndown) == 0) {
    while (digitalRead(btndown) == 0) {}
    switch (sel) {
      case 1:
        ajam--;
        break;
      case 2:
        amenit--;
        break;
    }
  }
}
void tampil_jam () {
  t = rtc.now();
  if (jam < 10 && menit < 10) {
    sprintf (buff, "0%d:0%d", jam, menit);
  }
  else  if (jam < 10 && menit >= 10) {
    sprintf (buff, "0%d:%d", jam, menit);
  }
  else  if (jam >= 10 && menit < 10) {
    sprintf (buff, "%d:0%d", jam, menit);
  }
  else  if (jam >= 10 && menit >= 10) {
    sprintf (buff, "%d:%d", jam, menit);
  }


  lcd.setCursor (5, 0);
  lcd.print(buff);
}
void tampil_tanggal() {
//  t = rtc.now();
  if (tanggal < 10 && bulan < 10) {
    sprintf (buff, "0%d-0%d-%d", tanggal, bulan, tahun);
  }
  else  if (tanggal < 10 && bulan >= 10) {
    sprintf (buff, "0%d-%d-%d", tanggal, bulan, tahun);
  }
  else  if (tanggal >= 10 && bulan < 10) {
    sprintf (buff, "%d-0%d-%d", tanggal, bulan, tahun);
  }
  else  if (tanggal >= 10 && bulan >= 10) {
    sprintf (buff, "%d-%d-%d", tanggal, bulan, tahun);
  }
  lcd.setCursor(3, 1);
  lcd.print(buff);
}
void set_alarm_jam() {
  if (ajam < 10 && amenit < 10) {
    sprintf (buff, "0%d:0%d", ajam, amenit);
  }
  else  if (ajam < 10 && amenit >= 10) {
    sprintf (buff, "0%d:%d", ajam, amenit);
  }
  else  if (ajam >= 10 && amenit < 10) {
    sprintf (buff, "%d:0%d", ajam, amenit);
  }
  else  if (ajam >= 10 && amenit >= 10) {
    sprintf (buff, "%d:%d", ajam, amenit);
  }
  if (ajam > 23) {
    ajam = 0;
  }
  lcd.setCursor(1, 0);
  lcd.print("Set nilai Jam");
  lcd.setCursor(5, 1);
  lcd.print(buff);
}
void set_alarm_menit() {
  if (ajam < 10 && amenit < 10) {
    sprintf (buff, "0%d:0%d", ajam, amenit);
  }
  else  if (ajam < 10 && amenit >= 10) {
    sprintf (buff, "0%d:%d", ajam, amenit);
  }
  else  if (ajam >= 10 && amenit < 10) {
    sprintf (buff, "%d:0%d", ajam, amenit);
  }
  else  if (ajam >= 10 && amenit >= 10) {
    sprintf (buff, "%d:%d", ajam, amenit);
  }
  if (amenit > 59) {
    amenit = 0;
  }
  lcd.setCursor(1, 0);
  lcd.print("Set Nilai Menit");
  lcd.setCursor(5, 1);
  lcd.print(buff);
}
//void set_alarm_tanggal() {
//  DateTime now = rtc.now();
//  if (atanggal < 10 && abulan < 10) {
//    sprintf (buff, "0%d-0%d-%d", atanggal, abulan, tahun);
//  }
//  else  if (tanggal < 10 && bulan >= 10) {
//    sprintf (buff, "0%d-%d-%d", atanggal, abulan, tahun);
//  }
//  else  if (atanggal >= 10 && abulan < 10) {
//    sprintf (buff, "%d-0%d-%d", atanggal, abulan, tahun);
//  }
//  else  if (atanggal >= 10 && abulan >= 10) {
//    sprintf (buff, "%d-%d-%d", atanggal, abulan, tahun);
//  }
//
//  lcd.setCursor(0, 0);
//  lcd.print("Set Nilai Tnggl");
//  lcd.setCursor(3, 1);
//  lcd.print(buff);
//}
//void set_alarm_bulan() {
//  DateTime now = rtc.now();
//  if (atanggal < 10 && abulan < 10) {
//    sprintf (buff, "0%d-0%d-%d", atanggal, abulan, tahun);
//  }
//  else  if (tanggal < 10 && bulan >= 10) {
//    sprintf (buff, "0%d-%d-%d", atanggal, abulan, tahun);
//  }
//  else  if (atanggal >= 10 && abulan < 10) {
//    sprintf (buff, "%d-0%d-%d", atanggal, abulan, tahun);
//  }
//  else  if (atanggal >= 10 && abulan >= 10) {
//    sprintf (buff, "%d-%d-%d", atanggal, abulan, tahun);
//  }
//
//  lcd.setCursor(0, 0);
//  lcd.print("Set Nilai Bulan");
//  lcd.setCursor(3, 1);
//  lcd.print(buff);
//}
void menu_utama() {
  if (state == 1) {
    tampil_jam();
    tampil_tanggal();
  }
  else if (state == 0) {
    tampil_alarm_now();
  }
}
void tampil_alarm_now() {
  bjam = EEPROM.read(addrjam);
  bmenit = EEPROM.read(addrmenit);
  if (bjam < 10 && bmenit < 10) {
    sprintf (buff, "0%d:0%d", bjam, bmenit);
  }
  else  if (bjam < 10 && bmenit >= 10) {
    sprintf (buff, "0%d:%d", bjam, bmenit);
  }
  else  if (bjam >= 10 && bmenit < 10) {
    sprintf (buff, "%d:0%d", bjam, bmenit);
  }
  else  if (bjam >= 10 && bmenit >= 10) {
    sprintf (buff, "%d:%d", bjam, bmenit);
  }
  lcd.setCursor(2, 0);
  lcd.print("Alarm di Set");
  lcd.setCursor(5, 1);
  lcd.print(buff);
}
void run_alarm() {
  t//t = rtc.now();
  if (millis() - waktulama >= interval) {
    lcd.clear ();
    waktulama = millis();
    if (state == 0) {
      state = 1;
    }
    else if (state == 1) {
      state = 0;
    }
    menu_utama();
    Serial.print(bjam);
    Serial.print(":");
    Serial.print(bmenit);
    Serial.print("\t");
    Serial.print(bjam);
    Serial.print(":");
    Serial.println(bmenit);
    if ((jam == bjam) && (menit == bmenit)) {
      Serial.println("Alarm");
      digitalWrite(pinBuzzer, state);
    }
  }
}
