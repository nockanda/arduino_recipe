#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  lcd.setCursor(0,0); //LCD의 왼쪽 상단으로 커서이동
  lcd.print("XKC-Y25-V"); //원하는 text출력(한글안됨!)
}

void loop() {
  //수위센서 읽기
  if(digitalRead(2) == LOW){
    lcd.setCursor(0,1); //LCD 좌표이동
    lcd.print("No water..      "); //결과출력
  }else{
    lcd.setCursor(0,1); //LCD 좌표이동
    lcd.print("Water Detected!!"); //결과출력
  }
  delay(1000);
}