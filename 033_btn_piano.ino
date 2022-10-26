#define NOTE_C6  1047
#define NOTE_D6  1175
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_G6  1568
#define NOTE_A6  1760
#define NOTE_B6  1976
#define NOTE_C7  2093

#define buzzer 13

byte btns[] = {2,3,4,5,6,7,8,9};
int pitch[] = {NOTE_C6,NOTE_D6,NOTE_E6,NOTE_F6,NOTE_G6,NOTE_A6,NOTE_B6,NOTE_C7};
bool pre_state[] = {1,1,1,1,1,1,1,1};

void setup() {
  Serial.begin(9600);
  for(int i = 0;i<8;i++){
    pinMode(btns[i],INPUT_PULLUP);
  }
}

void loop() {
  for(int i = 0;i<8;i++){
    bool now_state = digitalRead(btns[i]);
    if(now_state == LOW && pre_state[i] == HIGH){
      tone(buzzer,pitch[i]);
    }else if(now_state == HIGH && pre_state[i] == LOW){
      noTone(buzzer);
    }

    pre_state[i] = now_state;
  }
}


