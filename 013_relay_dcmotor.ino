void setup() {
  //릴레이가 연결된 2번핀을 출력으로 설정한다
  pinMode(2, OUTPUT);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
}

void loop() {
  if(digitalRead(3) == LOW){
    //풀업방식이기 때문에~ 이게 버튼이 눌려진경우!
    digitalWrite(2,HIGH); //릴레이를 켜겠습니다!
  }
  if(digitalRead(4) == LOW){
    digitalWrite(2,LOW); //릴레이를 끄겠습니다!
  }
}

