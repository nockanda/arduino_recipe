#include <MQUnifiedsensor.h>

#define placa "Arduino UNO"
#define Voltage_Resolution 5
#define pin A0 
#define type "MQ-6"
#define ADC_Bit_Resolution 10
#define RatioMQ6CleanAir 10

MQUnifiedsensor MQ6(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
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
  if(sensor > 10000){
    digitalWrite(2,HIGH);
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
  }else if(sensor > 5000){
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