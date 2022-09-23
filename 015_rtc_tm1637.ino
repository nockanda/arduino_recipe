#include <ThreeWire.h>  //RTC
#include <RtcDS1302.h> //RTC
#include <TM1637Display.h> //TM1637

//TM1637
#define CLK1 2
#define DIO1 3
TM1637Display display1(CLK1, DIO1);

//RTC
ThreeWire myWire(7,6,8); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

//시계 가운데 콜론표기
bool dot_sw = false;

void setup() {
  Serial.begin(9600);
  display1.setBrightness(0x0f); //밝기를 최대로 해라
  
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    //RTC모듈을 시작하고 현재 컴퓨터의 시간값을 기록한다!
    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    if (!Rtc.IsDateTimeValid()) 
    {
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

}

void loop() {
  //RTC모듈의 시간값을 가지고 온다!
  RtcDateTime now = Rtc.GetDateTime();
  //시간과 분을 FND모듈에 출력한다!
  if(dot_sw){
    display1.showNumberDecEx(now.Hour()*100+now.Minute(), 0x40, true);
    dot_sw = !dot_sw;
  }else{
    display1.showNumberDecEx(now.Hour()*100+now.Minute(), 0x80, true);
    dot_sw = !dot_sw;
  }
  

  Serial.print("HOUR : ");
  Serial.println(now.Hour());
  Serial.print("Minute : ");
  Serial.println(now.Minute());
  Serial.print("Second : ");
  Serial.println(now.Second());

  delay(1000); //1초간격으로 한다!
}