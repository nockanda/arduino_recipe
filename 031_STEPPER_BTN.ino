#include <Stepper.h>

#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define BTN1 8
#define BTN2 9

const int stepsPerRevolution = 2048; 

Stepper myStepper(stepsPerRevolution, IN4, IN2, IN3, IN1);

void setup() {
  Serial.begin(9600);
  pinMode(BTN1,INPUT_PULLUP);
  pinMode(BTN2,INPUT_PULLUP);
  myStepper.setSpeed(15); //RPM
}

void loop() {
  if(digitalRead(BTN1) == LOW){
    myStepper.step(32);
  }
  if(digitalRead(BTN2) == LOW){
    myStepper.step(-32);
  }
}


