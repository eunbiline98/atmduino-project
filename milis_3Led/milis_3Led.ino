int pin1 =  8;        // Pin LED1
int pin2 =  9;        // Pin LED2
int pin3 =  10;        // Pin LED3
long tunggu1 = 3000;   // Waktu tunggu LED1
long tunggu2 = 4000;   // Waktu tunggu LED2
long tunggu3 = 5000;   // Waktu tunggu LED3
long mati    = 6000;   // Waktu tunggu MATI
long mulai;            // Waktu mulai
 
void setup() 
{
    // Set pin sebagai output
    pinMode(pin1, OUTPUT);      
    pinMode(pin2, OUTPUT);      
    pinMode(pin3, OUTPUT);
 
    // Catat waktu sekarang ke variable mulai
    mulai = millis();
} 
 
void loop() { 
 awal:
    // Apakah waktu kini sudah melewati waktu tunggu1 ? 
    if ( millis() > mulai + tunggu1 ) { 
        digitalWrite(pin1, HIGH); // Bila ya, nyalakan LED1 
    } 
 
    // Apakah waktu kini sudah melewati waktu tunggu2 ? 
    if ( millis() > mulai + tunggu2 ) { 
        digitalWrite(pin2, HIGH); // Bila ya, nyalakan LED2 
    } 
 
    // Apakah waktu kini sudah melewati waktu tunggu3 ? 
    if ( millis() > mulai + tunggu3 ) { 
        digitalWrite(pin3, HIGH); // Bila ya, nyalakan LED3 
    } 
    if ( millis() > mulai + mati ) { 
        digitalWrite(pin3, LOW); // mati
        digitalWrite(pin2, LOW); // mati
        digitalWrite(pin1, LOW); // mati 
    } 
    goto awal; 
}
