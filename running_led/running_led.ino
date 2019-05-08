int ledPin1 = 0;
int ledPin2 = 1;
int ledPin3 = 2;
int ledPin4 = 3;
int ledPin5 = 4;
// type data yang berfungsi sebagai penyimpan bilangan bulat
 
void setup() 
{
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(ledPin3, OUTPUT);
pinMode(ledPin4, OUTPUT);
pinMode(ledPin5, OUTPUT);
// menjadikan PIN 0, 1, 2, 3, dan 4 sebagai OUTPUT
}
 
void loop()
// Menyalakan LED sacara bergilir 
{
digitalWrite(ledPin1, HIGH);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, LOW);
digitalWrite(ledPin5, LOW);
delay(100);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, HIGH);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, LOW);
digitalWrite(ledPin5, LOW);
delay(100);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, HIGH);
digitalWrite(ledPin4, LOW);
digitalWrite(ledPin5, LOW);
delay(100);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, HIGH);
digitalWrite(ledPin5, LOW);
delay(100);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, LOW);
digitalWrite(ledPin5, HIGH);
delay(100);
//MODE 2
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, LOW);
digitalWrite(ledPin5, HIGH);
delay(100);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, HIGH);
digitalWrite(ledPin5, LOW);
delay(100);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, HIGH);
digitalWrite(ledPin4, LOW);
digitalWrite(ledPin5, LOW);
delay(100);
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, HIGH);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, LOW);
digitalWrite(ledPin5, LOW);
delay(100);
digitalWrite(ledPin1, HIGH);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, LOW);
digitalWrite(ledPin5, LOW);
delay(100);
//MODE 3
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, HIGH);
digitalWrite(ledPin3, HIGH);
digitalWrite(ledPin4, HIGH);
digitalWrite(ledPin5, LOW);
delay(300);
//MODE 4
digitalWrite(ledPin1, LOW);
digitalWrite(ledPin2, HIGH);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, HIGH);
digitalWrite(ledPin5, LOW);
delay(250);
digitalWrite(ledPin1, HIGH);
digitalWrite(ledPin2, LOW);
digitalWrite(ledPin3, LOW);
digitalWrite(ledPin4, LOW);
digitalWrite(ledPin5, HIGH);
delay(250);
//MODE 5
digitalWrite(ledPin1, HIGH);
digitalWrite(ledPin2, HIGH);
digitalWrite(ledPin3, HIGH);
digitalWrite(ledPin4, HIGH);
digitalWrite(ledPin5, HIGH);
delay(350);
}
