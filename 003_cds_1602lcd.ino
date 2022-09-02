#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  lcd.setCursor(0,0); //LCD의 왼쪽 상단으로 커서이동
  lcd.print("CDS Data!"); //원하는 text출력(한글안됨!)
}

void loop() {
  int cds = analogRead(A0); //광센서값 읽기!

  lcd.setCursor(0,1); //LCD 좌표이동
  lcd.print("CDS="); //광센서 값 출력
  lcd.print(cds);
  lcd.print("   ");
  delay(1000);
}