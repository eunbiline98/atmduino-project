#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE);


Servo servo;
int servoPos = 0;
long duration, distance;


#define buzzerPin A1
#define trigPin   13
#define echoPin   12

int senVal1 = 0;
int senVal2 = 0;

#define RST_PIN 8
#define SS_PIN 10

int card1Balance = 1000;
int card2Balance = 300;

#define num 7
char Data[num];
byte data_count = 0;

String num1, num2, card, card2;


bool recharge = true;

MFRC522 mfrc522(SS_PIN, RST_PIN);




void setup () {
  lcd.begin(16, 2);
  Serial.begin(9600);

  servo.attach(9);

  servo.write(30);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  KP2.SetKeypadVoltage(5.0);

  SPI.begin();
  mfrc522.PCD_Init();

  lcd.setCursor(0, 0);
  lcd.print(" Automatic toll");
  lcd.setCursor(0, 1);
  delay(3000);
  lcd.clear();
}
void loop()
{

  if (recharge == 0)
  {
    reCharge();
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("   Welcome!!!");
    sensorRead();
    rfid();
    KeyPad();
    if (distance < 16)
    {
      servoDown();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Vehicle detected");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Put your card to");
      lcd.setCursor(0, 1);
      lcd.print("the reader......");
      delay(2000);
      lcd.clear();

    }
  }
}

void servoDown()
{
  servo.attach(9);
  for (servoPos = 30; servoPos <= 120; servoPos += 1)
  {
    servo.write(servoPos);
    delay(5);
  }
}

void servoUp()
{
  servo.attach(9);
  for (servoPos = 120; servoPos >= 30; servoPos -= 1)
  {
    servo.write(servoPos);
    delay(5);
  }
}

void sensorRead()
{
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print("Jarak: ");
  Serial.println(distance);
}

void rfid()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  if (content.substring(1) == "2F 7D 68 68")
  {
    if (card1Balance >= 500)
    {
      lcdPrint();
      card1Balance = card1Balance - 500;
      lcd.setCursor(9, 1);
      lcd.print(card1Balance);
      delay(2000);
      lcd.clear();
      state = 1;
    }
    else
    {
      card = content.substring(1);
      LcdPrint();
      lcd.setCursor(9, 1);
      lcd.print(card1Balance);
     // lcd.print(" Tk");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Please Recharge");
      delay(1000);
      lcd.clear();
      state = 0;
    }
  }
  else if (content.substring(1) == "F4 C2 37 BB")
  {
    if (card2Balance >= 500)
    {
      lcdPrint();
      card2Balance = card2Balance - 500;
      lcd.setCursor(9, 1);
      lcd.print(card2Balance);
      delay(2000);
      lcd.clear();
      state = 1;
    }
    else
    {
      card = content.substring(1);
      LcdPrint();
      lcd.setCursor(9, 1);
      lcd.print(card2Balance);
      lcd.print(" Tk");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Please Recharge");
      lcd.clear();
      delay(1000);
      state = 0;
    }
  }

  else   {
    digitalWrite(buzzerPin, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Unknown Vehicle");
    lcd.setCursor(0, 1);
    lcd.print("Access denied");
    delay(1500);
    lcd.clear();
    digitalWrite(buzzerPin, LOW);
  }
}

void KeyPad()
{
  byte KState = KP2.Key_State();

  if (KState == PRESSED)
  {
    Key = KP2.Getkey();
    if (Key)
    {
      if (Key == 'A')
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Recharging Mode.");
        lcd.setCursor(0, 1);
        lcd.print("................");
        delay(1500);
        lcd.clear();
        recharge = 0;
      }
    }
  }
}

void clearData()
{
  while (data_count != 0)
  {
    Data[data_count--] = 0;
  }
  return;
}

void reCharge()
{

  lcd.setCursor(0, 0);
  lcd.print ("Enter the amount");

  byte KState = KP2.Key_State();

  if (KState == PRESSED)
  {
    Key = KP2.Getkey();
    if (Key)
    {
      if (Key == 'D')
      {
        if (card == "73 50 76 2E")
        {
          num1 = Data;
          card1Balance = num1.toInt() + card1Balance;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Your current");
          lcd.setCursor(0, 1);
          lcd.print("balance: ");
          lcd.setCursor(9, 1);
          lcd.print (card1Balance);
          lcd.print(" Tk");
          delay(3000);
          clearData();
          lcd.clear();
          recharge = 1;
        }
        else if (card == "F4 C2 37 BB")
        {
          num2 = Data;
          card2Balance = num2.toInt() + card2Balance;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Your current");
          lcd.setCursor(0, 1);
          lcd.print("balance: ");
          lcd.setCursor(9, 1);
          lcd.print (card2Balance);
          lcd.print(" Tk");
          delay(3000);
          clearData();
          lcd.clear();
          recharge = 1;
        }
      }
      else
      {
        Data[data_count] = Key;
        lcd.setCursor(data_count, 1);
        lcd.print(Data[data_count]);
        data_count++;
      }
    }
  }
}
void lcdPrint()
{
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Successfully");
  lcd.setCursor(0, 1);
  lcd.print(" paid your bill");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your Remaining");
  lcd.setCursor(0, 1);
  lcd.print("balance: ");
}

void LcdPrint()
{
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
  delay(100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Your balance");
  lcd.setCursor(0, 1);
  lcd.print(" is insufficent");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Your Remaining");
  lcd.setCursor(0, 1);
  lcd.print("balance: ");
}
