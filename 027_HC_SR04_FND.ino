#include <TM1637Display.h> //TM1637
//TM1637
#define CLK 6
#define DIO 7
TM1637Display display(CLK, DIO);

#define trig 2
#define echo 3

void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT); //trig 발사
  pinMode(echo,INPUT); //echo 받기
  display.setBrightness(0x0f); //밝기를 최대로 해라
}
void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(trig);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  int dist = (pulseIn(echo, HIGH)/29.0)/2; //cm
  display.showNumberDec(dist, false); //FND화면에 출력한다!
  delay(100);
}