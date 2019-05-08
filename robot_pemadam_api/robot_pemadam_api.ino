//==========================================================================================
//  Progam ini di buat oleh Misbah najh (FB)
//  Program dikendalikan menguanakan sensor jarak Ultrasonic 
//  mengunakan motor servo MG995,sensor hc-sr04,flame sensor 5channel, fan L9110, arduino uno,dan chassis
//  Chassis+servo modif didapatkan https://www.tokopedia.com/microbot/frame-chassis-robot-pemadam-api-servo-roda
//  Tutorial dan video klik  https://www.sinauduino.blogspot.co.id
//  full tutorial video https://www.youtube.com/watch?v=BL8ZB5-ql9Q
//==========================================================================================

//inisialisai motor servo
#include <Servo.h>
#define RODA1 4 
#define RODA2 5 
Servo Roda1; Servo Roda2; 

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

//KALIBRASI KECEPATAN DAN SETPOIN SENSOR
int kecepataan =650; // NILAI RESPON BELOK 90* (500-1000);
int rodakanan  =65;  // NILAI RESPON RODA KANAN (75-90);
int rodakiri   =80;  // NILAI RESPON RODA KIRI (75-80);
int setpoin    =7;   // NILAI TOLERANSI JARAK HINDAR (7-15);
int lintasan   =200; // NILAI TOLERANSI WARNA LINTASAN (0-1024)
int api        =500; // NILAI TOLERANSI CAHAYA API (0-1024)
 
//inisialisasi sensor 1 sebelah kiri
#include <NewPing.h>
#define echo1    8
#define trigger1 7
NewPing sonar1(trigger1,echo1,100);

//inisialisasi sensor 2 sebelah depan
#define echo2    12
#define trigger2 11
NewPing sonar2(trigger2,echo2,100);

//inisialisasi sensor 2 sebelah kanan
#define echo3    10
#define trigger3 9
NewPing sonar3(trigger3,echo3,100);

//definisi pin kipas dan pin buzzer
#define kipas 6
#define buzzer 3
bool keadaan;
void setup() {
 Serial.begin(9600); // serial monitor "menampilkan data sensor"
 lcd.begin(16,2);
 diam(3000);
 Roda1.attach(RODA1);  //pin motor servo
 Roda2.attach(RODA2);  
 pinMode(kipas,INPUT); 
 pinMode(buzzer,OUTPUT);
 keadaan = 0;

 lcd.setCursor(0,0);
 lcd.print(" Astro-Tech ");
 lcd.setCursor(0,1);
 ldc.print("Stmik ASIA Ready")
 delay(500);
 lcd.clear();
 } 

void loop() {
// sensor mengukur dan membaca
int jarak1 =sonar1.ping_cm(); // sensor kiri
int jarak2 =sonar2.ping_cm(); // sensor depan
int jarak3 =sonar3.ping_cm(); // sensor kanan
int sensor = analogRead(A0); // pin sensor tcr5000
int api    = analogRead(A1); // pin sensor Api A1-A5
//sensor menampilkan data yang dibaca
Serial.print(jarak1);
Serial.print("   ||   ");
Serial.print(jarak2);
Serial.print("   ||   ");
Serial.print(jarak3);
Serial.print("   ||   ");
Serial.print(api);
Serial.print("   ||   ");
Serial.println(sensor);

//tampilan sensor lcd
lcd.setCursor(1,0);
lcd.print(jarak1);
lcd.print("");
lcd.setCursor(5,0);
lcd.print(jarak2);
lcd.print("");
lcd.setCursor(9,0);
lcd.print(jarak3);
lcd.print("");
lcd.setCursor(13,0);
lcd.print(api);
lcd.print("");
lcd.setCursor(0,5);
lcd.print(sensor);

//case utama jika api terdeteksi maka exsekusi
if ((api2>api||api3>api||api4>api) && (jarak2>1&&jarak2<15)){
digitalWrite(buzzer,HIGH);  //buzzer bunyi
pinMode(kipas, OUTPUT); digitalWrite(kipas,LOW);//kipas bergerak
diam(2000); // panggil diam "lihat inisialisasi progam pangillan"
tiup(kecepataan);  //panggil tiup
diam(1000); //panggil diam
keadaan = 1; 
}

//case terakhir jika api tidak terdeteksi maka exsekusi
else{
digitalWrite(buzzer,LOW); // buzzer mati
pinMode(kipas, INPUT); digitalWrite(kipas,HIGH); // kipas berhenti
if (sensor>lintasan && keadaan > 0){
  maju();
  delay(kecepataan);
  diam (100000);
}
//jika sensor kiri terdeteksi maka belok kanan
else if (jarak1<setpoin&&jarak1>1){ 
  kanan(); //panggil kanan
  delay(50);
  }
//jika sensor kanan terdeteksi maka belok kiri
else if (jarak3<setpoin&&jarak3>1){
  kiri();
  delay(50);
  }
//jika sensor depan terdeteksi maka balik (balik belum ditentukan)
else if (jarak2<setpoin&&jarak2>1){
  //jika sensor kiri < sensor kanan maka ditentukan "balik kanan"
  if (jarak1<jarak3){
  balik_kanan();
  delay(kecepataan);
  }
  //jika sensor kanan > sensor kanan maka ditentukan "balik kiri"
  else if (jarak1>jarak3){
  balik_kiri();
  delay(kecepataan);
}
}
//jika semua sensor (sensor api dan sensor ultrasonik tidak terdeteksi) maka maju
else{
  maju();
  delay(100);
}
}
}

// inisialisasi progam pangillan
void maju(){
  Roda1.write(380);
  Roda2.write(-380);
}
void mundur(){
  Roda1.write(-380);
  Roda2.write(380);
}
void balik_kiri(){
  Roda1.write(-380);
  Roda2.write(-380);
}
void balik_kanan(){
  Roda1.write(380);
  Roda2.write(380);
}
void kanan(){
 Roda1.write(380);
 Roda2.write(rodakanan); //nilai roda2 agak lambat
}
void kiri(){
 Roda1.write(rodakiri); //nilai roda1 agak lambat
 Roda2.write(-380);
}
void diam(int x){
  pinMode(RODA1,INPUT);
  pinMode(RODA2,INPUT);
  digitalWrite(RODA1,LOW);
  digitalWrite(RODA2,LOW);
  delay(x);
  pinMode(RODA1,OUTPUT);
  pinMode(RODA2,OUTPUT);
  }
void tiup(int x){
balik_kanan();
delay(x/4);
diam(x);
balik_kiri();
delay(x/2);
diam(x);
balik_kanan();
delay(x/2);
diam(x);
balik_kiri();
delay(x/4);
diam(x);
}


