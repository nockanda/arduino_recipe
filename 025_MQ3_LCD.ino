#include <MQUnifiedsensor.h>
#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD
#define         Board                   ("Arduino UNO")
#define         Pin                     (A0)  //Analog input 3 of your arduino
#define         Type                    ("MQ-3") //MQ3
#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
#define         RatioMQ3CleanAir        (60) //RS / R0 = 60 ppm 

MQUnifiedsensor MQ3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600); //Init serial port
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  lcd.setCursor(0,0); //LCD의 왼쪽 상단으로 커서이동
  lcd.print("MQ3 SENSOR!"); //원하는 text출력(한글안됨!)
  
  MQ3.setRegressionMethod(1);
  MQ3.setA(4.8387); MQ3.setB(-2.68);
  MQ3.init(); 
  
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ3.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += MQ3.calibrate(RatioMQ3CleanAir);
    Serial.print(".");
  }
  MQ3.setR0(calcR0/10);
  Serial.println("  done!.");
}

void loop() {
  MQ3.update();
  float sensor = MQ3.readSensor()*10;
  Serial.println(sensor,6);
  lcd.setCursor(0,1); //LCD 좌표이동
  String line = String(sensor,4) + "PPM";
  while(line.length()<16) line+=" ";
  lcd.print(line);
  if(sensor > 0.03){
    tone(13,2000);
  }else{
    noTone(13);
  }
  delay(500);
}