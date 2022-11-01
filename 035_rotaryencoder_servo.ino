#include <Servo.h>

#define NOCK_CLK 3
#define NOCK_DT 4
#define NOCK_SW 5


Servo myservo;

bool pre_sensorA = LOW;

int num = 0;

void setup() {
  Serial.begin(9600); //나 결과를 PC로 볼꺼야~
  pinMode(NOCK_CLK, INPUT);
  pinMode(NOCK_DT, INPUT);
  pinMode(NOCK_SW, INPUT_PULLUP);
  myservo.attach(9);
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
      num+=5;
      if(num>180) num=180;
    }else{
      //반시계방향으로 회전하고 있구나~
      //Serial.println("반시계방향");
      num-=5;
      if(num<0) num=0;
    }
    Serial.println(num);
    myservo.write(num);
    delay(20);
  }


  pre_sensorA = sensorA;
  delay(1);
}
