#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

//카운트 변수
int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT); //적외선근접센서
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  //첫번째줄 데이터 제목
  lcd.setCursor(0,0); //LCD 1번째 줄에
  lcd.print("MY COUNTER!"); //제목을 출력
  lcd.setCursor(0,1); //LCD 2번째 줄에
  lcd.print(count); //이걸 출력
}

void loop() {
  if(digitalRead(2) == LOW){
    count++;
    lcd.setCursor(0,1); //LCD 2번째 줄에
    lcd.print(count); //이걸 출력
    delay(100);
  }
}
