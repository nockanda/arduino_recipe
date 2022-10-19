#include "max6675.h"
#include <Arduino.h>
#include <TM1637Display.h>

#define CLK 6
#define DIO 7

TM1637Display display(CLK, DIO);

int thermoDO = 3;
int thermoCS = 4;
int thermoCLK = 5;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);
  display.setBrightness(0x0f);
  display.showNumberDec(0, false);
  
  Serial.println("MAX6675 test");
  delay(500);
}

void loop() {
   float temp = thermocouple.readCelsius();
   Serial.print("C = "); 
   Serial.println(temp);
   display.showNumberDec(temp, false);
   delay(500);
}