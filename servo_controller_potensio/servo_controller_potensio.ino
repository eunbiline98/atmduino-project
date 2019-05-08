#include <Servo.h>

Servo servo1;
int angle = 0;
void setup()
{
servo1.attach(10);
}
void loop()
{
analogRead(0);
angle=map(angle, 0, 1023, 0, 180);
servo1.write(angle);
delay(15);
} 
