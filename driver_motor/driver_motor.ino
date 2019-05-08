void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
pinMode(12,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()){
  int inByte = Serial.read();
  if(inByte == 'a')
  {digitalWrite(13,HIGH);
  digitalWrite(12,LOW);
  Serial.println("arah motor kanan");
  }
  
  if(inByte == 'b')
  {digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  Serial.println("arah motor kiri");
}

  if(inByte == 'c')
  {digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  Serial.println("Stop");
}
  }
}

