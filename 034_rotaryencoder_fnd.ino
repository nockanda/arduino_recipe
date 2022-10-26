#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 6
#define DIO 7
TM1637Display display(CLK, DIO);

#define NOCK_CLK 3
#define NOCK_DT 4
#define NOCK_SW 5

bool pre_sensorA = LOW;

int num = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //나 결과를 PC로 볼꺼야~
  pinMode(NOCK_CLK, INPUT);
  pinMode(NOCK_DT, INPUT);
  pinMode(NOCK_SW, INPUT_PULLUP);
  display.setBrightness(0x0f);
  display.showNumberDec(0, false); //초기값은 0!
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(NOCK_SW) == LOW){
    //풀업방식이다!
    //아무것도 누르지 않았을때 HIGH 누르고있을때 LOW
    num = 0;
    display.showNumberDec(num, false);
  }

  
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
      num++;
    }else{
      //반시계방향으로 회전하고 있구나~
      //Serial.println("반시계방향");
      num--;
    }
    //Serial.println(num);
    display.showNumberDec(num, false);
  }


  pre_sensorA = sensorA;
  delay(1);
}
