const int DA = A0;
const int led_01 = 4;
const int led_02 = 5;
const int led_03 = 6;
const int led_04 = 7;
const int led_05 = 8;
const int led_06 = 9;
const int led_07 = 10;
const int led_08 = 11;
const int led_09 = 12;
 
int sVal_01 = 500; // Initial Threshold
int sVal_02 = 504;
int sVal_03 = 508;
int sVal_04 = 508;
int sVal_05 = 512;
int sVal_06 = 516;
int sVal_07 = 520;
int sVal_08 = 524;
int sVal_09 = 528;

int lastPin = 12; 
int totalLED = 9; 

int debugSwitch = true; 
int ledTest = true; 


int sensorvalue = 0; 
 
void setup() {
  Serial.begin(9600);
  for (int i = 3; i <= lastPin; i++) {
    pinMode(i, OUTPUT);
  }

  if (ledTest == true) {
    testLight(); 
  }
}

void loop() {
  sensorvalue = analogRead(DA); 
  if (debugSwitch == true) {
    debug();
  } else {
    Serial.println("The debugging mode is set to false!");
  }
  musicLights();
}

void debug() {
  Serial.print("Sound Value: ");

  if (sensorvalue >= sVal_01) {
    Serial.print(sensorvalue);
    Serial.println(" - LED ON!");
  } else {
    Serial.println(sensorvalue);
  }
}

void testLight() {
  digitalWrite(led_05, HIGH);
  delay(1000);
  digitalWrite(led_04, HIGH);
  digitalWrite(led_06, HIGH);
  delay(1000);
  digitalWrite(led_03, HIGH);
  digitalWrite(led_07, HIGH);
  delay(1000);
  digitalWrite(led_02, HIGH);
  digitalWrite(led_08, HIGH);
  delay(1000);
  digitalWrite(led_01, HIGH);
  digitalWrite(led_09, HIGH);
  delay(2000);
  digitalWrite(led_01, LOW);
  digitalWrite(led_09, LOW);
  delay(500);
  digitalWrite(led_02, LOW);
  digitalWrite(led_08, LOW);
  delay(500);
  digitalWrite(led_03, LOW);
  digitalWrite(led_07, LOW);
  delay(500);
  digitalWrite(led_04, LOW);
  digitalWrite(led_06, LOW);
  delay(500);
  digitalWrite(led_05, LOW);
}

void musicLights() {
    
  if(sensorvalue >= sVal_01) {
    digitalWrite(led_05, HIGH);
  } else {
    digitalWrite(led_05, LOW);
  }

  if(sensorvalue >= sVal_02) {
    digitalWrite(led_04, HIGH);
  } else {
    digitalWrite(led_04, LOW);
  }

  if(sensorvalue >= sVal_03) {
    digitalWrite(led_06, HIGH);
  } else {
    digitalWrite(led_06, LOW);
  }

  if(sensorvalue >= sVal_04) {
    digitalWrite(led_03, HIGH);
  } else {
    digitalWrite(led_03, LOW);
  }

  if(sensorvalue >= sVal_05) {
    digitalWrite(led_07, HIGH);
  } else {
    digitalWrite(led_07, LOW);
  }

  if(sensorvalue >= sVal_06) {
    digitalWrite(led_02, HIGH);
  } else {
    digitalWrite(led_02, LOW);
  }

  if(sensorvalue >= sVal_07) {
    digitalWrite(led_08, HIGH);
  } else {
    digitalWrite(led_08, LOW);
  }

  if(sensorvalue >= sVal_08) {
    digitalWrite(led_01, HIGH);
  } else {
    digitalWrite(led_01, LOW);
  }

  if(sensorvalue >= sVal_09) {
    digitalWrite(led_09, HIGH);
  } else {
    digitalWrite(led_09, LOW);
  }
}
