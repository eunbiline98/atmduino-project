void setup() {
  // put your setup code here, to run once:

{
#define selA A0
#define selB A1
#define selC A2
void setup(){
Serial.begin(9600);
pinMode(selA, OUTPUT);
pinMode(selB, OUTPUT);
pinMode(selC, OUTPUT);
}
int line[17];
void switchMUX(int a, int b, int c)
{
  digitalWrite(selA, a);
  digitalWrite(selB, b);
  digitalWrite(selC, c);
}
void readMux()
{
  switchMUX(0,0,0);
  line[9] = analogRead(A3);
  line[6] = analogRead(A4);
  switchMUX(0,0,1);
  line[15] = analogRead(A3);
  line[3] = analogRead(A4);
  switchMUX(0,1,0);
  line[11] = analogRead(A3);
  line[4] = analogRead(A4);
  switchMUX(0,1,1);
  line[14] = analogRead(A3);
  line[2] = analogRead(A4);
  switchMUX(1,0,0);
  line[10] = analogRead(A3);
  line[5] = analogRead(A4);
  switchMUX(1,0,1);
  line[12] = analogRead(A3);
  line[0] = analogRead(A4);
  switchMUX(1,1,0);
  line[8] = analogRead(A3);
  line[7] = analogRead(A4);
  switchMUX(1,1,1);
  line[13] = analogRead(A3);
  line[1] = analogRead(A4);
}
void loop()
{
  readMux();
  Serial.print(line[0]);
  Serial.print(" ");
  Serial.print(line[1]);
  Serial.print(" ");
  Serial.print(line[2]);
  Serial.print(" ");
  Serial.print(line[3]);
  Serial.print(" ");
  Serial.print(line[4]);
  Serial.print(" ");
  Serial.print(line[5]);
  Serial.print(" ");
  Serial.print(line[6]);
  Serial.print(" ");
  Serial.print(line[7]);
  Serial.print(" ");
  Serial.print(line[8]);
  Serial.print(" ");
  Serial.print(line[9]);
  Serial.print(" ");
  Serial.print(line[10]);
  Serial.print(" ");
  Serial.print(line[11]);
  Serial.print(" ");
  Serial.print(line[12]);
  Serial.print(" ");
  Serial.print(line[13]);
  Serial.print(" ");
  Serial.print(line[14]);
  Serial.print(" ");
  Serial.println(line[15]);
  delay(1000);
