#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

#include <SoftwareSerial.h> //이산화탄소
#include <MHZ19.h> //이산화탄소

//이산화탄소센서 관련
SoftwareSerial ss(2,3);
MHZ19 mhz(&ss);

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  ss.begin(9600); //이산화탄소센서 시작!
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  lcd.setCursor(0,0); //LCD의 왼쪽 상단으로 커서이동
  lcd.print("Co2 Data!"); //원하는 text출력(한글안됨!)
}

void loop() {
  MHZ19_RESULT response = mhz.retrieveData();
  if (response == MHZ19_RESULT_OK)
  {
    int co2 = mhz.getCO2(); //이산화탄소 농도 측정
    lcd.setCursor(0,1); //LCD 좌표이동
    lcd.print("Co2="); //센서 값 출력
    lcd.print(co2);
    lcd.print("PPM   "); //단위 PPM
  }
  else
  {
    lcd.setCursor(0,1); //LCD 좌표이동
    lcd.print("Co2=NO DATA");
  }
  delay(2000);
}