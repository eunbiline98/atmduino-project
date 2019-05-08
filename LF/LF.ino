/**************************
 light follower robot
 www.muhilham.com
 30/07/2018
***********************/

//Motor Kiri
#define DIR_KI1 4 // IN4
#define DIR_KI2 5 // IN3
#define PWM_KI  3 // ENB
//Motor Kanan
#define DIR_KA1 7 // IN2
#define DIR_KA2 8 // IN1
#define PWM_KA  9 // ENA

const int pinSensor[3] = {A0, A1, A2};
int level = 150;
int threshold_SenKiri, threshold_SenTengah, threshold_SenKanan;
int baca[3];

int Kec_Min = -170;
int Kec_Max =  200; // Max = 255

void setup() {
  //Serial.begin(9600);
  pinMode(13,  OUTPUT);
  digitalWrite(13, LOW);
  for (int i = 4; i <= 9; i++) { // Set pin digital 4 - 9 sebagai output (direction motor)
    pinMode(i, OUTPUT);
  }
  for (int i = 0; i <= 2; i++) { // Kalibrasi batas ambang nilai sensor
    pinMode(pinSensor[i], INPUT);
    baca[i] = analogRead(pinSensor[i]);
  }
  threshold_SenKiri = baca[0] + level;
  threshold_SenTengah = baca[1] + level;
  threshold_SenKanan = baca[2] + level;
}

void loop() {
  for (int i = 0; i <= 2; i++) {
    baca[i] = analogRead(pinSensor[i]);
  }
  Serial.print(threshold_SenKiri);
  Serial.print("|");
  Serial.print(threshold_SenTengah);
  Serial.print("|");
  Serial.print(threshold_SenKanan);
  Serial.print("\t");
  Serial.print(baca[0]);
  Serial.print("|");
  Serial.print(baca[1]);
  Serial.print("|");
  Serial.print(baca[2]);
  Serial.print("\t");
  followLight();
}

void followLight() {
  int sensor = BacaSensor();
  if (sensor != 0b000) {
    switch (sensor) {
      case 0b001 : driveMotor(Kec_Max / 2, Kec_Max); break;
      case 0b011 : driveMotor(Kec_Max / 3, Kec_Max / 2); break;
      case 0b010 : driveMotor(Kec_Max, Kec_Max); break;
      case 0b111 : driveMotor(Kec_Max, Kec_Max); break;
      case 0b110 : driveMotor(Kec_Max / 2, Kec_Max / 3); break;
      case 0b100 : driveMotor(Kec_Max, Kec_Max / 2); break;
    }
  }
  else {
    driveMotor(0, 0);
  }
}

void driveMotor(int KEC_KI, int KEC_KA) {
  /** Motor Kiri **/
  if (KEC_KI < 0) {
    digitalWrite(DIR_KI1, LOW);
    digitalWrite(DIR_KI2, HIGH);
  }
  else if (KEC_KI > 0) {
    digitalWrite(DIR_KI1, HIGH);
    digitalWrite(DIR_KI2, LOW);
  }
  else {
    digitalWrite(DIR_KI1, HIGH);
    digitalWrite(DIR_KI2, HIGH);
  }

  /** Motor Kanan **/
  if (KEC_KA < 0) {
    digitalWrite(DIR_KA1, LOW);
    digitalWrite(DIR_KA2, HIGH);
  }
  else if (KEC_KA > 0) {
    digitalWrite(DIR_KA1, HIGH);
    digitalWrite(DIR_KA2, LOW);
  }
  else {
    digitalWrite(DIR_KA1, HIGH);
    digitalWrite(DIR_KA2, HIGH);
  }

  analogWrite(PWM_KI, abs(KEC_KI)); // Kirim PWM Kiri
  analogWrite(PWM_KA, abs(KEC_KA)); // Kirim PWM Kanan

  /*** Pembatasan kecepatan ***/
  if (KEC_KI > Kec_Max)KEC_KI = Kec_Max;
  if (KEC_KI < Kec_Min)KEC_KI = Kec_Min;
  if (KEC_KA > Kec_Max)KEC_KA = Kec_Max;
  if (KEC_KA < Kec_Min)KEC_KA = Kec_Min;
  
  Serial.print("PWM Kiri : ");
  Serial.print(KEC_KI);
  Serial.print(" | ");
  Serial.print("PWM Kanan : ");
  Serial.print(KEC_KA);
  Serial.print(" | ");
  Serial.print("   ");
}

int BacaSensor() {
  int SenKiri, SenTengah, SenKanan;
  int Sensor = 0;

  if (baca[0] > threshold_SenKiri) SenKiri = 1;
  else SenKiri = 0;
  if (baca[1] > threshold_SenTengah) SenTengah = 1;
  else SenTengah = 0;
  if (baca[2] > threshold_SenKanan) SenKanan = 1;
  else SenKanan = 0;

  int Sen[3] = {SenKiri, SenTengah, SenKanan};
  for (int i = 0; i <= 2; i++) {
    if (Sen[i] == 1) {
      Sensor = Sensor | (0b100 >> i);
    }
    Serial.print("|");
    Serial.print(Sen[i]);
    Serial.print("|");
    if (i == 2) Serial.println(" ");
  }
  return Sensor;
}
