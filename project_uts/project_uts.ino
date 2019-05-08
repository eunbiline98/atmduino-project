#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

const int analogInPin = A0;  // pin potensiometer 
const int analogOutPin = 13; // pin indikator

int sensorValue ;        // value read from the pot
int outputValue ;        // value output to the PWM (analog out)
int led1    = 4 ;
int led2    = 5;
int button  = 3;

void setup() {

 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
 pinMode(button, INPUT); 
 lcd.begin(16, 2); // ukuran lcd 16 baris 2 kolom

 lcd.setCursor(0,0); // kordinat (baris,kolom)
 lcd.print ("Ath Thaareq M");
 lcd.setCursor(0,1);
 lcd.print ("16202006");
 delay(1000);
 lcd.clear();
 
 lcd.setCursor(0,0); 
 lcd.print ("Sensor  Actuator");
 lcd.setCursor(6,1);
 lcd.print ("UTS");
 delay(1000);
 lcd.clear();
 
 lcd.setCursor(3,0);
 lcd.print ("READY...!!");
 delay(500);
 
 lcd.clear();
}

void loop() {
 
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(analogOutPin, outputValue);

// keluaran Vout dari sensor
    //int nilai = analogRead (A0);
    //float tegangan_hasil = 5.0 * nilai / 1024;
  //tampilan hasil output nilai analog
  //Serial.print ("Vout=");
  //Serial.print (tegangan_hasil);
  //Serial.print (" V");
    
// tampilan hasil nilai digital sensor
lcd.setCursor(0,0);
  lcd.print("Sensor =");
  lcd.print(outputValue);
  lcd.print(" ");
  
//lcd.setCursor(0,1);
  //lcd.print("Output =");
  //lcd.print(outputValue);
  //lcd.print("  ");
 

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (digitalRead(button) == HIGH) {
    
   // digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Led 1 Menyala");
    
  } 
  else if (digitalRead(button) == LOW) {
  
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    lcd.setCursor(0,1);
    lcd.print("Led 2 Menyala");
    lcd.print("          ");
  }
  else if (digitalRead(button) == LOW){

    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    lcd.setCursor(0,1);
    lcd.print("Led 1 Menyala");
    lcd.print("          ");
  }
   else if (digitalRead(button) == LOW) {
  
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    lcd.setCursor(0,1);
    lcd.print("Led 2 Menyala");
    lcd.print("          ");
  }
  
  delay(200);
}
