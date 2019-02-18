#include <Adafruit_NeoPixel.h>
#define TailPIN D2
#define RWingPIN D1
#define LWingPIN D3
#define TailLEDcount 9
#define RWingLEDcount 2
#define LWingLEDcount 2

Adafruit_NeoPixel Tail = Adafruit_NeoPixel(TailLEDcount, TailPIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel RWing = Adafruit_NeoPixel(RWingLEDcount, RWingPIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel LWing = Adafruit_NeoPixel(LWingLEDcount, LWingPIN, NEO_GRBW + NEO_KHZ800);

int brightness=10;
unsigned long NOW=millis();
unsigned long LAST=millis();
unsigned long interval=1000;
unsigned long strobelength=50;
bool strobestate=1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  RWing.begin();
  LWing.begin();
  Tail.begin();
  RWing.setPixelColor(1,255,255,255,255);
  RWing.setPixelColor(0,0,255,0,0);
  LWing.setPixelColor(1,255,255,255,255);
  LWing.setPixelColor(0,255,0,0,0);
  RWing.setBrightness(brightness);
  RWing.show();
  LWing.setBrightness(brightness);
  LWing.show();
  
  for(int i=0;i<TailLEDcount;i++){
    Tail.setPixelColor(i,255,255,255,255);
  }
  Tail.setBrightness(brightness);
  Tail.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  NOW=millis();
  strobe();
}

void strobe(){
  if(!strobestate){
    if(NOW-LAST>interval){
      LAST=millis();
      strobestate=1;
      for(int i=0;i<TailLEDcount;i++){
        Tail.setPixelColor(i,255,255,255,255);
      }
      Tail.show();
    } 
  }
  if(strobestate){
    if(NOW-LAST>strobelength){
      LAST=millis();
      strobestate=0;
      for(int i=0;i<TailLEDcount;i++){
        Tail.setPixelColor(i,0,0,0,0);
      }
      Tail.show();
    }
  }
  
}
