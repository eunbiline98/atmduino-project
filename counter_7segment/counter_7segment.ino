int A = 2;
int B = 3;
int C = 4;
int D = 6;
int DP = 5;
int E = 7;
int F = 8;
int G = 9;

int switchUpPin = 13;
int switchDownPin = 12;
int counter = 0;
int buttonUpState = 0;
int lastButtonUpState = 0;
int buttonDownState = 0;
int lastButtonDownState = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(switchUpPin,INPUT_PULLUP);
  pinMode(switchDownPin,INPUT_PULLUP);
  

  digitalWrite(DP , HIGH);
}

void loop()
{
  buttonUpState = digitalRead(switchUpPin);
  buttonDownState = digitalRead(switchDownPin);

  if (buttonUpState != lastButtonUpState)
  {
    if (buttonUpState == HIGH)
    {
      if (counter == 100)
      {
        counter = -1;
      }
      counter++;
      Serial.println(counter);
      changeNumber(counter);
      delay(300);
    }
    else
    {
      Serial.println("OFF");
    }
    delay(50);
  }


  if (buttonDownState != lastButtonDownState)
  {
    if (buttonDownState == HIGH)
    {
      if (counter == 0)
      {
        counter = 100;
      }
      counter--;
      Serial.println(counter);
      changeNumber(counter);
      delay(300);
    }
    else
    {
      Serial.println("OFF");
    }
    delay(50);
  }
  changeNumber(counter);
}

void changeNumber(int buttonPress)
{
  switch (buttonPress)
  {
    //number 0
    case 0:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;
    //number 1
    case 1:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    //number 2
    case 2:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;
    //number 3
    case 3:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;
    //number 4
    case 4:
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    //number 5
    case 5:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    //number 6
    case 6:
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    //number 7
    case 7:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    //number 8
    case 8:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    //number 9
    case 9:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;

      case 10:
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
  }

}
