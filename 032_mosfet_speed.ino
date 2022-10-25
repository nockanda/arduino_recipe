#define mosfet 3

void setup() {
  Serial.begin(9600);
}

void loop() {
  int power = analogRead(A0);
  analogWrite(mosfet,map(power,0,1023,0,255));
  delay(100);
}


