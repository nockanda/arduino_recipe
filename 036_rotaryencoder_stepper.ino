#include <Stepper.h>

#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define NOCK_CLK 11
#define NOCK_DT 12
#define NOCK_SW 13

const int stepsPerRevolution = 2048; 

Stepper myStepper(stepsPerRevolution, IN4, IN2, IN3, IN1);


bool pre_sensorA = LOW;


void setup() {
  Serial.begin(9600); //나 결과를 PC로 볼꺼야~
  pinMode(NOCK_CLK, INPUT);
  pinMode(NOCK_DT, INPUT);
  pinMode(NOCK_SW, INPUT_PULLUP);
myStepper.setSpeed(15); //RPM
}

void loop() {
  //1.지금 센서값을 확인해야하는 타이밍인가?
  //(=CLK핀에 상승에지가 발생했는가?)
  bool sensorA = digitalRead(NOCK_CLK);
  //여기서 할거하고~~
  if(pre_sensorA == HIGH && sensorA == LOW){
    //센서A의 Falling edge!
    //2.센서B의 상태를 가지고 와서 비교를 해본다!
    bool sensorB = digitalRead(NOCK_DT);
    if(sensorA != sensorB){
      //시계방향으로 회전하고 있구나~
      //Serial.println("시계방향");
      myStepper.step(32);
    }else{
      //반시계방향으로 회전하고 있구나~
      //Serial.println("반시계방향");
      myStepper.step(-32);
    }
    //Serial.println(num);
  }


  pre_sensorA = sensorA;
  delay(1);
}
