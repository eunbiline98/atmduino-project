#include <Stepper.h>

#define STEPS_PER_MOTOR_REVOLUTION 32   
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048  

Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 8, 10, 9, 11);

int  Steps2Take;

void setup(){

}

void loop(){

  Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION / .05;  
  small_stepper.setSpeed(400);   
  small_stepper.step(Steps2Take);
  delay(1000);
  
  Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION / .05;   
  small_stepper.setSpeed(700); 
  small_stepper.step(Steps2Take);
  delay(2000);

}

