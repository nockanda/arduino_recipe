#include <IRremote.h>

int RECV_PIN = 5; //리모컨 수신기 5번에 연결함
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  irrecv.enableIRIn(); //리모컨 수신 시작~!
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
}
     
void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    if(results.value == 0xFF30CF){
        digitalWrite(2,!digitalRead(2));
    }else if(results.value == 0xFF18E7){
        digitalWrite(3,!digitalRead(3));
    }else if(results.value == 0xFF7A85){
        digitalWrite(4,!digitalRead(4));
    }
    irrecv.resume();
  }
  delay(100);
}

