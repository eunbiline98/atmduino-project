#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define BINTANG 42
#define PAGAR 35
#define TOMBOL_A 65
#define TOMBOL_B 66
#define TOMBOL_C 67
#define TOMBOL_D 68

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {1,  2,  3, 'A'},
  {4,  5,  6, 'B'},
  {7,  8,  9, 'C'},
  {'*','0', '#','D'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {3, 2, 1, 0}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
long dtKey=0; 
void setup(){
  //Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
} 
void loop(){
  char key = keypad.getKey();
    if (key){
        if(key == BINTANG ){ // clear data = tekan *;
          lcd.clear();
          dtKey=0; key = 0;
          lcd.print(dtKey);
        }

      if ( key == 48 )key=0; // conversi variable '0' ke 0
      lcd.clear(); 
      dtKey = dtKey*10+key;
      lcd.print(dtKey);
    }
}
