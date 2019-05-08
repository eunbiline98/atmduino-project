#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

#define kendaliLed1 12
#define kendaliLed2 13
#define kendaliTombol 2
unsigned int sensor[8], nilaiMin[8], nilaiMax[8], nilaiRef[8];
int i, x=0;
boolean biner[8];
void KendaliSelector(int c, int b, int a){
  digitalWrite (A1, a);
  digitalWrite (A2, b);
  digitalWrite (A3, c);
}
void KendaliBacasensor (){
  KendaliSelector (0,0,0);
  sensor[0] = analogRead (A0)/4;
  KendaliSelector (0,0,1);
  sensor[1] = analogRead (A0)/4;
  KendaliSelector (0,1,0);
  sensor[2] = analogRead (A0)/4;
  KendaliSelector (0,1,1);
  sensor[3] = analogRead (A0)/4;
  KendaliSelector (1,0,0);
  sensor[4] = analogRead (A0)/4;
  KendaliSelector (1,0,1);
  sensor[5] = analogRead (A0)/4;
  KendaliSelector (1,1,0);
  sensor[6] = analogRead (A0)/4;
  KendaliSelector (1,1,1);
  sensor[7] = analogRead (A0)/4;
}
void KendaliTampilsensor (){
  bacaSensorbiner();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(biner[0]);
  lcd.setCursor(1,0);
  lcd.print(biner[1]);
  lcd.setCursor(2,0);
  lcd.print(biner[2]);
  lcd.setCursor(3,0);
  lcd.print(biner[3]);
  lcd.setCursor(4,0);
  lcd.print(biner[4]);
  lcd.setCursor(5,0);
  lcd.print(biner[5]);
  lcd.setCursor(6,0);
  lcd.print(biner[6]);
  lcd.setCursor(7,0);
  lcd.print(biner[7]);
  lcd.setCursor (1,1);
  lcd.print ("Sensor Biner");
}
void setup() {
pinMode (A1, OUTPUT);
pinMode (A2, OUTPUT);
pinMode (A3, OUTPUT);
pinMode (kendaliLed1, OUTPUT);
pinMode (kendaliLed2, OUTPUT);
pinMode (kendaliTombol, INPUT);
digitalWrite(kendaliTombol, HIGH);
Serial.begin(9600);
lcd.begin(16,2);
dataSensor();
}
void loop() {
tampilDatasensor();
if (digitalRead(kendaliTombol)==LOW){
  while (digitalRead(kendaliTombol)==LOW){
  }
  kalibrasi();
}

 KendaliTampilsensor ();
}
void kalibrasi (){
  lcd.clear();
  lcd.print ("kalibrasi on !");
  Serial.println ("kalibrasi on !");
 for (i=0; i<8; i++){
  nilaiMin[i] = 1023;
  nilaiMax[i] = 0;
 }
 delay(100);
 while (digitalRead(kendaliTombol) == HIGH){
  digitalWrite (12, HIGH);
  digitalWrite (13, LOW);
  delay(100);
  KendaliBacasensor();
  for(i=0;i<8;i++){
    if(sensor[i] > nilaiMax[i]) nilaiMax[i] = sensor[i];
    if(sensor[i] < nilaiMin[i]) nilaiMin[i] = sensor[i];
  }
  digitalWrite (12, LOW);
  digitalWrite (13, HIGH);
  delay(100);
 }
 lcd.clear();
 lcd.print("Kalibrasi DONE!!");
 Serial.println("Kalibrasi DONE!!");
 digitalWrite (12, HIGH);
 digitalWrite (13, HIGH);
 for(i=0;i<8;i++){
  nilaiRef[i] = (nilaiMax[i] + nilaiMin[i])/2.1;
  EEPROM.write(i,nilaiRef[i]);
 }
 delay(500);
}
void bacaSensorbiner(){
  KendaliBacasensor();
  if (sensor[0] > nilaiRef[0]){
    biner[0] = 0;
  }
  else {
    biner[0] = 1;
  }
    if (sensor[1] > nilaiRef[1]){
    biner[1] = 0;
  }
  else {
    biner[1] = 1;
  }
    if (sensor[2] > nilaiRef[2]){
    biner[2] = 0;
  }
  else {
    biner[2] = 1;
  }
    if (sensor[3] > nilaiRef[3]){
    biner[3] = 0;
  }
  else {
    biner[3] = 1;
  }
    if (sensor[4] > nilaiRef[4]){
    biner[4] = 0;
  }
  else {
    biner[4] = 1;
  }
    if (sensor[5] > nilaiRef[5]){
    biner[5] = 0;
  }
  else {
    biner[5] = 1;
  }
    if (sensor[6] > nilaiRef[6]){
    biner[6] = 0;
  }
  else {
    biner[6] = 1;
  }
    if (sensor[7] > nilaiRef[7]){
    biner[7] = 0;
  }
  else {
    biner[7] = 1;
  }
}
void tampilDatasensor(){
  for(i=0;i<8;i++){
    Serial.print(sensor[i]);
    Serial.print("  ");
  }
  Serial.println(" ");
  delay(100);
}
void dataSensor(){
  for(i=0;i<8;i++){
    nilaiRef[i]=EEPROM.read(i);
  }
}
