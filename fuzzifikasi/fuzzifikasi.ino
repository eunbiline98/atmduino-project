float suhu;
float dingin,hangat,panas;
float pwm;
float Lambat,Sedang,Cepat;
unsigned char suhuDingin(){
  if (suhu <= 30){dingin =1;}
  else if (suhu >=30 && suhu <=45){dingin=(45-suhu)/15;}
  else if (suhu >= 45){dingin =0;}
  return dingin;
}
unsigned char suhuHangat(){
  if (suhu <= 30){hangat =0;}
  else if (suhu >=30 && suhu <=45){hangat=(suhu-30)/15;}
  else if (suhu >=45 && suhu <=60){hangat=(60-suhu)/15;}
  else if (suhu >= 60){hangat =0;}
  return hangat;
}
unsigned char suhuPanas (){
  if (suhu <=45 ){panas =0;}
  else if (suhu >=45 && suhu <=60){panas=(suhu-45)/15;}
  else if (suhu >= 60){panas =1;}
  return panas;
}
unsigned char pwmLambat(){
  if (pwm <= 100){Lambat =1;}
  else if (pwm >=100 && pwm <=150){Lambat=(150-pwm)/50;}
  else if (pwm >= 150){Lambat =0;}
  return Lambat;
}
unsigned char pwmSedang(){
  if (pwm <= 100){Sedang =0;}
  else if (pwm >=100 && pwm <=150){Sedang=(pwm-100)/50;}
  else if (pwm >=150 && pwm <=200){Sedang=(200-pwm)/50;}
  else if (pwm >= 200){Sedang =0;}
  return Sedang;
}
unsigned char pwmCepat (){
  if (pwm <= 100){Lambat =1;}
  else if (pwm >=150 && pwm <=200){Cepat=(pwm-150)/50;}
  else if (pwm >= 200){Cepat =0;}
  return Cepat;
}
void fuzzifikasi(){
  suhuDingin();
  suhuHangat();
  suhuPanas();
  pwmLambat();
  pwmSedang();
  pwmCepat();
}
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
suhu = 54; // contoh kita memasukan nilai suhu 54 derajat
pwm = 104; // contoh kita memasukan nilai pwm 104
fuzzifikasi(); // memanggil fungsi fuzzifikasi untuk menghitung keanggotaan masing2 variable
Serial.print("dingin : ");
Serial.print(dingin);
Serial.print("t");
Serial.print("hangat : ");
Serial.print(hangat);
Serial.print("t");
Serial.print("panas : ");
Serial.println(panas);
Serial.print("lambat : ");
Serial.print(Lambat);
Serial.print("t");
Serial.print("sedang : ");
Serial.print(Sedang);
Serial.print("t");
Serial.print("cepat : ");
Serial.println(Cepat);
}
void loop() {
  // put your main code here, to run repeatedly:
}
