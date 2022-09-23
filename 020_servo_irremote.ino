#include <Servo.h> //서보모터 라이브러리(설치안해두됨)
#include <IRremote.h>

int RECV_PIN = 2; //리모컨 수신기 2번에 연결함
IRrecv irrecv(RECV_PIN);
decode_results results;

Servo nock_servo; //서보모터
int degree = 0;

void setup() {
  nock_servo.attach(9); //서보모터 9번에 연결함!
  nock_servo.write(degree);
  irrecv.enableIRIn(); //리모컨 수신 시작~!
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    if(results.value == 0xFFA857){
      //인식된 리모컨의 id가 +라면~
      degree+=20; //각도증가!
      if(degree > 180) degree = 180; //아무리 증가해도 180을 넘을 순 없음!
      nock_servo.write(degree); //서보모터 작동!
    }else if(results.value == 0xFFE01F){
      //인식된 리모컨의 id가 -라면~
      degree-=20; //각도감소!
      if(degree < 0) degree = 0; //아무리 감소해도 0보다 작을 순 없음!
      nock_servo.write(degree); //서보모터 작동!
    }
    irrecv.resume();
  }
  delay(100);
}

