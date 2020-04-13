#include <Wire.h> 
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

#include <EEPROM.h>
byte kondisi;

//dht11
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 12
DHT dht(dht_dpin, DHTTYPE);

//themistor
#define rt0 10000   // Ω
#define b 3977      // K
#define vcc 5    //Supply voltage
#define r 10000  //R=10KΩ
int tempPin = A0;
float val, rt, vr, ln, suhu, T0;
float set_suhu;

#define relay_blower 8 
#define relay_hologen 9 

int sensor_hujan = A3;
int hujanState = 0;

#define pin_cw 10
#define pin_cww 11
int sens_a = A1;
int sens_b = A2;
 
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'} };
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 2, 1, 0}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
int menu = 1;

byte baju[] = {
  B00000,
  B01010,
  B01110,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000
};

void setup(){
  //Serial.begin(9600);
  lcd.begin();
  dht.begin();
  T0 = 25 + 273.15;
  pinMode(relay_blower,OUTPUT);
  pinMode(relay_hologen,OUTPUT); 
  pinMode(sensor_hujan, INPUT);
  pinMode(sens_a, INPUT_PULLUP);
  pinMode(sens_b, INPUT_PULLUP);
   
  digitalWrite(relay_hologen,LOW);  
  digitalWrite(relay_blower,LOW);
  lcd.setCursor(2,0);  
  lcd.print("Rancangan Bangun");
  lcd.setCursor(2,1);  
  lcd.print("Sistem Pengering");
  lcd.setCursor(7,2);  
  lcd.print("Pakaian");
  lcd.setCursor(2,3);  
  lcd.print("Industri Rumahan");           
  delay(3000);
  lcd.clear();
  data_eeprom();
}

void loop(){
  sensor_suhu();
  sensor_kelembaban();
  data_eeprom();
  main_menu();
  lcd.createChar(0, baju);
  lcd.setCursor(0, 1);
  lcd.write(0);
  lcd.print(":");
  Serial.println(set_suhu);
// set suhu
//  if(digitalRead(btn_down)==LOW)
//  {
//    if(set_suhu>0)
//    {
//      set_suhu--;    
//    }
//  }
//  if(digitalRead(btn_up)==LOW)
//  {
//    if(set_suhu<150)
//    {
//      set_suhu++;
//    }
//  }
//  lcd.setCursor(0,1);
//  lcd.print("Set suhu: ");
//  lcd.print(set_suhu);
//  lcd.write(0b11011111);
//  lcd.print("    ");
//
char customKey = customKeypad.getKey();
if (customKey=='A'){
    menu++;
  }
if (customKey=='B'){
   menu--;
}
if (customKey=='D'){
   executeAction();
}

//pengaturan blower,lampu,conveyor
if(suhu > set_suhu)
{
  digitalWrite(relay_hologen,LOW);
  digitalWrite(relay_blower,LOW);
}
else
{  
  digitalWrite(relay_hologen,HIGH);
  digitalWrite(relay_blower,HIGH);    
}
}
void main_menu() {
  lcd.setCursor(0,2);
  lcd.print("Pilih Bahan :");
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.setCursor(0, 3);
      lcd.print("  Catton >  ");
      break;
    case 2:
      lcd.setCursor(0, 3);
      lcd.print("< Sutra >  ");
      break;
    case 3:
      lcd.setCursor(0, 3);
      lcd.print("< Drill    ");
      break;
    case 4:
      menu = 3;
      break;
  }
}

void executeAction() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
  }
}

void action1() {
  lcd.clear();
  EEPROM.write(0,1);
  lcd.setCursor(2, 1);
  lcd.print("Setup Sukses...!");
  delay(2000);
  lcd.clear();
}
void action2() {
  lcd.clear();
  EEPROM.write(0,2);
  lcd.setCursor(2, 1);
  lcd.print("Setup Sukses...!");
  delay(2000);
  lcd.clear();
}
void action3() {
  lcd.clear();
  EEPROM.write(0,3);
  lcd.setCursor(2, 1);
  lcd.print("Setup Sukses...!");
  delay(2000);
  lcd.clear();
  
}
void data_eeprom() {
  Serial.println(kondisi);
  kondisi=EEPROM.read(0);
  if(kondisi == 1){
    set_suhu = 20.00;
    lcd.setCursor(2, 1);
    lcd.print("Catton");
  }
 if(kondisi==2){
    set_suhu = 28.00;
    lcd.setCursor(2, 1);
    lcd.print("Sutra  ");
  }
  if(kondisi==3){
    set_suhu = 38.00;
    lcd.setCursor(2, 1);
    lcd.print("Drill  ");
  }
}
void sensor_suhu(){
 val = analogRead(A0);              //Acquisition analog value of val
  val = (5.00 / 1023.00) * val;      //Conversion to voltage
  vr = vcc - val;
  rt = val / (vr / r);               //Resistance of rt
  
  ln = log(rt / rt0);
  suhu = (1 / ((ln / b) + (1 / T0))); //Temperature from thermistor
  
  suhu = suhu - 273.15; 
   lcd.setCursor(0,0);
  lcd.print("T:");    
  lcd.print(suhu);
  lcd.write(0b11011111);
  lcd.print("C ");
}
void sensor_kelembaban(){
float h = dht.readHumidity();

lcd.setCursor(11,0);     
lcd.print("H:");
lcd.print(h);
lcd.print("%  ");
}
