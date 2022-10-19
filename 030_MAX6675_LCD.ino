#include "max6675.h"
#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

int thermoDO = 3;
int thermoCS = 4;
int thermoCLK = 5;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  lcd.setCursor(0,0); //LCD의 왼쪽 상단으로 커서이동
  lcd.print("MAX6675 test"); //원하는 text출력(한글안됨!)
  
  Serial.println("MAX6675 test");
  delay(500);
}

void loop() {
   float temp = thermocouple.readCelsius();
   Serial.print("C = "); 
   Serial.println(temp);
   String line = String(temp)+"'C";
   while(line.length()<16) line+= " ";
   lcd.setCursor(0,1);
   lcd.print(line);
   delay(500);
}