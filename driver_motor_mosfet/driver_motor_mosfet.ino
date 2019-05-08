const int bt = 5;
const int bt2 = 6;
int st = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(bt, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  int bt = 0;
  int bt2 = 0;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
      if(digitalRead(bt)==0 && st == 0){
       // lcd.clear();
       digitalWrite(8, HIGH);
        digitalWrite(9, LOW); 
        delay(500); 
        
        st =1;
        
      }
      if(digitalRead(bt)==0 && st == 1){
       // lcd.clear();
        delay(500);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW); 
        st =0;
       
      }
      
      if(digitalRead(bt2)==0 && st == 0){
       // lcd.clear();
       delay(500);
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH); 
        
        st =1;
       
      }

      if(digitalRead(bt2)==0 && st == 1){
       // lcd.clear();
        delay(500);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW); 
        st =0;
      
      }
    }
