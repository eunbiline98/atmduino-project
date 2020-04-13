#include <Wire.h> 
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//EEPROM
#include <EEPROM.h>
byte kondisi;

//themistor
#define rt0 10000   // Ω
#define b 3977      // K
#define vcc 5    //Supply voltage
#define r 10000  //R=10KΩ
int tempPin = A0;
float val, rt, vr, ln, suhu, T0;
float set_suhu=30.00;

#define relay_blower 2 
#define relay_hologen 3 
 
//button
const int btn_up = 4;
const int btn_down = 5;
const int btn_ok = 6;
int menu = 1;

void setup(){
  Serial.begin(9600);
  T0 = 25 + 273.15;
  lcd.begin();
  pinMode(relay_blower,OUTPUT);
  pinMode(relay_hologen,OUTPUT);  
 
  pinMode(btn_up,INPUT_PULLUP);
  pinMode(btn_down,INPUT_PULLUP);
  pinMode(btn_ok,INPUT_PULLUP);
  
  lcd.print("Jemuran Otomatis");  

  digitalWrite(relay_hologen,LOW);  
  digitalWrite(relay_blower,LOW);           
  delay(2000);
  lcd.clear();
  data_eeprom();
}

void loop(){
  sensor_suhu();
  data_eeprom();
  main_menu();
  lcd.setCursor(0,0);
  lcd.print("suhu : ");    
  lcd.print(suhu);
  lcd.write(0b11011111);
  lcd.print("C ");
  lcd.setCursor(0, 1);
  lcd.print("Jenis:");
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
if (!digitalRead(btn_down)){
    menu++;
    main_menu();
    delay(100);
    while (!digitalRead(btn_down));
  }
  if (!digitalRead(btn_up)){
    menu--;
    main_menu();
    delay(100);
    while(!digitalRead(btn_up));
  }
  if (!digitalRead(btn_ok)){
    executeAction();
    main_menu();
    delay(100);
    while (!digitalRead(btn_ok));
  }

//Check suhu is in limit
if(suhu > set_suhu)
{
   digitalWrite(relay_blower,LOW);
   digitalWrite(relay_hologen,HIGH);  
}
else
{  
  digitalWrite(relay_hologen,LOW);
  digitalWrite(relay_blower,HIGH);    
}
 
  delay(100); 
}
void main_menu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.setCursor(6, 1);
      lcd.print(" catton");
      break;
    case 2:
      lcd.setCursor(6, 1);
      lcd.print(" sutra  ");
      break;
    case 3:
      lcd.setCursor(6, 1);
      lcd.print(" drill  ");
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
  EEPROM.write(0,1);
  lcd.setCursor(0, 1);
  lcd.print("Setup Sukses  ");
  delay(2000);
  lcd.clear();  
}
void action2() {
  EEPROM.write(0,2);
  lcd.setCursor(0, 1);
  lcd.print("Setup Sukses  ");
  delay(2000);
  lcd.clear();
}
void action3() {
  EEPROM.write(0,3);
  lcd.setCursor(0, 1);
  lcd.print("Setup Sukses  ");
  delay(2000);
  lcd.clear();
}

void data_eeprom() {
  Serial.println(kondisi);
  kondisi=EEPROM.read(0);
  if(kondisi == 1){
    set_suhu = 20.00;
  }
 if(kondisi==2){
    set_suhu = 28.00;
  }
  if(kondisi==3){
    set_suhu = 38.00;
  }
}
void sensor_suhu(){
  val = analogRead(A0);              //Acquisition analog value of val
  val = (5.00 / 1023.00) * val;      //Conversion to voltage
  vr = vcc - val;
  rt = val / (vr / r);               //Resistance of rt
  
  ln = log(rt / rt0);
  suhu = (1 / ((ln / b) + (1 / T0))); //Temperature from thermistor
  
  suhu = suhu - 273.15;                 //Conversion to Celsius
}
