#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(2,INPUT_PULLUP); //도어센서
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  //첫번째줄 데이터 제목
  lcd.setCursor(0,0); //LCD 1번째 줄에
  lcd.print("Door Sensor!"); //제목을 출력
}

void loop() {
  if(digitalRead(2) == LOW){
    //문이 닫혔다고 감지되었다면~
    lcd.setCursor(0,1); //LCD 2번째 줄에
    lcd.print("Door CLOSED!"); //이걸 출력
  }else{
    //문이 열렸다고 감지되었다면~
    lcd.setCursor(0,1); //LCD 2번째 줄에
    lcd.print("Door OPENED!"); //이걸 출력
  }
  delay(500);
}