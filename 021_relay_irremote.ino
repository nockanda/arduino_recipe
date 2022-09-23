#include <IRremote.h>

int RECV_PIN = 3; //리모컨 수신기 3번에 연결함
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
  irrecv.enableIRIn(); //리모컨 수신 시작~!
  pinMode(2,OUTPUT); //릴레이가 2번에 연결됨
}

void loop() {
  if (irrecv.decode(&results)) {
    if(results.value == 0xFFA857){
      //인식된 리모컨의 id가 +라면~
      digitalWrite(2,HIGH); //릴레이 작동
    }else if(results.value == 0xFFE01F){
     //인식된 리모컨의 id가 -라면~
      digitalWrite(2,LOW); //릴레이 멈춤
    }
    irrecv.resume(); //다음 코드 인식!
  }
  delay(100);
}

