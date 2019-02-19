#include <Adafruit_NeoPixel.h>
#define TailPIN D2
#define RWingPIN D1
#define LWingPIN D3
#define FusePIN 7
#define TailLEDcount 9
#define RWingLEDcount 2
#define LWingLEDcount 2
#define FuseLEDcount 7
#define BRIGHTNESS 255
Adafruit_NeoPixel Tail = Adafruit_NeoPixel(TailLEDcount, TailPIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel RWing = Adafruit_NeoPixel(RWingLEDcount, RWingPIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel LWing = Adafruit_NeoPixel(LWingLEDcount, LWingPIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel Fuse = Adafruit_NeoPixel(FuseLEDcount, FusePIN, NEO_GRBW + NEO_KHZ800);

unsigned long NOW=millis();
unsigned long LAST=millis();
unsigned long interval=1000;
unsigned long strobelength=1;
bool flashed=0;
void setup() {
  // put your setup code here, to run once:
  Tail.setBrightness(BRIGHTNESS);
  Tail.begin();
  Tail.show(); // Initialize all pixels to 'off'
  RWing.setBrightness(BRIGHTNESS);
  RWing.begin();
  RWing.show(); // Initialize all pixels to 'off'
  LWing.setBrightness(BRIGHTNESS);
  LWing.begin();
  LWing.show(); // Initialize all pixels to 'off'
  Fuse.setBrightness(BRIGHTNESS);
  Fuse.begin();
  Fuse.show(); // Initialize all pixels to 'off'
  Nav();
}

void loop() {
  // put your main code here, to run repeatedly:
  EVERY_N_SECONDS(1)Strobe();
}


//--------------------------------------
void Strobe(){
  if(!flashed){
    if(NOW-LAST>=interval){
      for(int x=0;x<TailLEDcount;x++){
        Tail.setPixelColor(x,255,255,255,255);
      }
      Tail.show();
      Tail.setBrightness(0);
      Tail.show();
      Tail.setBrightness(BRIGHTNESS);
      LAST=millis();flashed=1;
    }
  }
  else{
    if(NOW-LAST>=interval/6){
      for(int x=0;x<TailLEDcount;x++){
        Tail.setPixelColor(x,255,255,255,255);
      }
      Tail.show();
      Tail.setBrightness(0);
      Tail.show();
      Tail.setBrightness(BRIGHTNESS);
      LAST=millis();flashed=0;
    }
  }
}
//--------------------------------------
void Nav(){
  RWing.setPixelColor(1,255,255,255,255);
  RWing.setPixelColor(0,0,255,0,0);
  LWing.setPixelColor(1,255,255,255,255);
  LWing.setPixelColor(0,255,0,0,0);
  RWing.show();
  LWing.show();
  
}
