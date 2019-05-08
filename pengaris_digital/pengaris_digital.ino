#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);

#define echoPin 4 // echo
#define trigPin 5 // trig

int maximumRange = 200; //kebutuhan akan maksimal range
int minimumRange = 0; //kebutuhan akan minimal range
long durasi, jarak; //waktu untuk kalkulasi jarak

void setup() {
 //type lcd
 Serial.begin(9600);
 lcd.begin(16, 2); // ukuran lcd 16 baris 2 kolom
 lcd.setCursor(3,0);
 lcd.print ("Penggaris");
 lcd.setCursor(4,1);
 lcd.print ("Digital");
 delay(1500);
 lcd.clear();
 lcd.setCursor(3,0);
 lcd.print ("READY...!!");
 delay(500);
 lcd.clear();
 
 pinMode(echoPin, INPUT);
 pinMode(trigPin, OUTPUT);
}

void loop() {
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 
 digitalWrite(trigPin, LOW);
 
 durasi = pulseIn(echoPin, HIGH);
 jarak = durasi/58.2;

  lcd.setCursor(0,0);
  lcd.print("Jarak =");
  lcd.print(jarak);
  lcd.print("cm   ");

  Serial.println("Jarak =");
  Serial.println(jarak);
  Serial.println("cm   ");
  
  delay(500);

}

