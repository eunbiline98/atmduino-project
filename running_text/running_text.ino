#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/Arial14.h>

const int WIDTH = 1; // jumlah panel led matrik yang digunakan

const uint8_t *FONT = Arial14;
//const uint8_t *FONT = SystemFont5x7;

const char *MESSAGE = "SELAMAT DATANG DI SISTEM KOMPUTER STMIK ASIA MALANG, Go PIMNAS 2019.....   "; // text / tulisan yang ingin ditampilkan

SoftDMD dmd(WIDTH,1); 
DMD_TextBox box(dmd);

void setup() {
  Serial.begin(9600);
  dmd.setBrightness(255);
  dmd.selectFont(FONT);
  dmd.begin();
}

void loop() {
  const char *next = MESSAGE;
  while(*next) {
    box.print(*next);
    delay(200);
    next++;
  }
}
