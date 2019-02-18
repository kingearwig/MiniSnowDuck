#include <Adafruit_NeoPixel.h>
#define TailPIN D2
#define RWingPIN D1
#define LWingPIN D3
#define TailLEDcount 9
#define RWingLEDcount 2
#define LWingLEDcount 2
int brightness=255;
Adafruit_NeoPixel Tail = Adafruit_NeoPixel(TailLEDcount,TailPIN,NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel RWing = Adafruit_NeoPixel(RWingLEDcount,RWingPIN,NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel LWing = Adafruit_NeoPixel(LWingLEDcount,LWingPIN,NEO_GRBW + NEO_KHZ800);
unsigned long StrobeLength=300;
unsigned long StrobeSpeed=1000;
unsigned long lasttime=millis();
bool TailState=0;
void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<TailLEDcount;i++){
    Tail.setPixelColor(i,0,0,0,255);
  }
  LWing.setPixelColor(0,255,255,255,255);
  LWing.setPixelColor(1,0,255,0,0);
  LWing.show();
  RWing.setPixelColor(0,255,255,255,255);
  RWing.setPixelColor(1,255,0,0,0);
  RWing.show();
  
  Tail.setBrightness(brightness);
  Tail.begin();
  Tail.show();
  TailState=1;
  RWing.setBrightness(brightness);
  RWing.begin();
  RWing.show();
  LWing.setBrightness(brightness);
  LWing.begin();
  LWing.show();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  nav();
  strobe();
  //Serial.println(millis()-lasttime);
  Serial.println(TailState);
}

void nav(){
  LWing.setPixelColor(0,255,255,255,255);
  LWing.setPixelColor(1,0,255,0,0);
  LWing.show();
  RWing.setPixelColor(0,255,255,255,255);
  RWing.setPixelColor(1,255,0,0,0);
  RWing.show();
}
void strobe(){
  unsigned long currentmillis=millis();
  if(TailState=0 && currentmillis-lasttime>StrobeSpeed){
    Tail.setBrightness(brightness);
    Tail.show();
    lasttime=millis();
    TailState=1;
    
  }
  if(TailState=1 && currentmillis-lasttime>StrobeLength){
    Tail.setBrightness(0);
    Tail.show();
    lasttime=millis();
    TailState=0;
  }
}

