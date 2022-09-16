#include <Keypad.h>
#include <Wire.h>  //LCD
#include <LiquidCrystal_I2C.h> //LCD

//LCD관련
LiquidCrystal_I2C lcd(0x27,16,2);

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; 
byte colPins[COLS] = {9, 8, 7, 6}; 
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int computernumber[3];
int randNumber;
int num_count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init(); //LCD시작
  lcd.backlight(); //LCD백라이트 켜기

  //첫번째줄 데이터 제목
  lcd.setCursor(0,0); //LCD 1번째 줄에
  lcd.print("BASEBALL GAME!"); //제목을 출력
  lcd.setCursor(0,1); //LCD 2번째 줄에
  lcd.print("INPUT NUMBERS"); //이걸 출력
  
  randomSeed(analogRead(0));
  set_number();
}
int num = 0; //0~999
int result = 0;
void loop() {
  char customKey = customKeypad.getKey();
  
  if (customKey){
    if(customKey >= '0' && customKey <= '9'){
      //customKey : '0'  
      num = (num*10)+(int)(customKey-'0');
      if(num > 999) num=num%1000;
      //
      //display.showNumberDec(num, false);
      Serial.println(num);
      String line = "";
      if(num < 10) line += "0";
      if(num < 100) line += "0";
      line += String(num);
      while(line.length() < 16) line += " ";
      lcd.setCursor(0,1); //LCD 2번째 줄에
      lcd.print(line); //이걸 출력
    }else if(customKey == '#'){
      int s=0;
      int b=0;
      for(int i = 0;i<3;i++){
        if(computernumber[i] == num /100){
          //i가 0일때 한정해서 1S
          if(i==0) s++;
          else b++;
        }else if(computernumber[i] == (num /10)%10){
          if(i==1) s++;
          else b++;
        }else if(computernumber[i] == num %10){
          if(i==2) s++;
          else b++;
        }
      }
      
      if(s == 3){
        //정답을 맞춘경우
        String line = "HOME RUN!!!";
        while(line.length() < 16) line += " ";
        lcd.setCursor(0,1); //LCD 2번째 줄에
        lcd.print(line);
        set_number();
      }else{
        String line = "[S]=" + String(s) + ", [B]=" + String(b);
        while(line.length() < 16) line += " ";
        lcd.setCursor(0,1); //LCD 2번째 줄에
        lcd.print(line);
      }
      num = 0;
    }
  }
}

void set_number(){
  num_count = 0;
  computernumber[0] = 0;
  computernumber[1] = 0;
  computernumber[2] = 0;
  while(true){
    randNumber = random(0,10); //0~9
    if(num_count == 0){
      //첫번째 숫자
      computernumber[0] = randNumber;
      num_count++;
    }else if(num_count ==1){
      //두번째 숫자
      if(computernumber[0] != randNumber){
        computernumber[1] = randNumber;
        num_count++;
      }
    }else if(num_count ==2){
      if(computernumber[0] != randNumber && computernumber[1] != randNumber){
        computernumber[2] =randNumber;
        break;
      }
    }
  }
  Serial.print("정답=");
  Serial.print(computernumber[0]);
  Serial.print(computernumber[1]);
  Serial.println(computernumber[2]);
}
