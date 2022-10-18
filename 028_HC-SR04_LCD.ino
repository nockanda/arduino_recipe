#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

#define trig 2
#define echo 3

void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT); //trig 발사
  pinMode(echo,INPUT); //echo 받기
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  lcd.setCursor(0,0); //LCD의 왼쪽 상단으로 커서이동
  lcd.print("HC-SR04"); //원하는 text출력(한글안됨!)
}
void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(trig);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  int dist = (pulseIn(echo, HIGH)/29.0)/2; //cm
  String line = String(dist)+"CM";
  while(line.length()<16) line+= " ";
  lcd.setCursor(0,1);
  lcd.print(line);
  delay(100);
}