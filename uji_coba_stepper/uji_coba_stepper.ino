#include <AccelStepper.h>
#define HALFSTEP 8

//pin driver motor
#define motor1 8
#define motor2 9
#define motor3 10
#define motor4 11

//instalasi
AccelStepper stepper1(HALFSTEP, motor1, motor2, motor3, motor4);

void setup() {
  // put your setup code here, to run once:
  stepper1.setMaxSpeed(2000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(1000);
  stepper1.moveTo(20000);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (stepper1.distanceToGo()==0){
    stepper1.moveTo(-stepper1.currentPosition());
  }
stepper1.run();
}
