#include <MQUnifiedsensor.h>
#define         Board                   ("Arduino UNO")
#define         Pin                     (A0)  //Analog input 3 of your arduino
#define         Type                    ("MQ-3") //MQ3
#define         Voltage_Resolution      (5)
#define         ADC_Bit_Resolution      (10) // For arduino UNO/MEGA/NANO
#define         RatioMQ3CleanAir        (60) //RS / R0 = 60 ppm 

MQUnifiedsensor MQ3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin, Type);

void setup() {
  Serial.begin(9600); //Init serial port
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  
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
  if(sensor > 0.05){
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
  }else if(sensor > 0.03){
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
  }else{
    digitalWrite(2,LOW);
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
  }
  delay(500);
}