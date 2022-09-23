#include <TM1637Display.h> //TM1637
#include <BH1750.h> //BH1750
#include <Wire.h> //BH1750

//BH1750
BH1750 lightMeter;

//TM1637
#define CLK 6
#define DIO 7
TM1637Display display(CLK, DIO);


void setup() {
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  display.setBrightness(0x0f); //밝기를 최대로 해라
}

void loop() {
  float lux = lightMeter.readLightLevel(); //조도센서의 값을 읽는다!
  display.showNumberDec(lux, false); //FND화면에 출력한다!
  delay(1000); //1초간격으로 한다!
}