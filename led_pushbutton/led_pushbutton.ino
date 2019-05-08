int led1 = 2 ;
int led2 = 3 ;
int led3 = 4 ;

int button1 = 6 ;
int button2 = 7 ;
int button3 = 8 ;

void setup() {
  // put your setup code here, to run once:
pinMode (led1, OUTPUT);
pinMode (led2, OUTPUT);
pinMode (led3, OUTPUT);
pinMode (button1, INPUT);
pinMode (button2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(button1) == LOW) {
    
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    
delay(200);

    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    
delay(200);

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    
delay(200);
    } 
  
  else if (digitalRead(button2) == LOW) {

    digitalWrite(led1,LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
   
delay(200);

    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    
delay(200);

    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    
delay(200);
    }

  else if (digitalRead(button3) == LOW) {

    digitalWrite(led1,HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
   
delay(200);

    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    
delay(150);

    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    
delay(200);
    }
    
  else {
    // turn LED off:
    digitalWrite(led1, LOW);
     digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
  }
 }
