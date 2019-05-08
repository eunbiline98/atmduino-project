#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // alamat i2c lcd dan type lcd 16x2
 
const byte pump = 8;
#define LIMIT 600 // kelembapan tanah
 
void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
lcd.begin();
lcd.backlight();
pinMode(A0, INPUT_PULLUP);
pinMode(pump, OUTPUT);
pinMode(LED_BUILTIN, OUTPUT);
   
lcd.setCursor(0,0);
lcd.print("PENYIRAMAN CABAI");
lcd.setCursor(0,1);
lcd.print("OTOMATIS...");
delay(3000);
lcd.clear();
}
 
void loop() {
// put your main code here, to run repeatedly:
int s_soil = analogRead(A0);
Serial.println(s_soil);
  if ( s_soil > LIMIT){
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Ukur: ");
    lcd.print(s_soil);
    
    lcd.setCursor(0,1);
    lcd.print("POMPA HIDUP..");
    digitalWrite(pump, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("POMPA HIDUP");
 }
    else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Ukur: ");
      lcd.print(s_soil);
      lcd.setCursor(0,1);
      lcd.print("POMPA MATI...");
      digitalWrite(pump, LOW);
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("POMPA MATI");
 }
    delay(250);
}
