#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

//충격이 감지된 횟수를 측정하시오!
#define binary_sensor 2 //센서가 연결된 핀번호

int mycount = 0; //충격이 감지된 횟수

void setup() {
  // put your setup code here, to run once:
  pinMode(binary_sensor,INPUT); //바이너리센서기 때문에 입력으로 설정한다!
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  //첫번째줄 데이터 제목
  lcd.setCursor(0,0); //LCD 1번째 줄에
  lcd.print("MY COUNTER!"); //제목을 출력
  lcd.setCursor(0,1); //LCD 2번째 줄에
  lcd.print(mycount); //이걸 출력
}

void loop() {
  //충격이 감지 되었냐?
  if(digitalRead(binary_sensor) == HIGH){
    //충격이 감지가 된 상황!
    mycount++; //카운트 올림!
    lcd.setCursor(0,1); //LCD 2번째 줄에
    lcd.print(mycount); //이걸 출력
    delay(1+000); //소량의 딜레이로 불필요한 떨림을 방지하겠다!
  }
}

