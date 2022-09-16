#include <Servo.h> //서보모터 라이브러리(설치안해두됨)

Servo nock_servo; //서보모터
int degree = 0;

void setup() {
  nock_servo.attach(9); //서보모터 9번에 연결함!
  nock_servo.write(degree);
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
}

void loop() {
  if(digitalRead(2) == LOW){
    degree++; //각도증가!
    if(degree > 180) degree = 180; //아무리 증가해도 180을 넘을 순 없음!
    nock_servo.write(degree); //서보모터 작동!
    delay(10); 
  }
  if(digitalRead(3) == LOW){
    degree--; //각도감소!
    if(degree < 0) degree = 0; //아무리 감소해도 0보다 작을 순 없음!
    nock_servo.write(degree); //서보모터 작동!
    delay(10); 
  }
}

