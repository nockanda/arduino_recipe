#include <MQUnifiedsensor.h>
#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0 
#define type "MQ-6"
#define ADC_Bit_Resolution 10
#define RatioMQ6CleanAir 10

MQUnifiedsensor MQ6(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);

  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  lcd.setCursor(0,0); //LCD의 왼쪽 상단으로 커서이동
  lcd.print("GAS SENSOR!"); //원하는 text출력(한글안됨!)
  
  MQ6.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ6.setA(2127.2); MQ6.setB(-2.526); // Configurate the ecuation values to get CH4 concentration
 
  MQ6.init();   
  
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ6.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += MQ6.calibrate(RatioMQ6CleanAir);
    Serial.print(".");
  }
  MQ6.setR0(calcR0/10);
  Serial.println("  done!.");
  
}

void loop() {
  MQ6.update();
  float sensor = MQ6.readSensor();
  Serial.println(sensor);
  lcd.setCursor(0,1); //LCD 좌표이동
  String line = String(sensor) + "PPM";
  while(line.length()<16) line+=" ";
  lcd.print(line);
  if(sensor > 5000){
    tone(13,2000);
  }else{
    noTone(13);
  }
  delay(500);
}