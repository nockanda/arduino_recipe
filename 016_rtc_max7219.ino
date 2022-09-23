#include <ThreeWire.h>  //RTC
#include <RtcDS1302.h> //RTC
#include "LedControl.h" //도트매트릭스

//도트매트릭스
LedControl lc=LedControl(12,11,10,4);//DIN,CLK,CS,디바이스갯수

//RTC
ThreeWire myWire(3,2,4); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

//도트매트릭스에 출력할 숫자 폰트
byte nockanda_number[10][8]=
{
{0x00, 0x00, 0x3e, 0x41, 0x41, 0x3e, 0x00, 0x00},
{0x00, 0x00, 0x00, 0x01, 0x7f, 0x00, 0x00, 0x00},
{0x00, 0x00, 0x79, 0x49, 0x49, 0x4f, 0x00, 0x00},
{0x00, 0x00, 0x49, 0x49, 0x49, 0x7f, 0x00, 0x00},
{0x00, 0x00, 0x1f, 0x10, 0x7e, 0x10, 0x00, 0x00},
{0x00, 0x00, 0x4f, 0x49, 0x49, 0x79, 0x00, 0x00},
{0x00, 0x00, 0x7f, 0x49, 0x48, 0x78, 0x00, 0x00},
{0x00, 0x00, 0x03, 0x01, 0x01, 0x7f, 0x00, 0x00},
{0x00, 0x00, 0x7f, 0x49, 0x49, 0x7f, 0x00, 0x00},
{0x00, 0x00, 0x0f, 0x09, 0x49, 0x7f, 0x00, 0x00}
};

//시와 분사이에 콜론기호관련
bool mydot = false;

void setup() {
  Serial.begin(9600);

    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    //RTC모듈에 현재 컴퓨터 시간을 저장한다
    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

    if (!Rtc.IsDateTimeValid()) 
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }

  //도트매트릭스를 초기화한다!
  for(int i = 0;i<lc.getDeviceCount();i++){
    lc.shutdown(i,false);
    lc.setIntensity(i,8);
    lc.clearDisplay(i);
  }
}

void loop() {
  //현재시간을 가지고 온다!
  RtcDateTime now = Rtc.GetDateTime();

  //도트매트릭스에 시와 분을 표기한다!
  if(mydot){
    disp_dot(now.Hour()*100+now.Minute(),mydot);
    mydot = !mydot;
  }else{
    disp_dot(now.Hour()*100+now.Minute(),mydot);
    mydot = !mydot;
  }
  
   delay(1000); //1초간격으로 한다!
}


//도트매트릭스에 숫자폰트를 출력하는 함수!
void disp_dot(int temp, bool dot){
  //첫번째자리
  for(int j=0;j<8;j++){
      lc.setColumn(0,j,nockanda_number[temp/1000][7-j]);
  }
  //두번째자리
  for(int j=0;j<8;j++){
    lc.setColumn(1,j,nockanda_number[(temp%1000)/100][7-j]);
  }
  //세번째자리
  for(int j=0;j<8;j++){
    lc.setColumn(2,j,nockanda_number[(temp%100)/10][7-j]);
  }
  //네번째자리
  for(int j=0;j<8;j++){
    lc.setColumn(3,j,nockanda_number[temp%10][7-j]);
  }

  //콜론
  lc.setLed(2,1,0,dot);
  lc.setLed(2,2,0,dot);
  lc.setLed(2,5,0,dot);
  lc.setLed(2,6,0,dot);
}
