#include "DHT.h" //온습도
#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

//온습도관련
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  dht.begin(); //온습도시작
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  lcd.setCursor(0,0); //LCD의 왼쪽 상단으로 커서이동
  lcd.print("DHT11 Data!"); //원하는 text출력(한글안됨!)
}

void loop() {
  delay(2000); //2초 간격으로 측정
  float h = dht.readHumidity(); //습도 측정
  float t = dht.readTemperature(); //온도 측정
  if (isnan(h) || isnan(t)) {
    Serial.println(F("온도측정 실패!"));
    return;
  }

  lcd.setCursor(0,1); //LCD 좌표이동
  lcd.print("T="); //온도 출력
  lcd.print(t);
  lcd.print(" ");

  lcd.setCursor(8,1); //LCD 좌표이동
  lcd.print("H="); //습도 출력
  lcd.print(t);
  lcd.print(" ");
}