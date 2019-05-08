#include <Adafruit_PN532.h>
#include <Wire.h>
#include <SPI.h>
 
#define SCK  (13)
#define MOSI (11)
#define SS   (10)
#define MISO (12)
 
Adafruit_PN532 nfc(SCK, MISO, MOSI, SS);
 
void setup(void) {
  Serial.begin(9600);
  Serial.println("Test spi port rfid reader PN532 ");
  Serial.println("sabar tunggu 3 detik.....");
  delay(3000);
  nfc.begin();
 
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("board error");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Device Found PN5 Chip"); 
  Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware version > "); 
  Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.println((versiondata>>8) & 0xFF, DEC);
  nfc.SAMConfig(); //Set to read RFID tags
  Serial.println("silahkan tap kartu");
}
 
 
void loop(void) {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    
  // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
  // 'uid' will be populated with the UID, and uidLength will indicate
  // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  if (success) {
 
    Serial.println("kartu terbaca");
    Serial.print(" UID Length: ");
    Serial.print(uidLength, DEC);
    Serial.println(" BYTES");
    Serial.print("  UID VAL: ");
    nfc.PrintHex(uid, uidLength);
 
    if (uidLength == 4)
    {
      Serial.println(" MIFACE CLASSIC CARD > (4 byte UID)");
   
      // Factory default keyA is 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
      Serial.println("Authenticating block 4");
      uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; //Default Key    
    }
  }
}
