#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

#include "PMS.h" //미세먼지
#include <SoftwareSerial.h> //미세먼지

//미세먼지센서 관련
SoftwareSerial nockanda(2,3); //tx=2, rx=3
PMS pms(nockanda);
PMS::DATA data;

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  Serial.begin(9600);   //PC-아두이노간
  nockanda.begin(9600);  //미세먼지-아두이노간
  pms.passiveMode();    // 패시브모드

  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  //첫번째줄 데이터 제목
  lcd.setCursor(0,0);
  lcd.print("P1.0");
  lcd.setCursor(5,0);
  lcd.print("P2.5");
  lcd.setCursor(10,0);
  lcd.print("P10.0");
}

void loop()
{
  pms.requestRead();

  if (pms.readUntil(data))
  {
    //두번째줄 값 출력
    lcd.setCursor(0,1);
    lcd.print(data.PM_AE_UG_1_0); //미세먼지 PM1.0(먼지크기)
    lcd.setCursor(5,1);
    lcd.print(data.PM_AE_UG_2_5); //미세먼지 PM2.5(먼지크기)
    lcd.setCursor(10,1);
    lcd.print(data.PM_AE_UG_10_0); //미세먼지 PM10.0(먼지크기)
  }
  else
  {
    lcd.print("NO DATA");
  }

  delay(2000);
}