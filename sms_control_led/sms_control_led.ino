#include <gprs.h>
#include <softwareserial.h>
 
#define TIMEOUT    5000
#define LED_PIN    13
#define ON 1
#define OFF 0

const int MERAH = 5;
const int BIRU = 6;
 
int StatusMerah;
int StatusBIRU;
GPRS gprs;
 
void setup() {
  pinMode (MERAH , OUTPUT);
  pinMode (BIRU , OUTPUT);
  Serial.begin(9600);
  while(!Serial);
 
  Serial.println("Starting SIM800 Auto Read SMS");
  gprs.preInit();
  delay(1000);
 
  while(0 != gprs.init()) {
      delay(1000);
      Serial.print("init error\r\n");
  } 
 
  //Set SMS mode to ASCII
  if(0 != gprs.sendCmdAndWaitForResp("AT+CMGF=1\r\n", "OK", TIMEOUT)) {
    ERROR("ERROR:CNMI");
    return;
  }
   
  //Start listening to New SMS Message Indications
  if(0 != gprs.sendCmdAndWaitForResp("AT+CNMI=1,2,0,0,0\r\n", "OK", TIMEOUT)) {
    ERROR("ERROR:CNMI");
    return;
  }
 
  Serial.println("Init success");
}
 
//Variable to hold last line of serial output from SIM800
char currentLine[500] = "";
int currentLineIndex = 0;
 
//Boolean to be set to true if message notificaion was found and next
//line of serial output is the actual SMS message content
bool nextLineIsMessage = false;
 
void loop() {
  //Write current status to LED pin
  digitalWrite(MERAH, StatusMerah);
  digitalWrite(BIRU, StatusBIRU);
   
  //If there is serial output from SIM800
  if(gprs.serialSIM800.available()){
    char lastCharRead = gprs.serialSIM800.read();
    //Read each character from serial output until \r or \n is reached (which denotes end of line)
    if(lastCharRead == '\r' || lastCharRead == '\n'){
        String lastLine = String(currentLine);
         
        //If last line read +CMT, New SMS Message Indications was received.
        //Hence, next line is the message content.
        if(lastLine.startsWith("+CMT:")){
           
          Serial.println(lastLine);
          nextLineIsMessage = true;
           
        } else if (lastLine.length() > 0) {
           
          if(nextLineIsMessage) {
            Serial.println(lastLine);
             

// ########## MEMBACA KONTEN SMS DAN MENCARI+MENGARTIKAN KONTEN SMS KE PROGRAM #########
            //Kendali LED MERAH
            if(lastLine.indexOf("MERAH ON") >= 0){
              StatusMerah = 1;
              Serial.println("LED MERAH DINYALAKAN");} 
              else if(lastLine.indexOf("MERAH OFF") >= 0) {
              StatusMerah = 0;
              Serial.println("LED MERAH DIMATIKAN");}
            //Kendali LED BIRU
            if(lastLine.indexOf("BIRU ON") >= 0){
              StatusBIRU = 1;
              Serial.println("LED BIRU DINYALAKAN");} 
              else if(lastLine.indexOf("BIRU OFF") >= 0) {
              StatusBIRU = 0;
              Serial.println("LED BIRU DIMATIKAN");}
             
            nextLineIsMessage = false;
          }
           
        }
         
        //Clear char array for next line of read
        for( int i = 0; i < sizeof(currentLine);  ++i ) {
         currentLine[i] = (char)0;
        }
        currentLineIndex = 0;
    } else {
      currentLine[currentLineIndex++] = lastCharRead;
    }
  }
}
