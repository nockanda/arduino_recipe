#include <Servo.h> //서보모터 라이브러리(설치안해두됨)

Servo nock_servo; //서보모터

void setup() {
  nock_servo.attach(9); //서보모터 9번에 연결함!
}

void loop() {
  int data = analogRead(A0); //가변저항값을 읽음!
  nock_servo.write(map(data,0,1023,0,180)); //각도로 변환!
  delay(15); 
}