#define led_green 4 //녹색 LED
#define led_yellow 3 //노란색 LED
#define led_red 2 //빨강색 LED

void setup() {
  pinMode(led_green,OUTPUT);
  pinMode(led_yellow,OUTPUT);
  pinMode(led_red,OUTPUT);
}

void loop() {
  //2초동안 녹색 LED가 켜진다
  digitalWrite(led_green,HIGH);
  digitalWrite(led_yellow,LOW);
  digitalWrite(led_red,LOW);
  delay(2000);
  //2초동안 노란색 LED가 켜진다
  digitalWrite(led_green,LOW);
  digitalWrite(led_yellow,HIGH);
  digitalWrite(led_red,LOW);
  delay(2000);
  //2초동안 빨간색 LED가 켜진다
  digitalWrite(led_green,LOW);
  digitalWrite(led_yellow,LOW);
  digitalWrite(led_red,HIGH);
  delay(2000);
}