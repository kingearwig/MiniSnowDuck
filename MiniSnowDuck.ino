#include <Adafruit_NeoPixel.h>
#define TailPIN D2
#define RWingPIN D1
#define LWingPIN D3
#define TailLEDcount 9
#define RWingLEDcount 2
#define LWingLEDcount 2
#define ch5PIN D4
Adafruit_NeoPixel Tail = Adafruit_NeoPixel(TailLEDcount, TailPIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel RWing = Adafruit_NeoPixel(RWingLEDcount, RWingPIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel LWing = Adafruit_NeoPixel(LWingLEDcount, LWingPIN, NEO_GRBW + NEO_KHZ800);

int ch5;
int brightness=255;
unsigned long NOW=millis();
unsigned long LAST=millis();
unsigned long interval=500;
unsigned long strobelength=10;
int strobestate=1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ch5PIN,INPUT);
  RWing.begin();
  LWing.begin();
  Tail.begin();
  LWing.setPixelColor(0,255,255,255,255);
  LWing.setPixelColor(1,0,255,0,0);
  RWing.setPixelColor(0,255,255,255,255);
  RWing.setPixelColor(1,255,0,0,0);
  RWing.setBrightness(brightness);
  RWing.show();
  LWing.setBrightness(brightness);
  LWing.show();
  
  for(int i=0;i<TailLEDcount;i++){
    Tail.setPixelColor(i,0,0,0,0);
  }
  Tail.setBrightness(brightness);
  Tail.show();
}

void loop() {
  // put your main code here, to run repeatedly:
  NOW=millis();
  nav();
  ch5=pulseIn(ch5PIN,HIGH,25000);
  if(ch5>1200){
    brightness=map(ch5,1200,2000,255,0);
    strobe();
  }
  if(ch5<1200){
    brightness=map(ch5,1200,2000,255,0);
    solid();
  }
  Serial.print(ch5);Serial.print(" ");Serial.println(brightness);
}

void disco(){
  
}

void nav(){
  LWing.setPixelColor(0,255,255,255,255);
  LWing.setPixelColor(1,0,255,0,0);
  RWing.setPixelColor(0,255,255,255,255);
  RWing.setPixelColor(1,255,0,0,0);
  RWing.setBrightness(brightness);
  RWing.show();
  LWing.setBrightness(brightness);
  LWing.show();
}

void solid(){
  for(int i=0;i<TailLEDcount;i++){
    Tail.setPixelColor(i,255,255,255,255);
  }
  Tail.setBrightness(brightness);
  Tail.show();
}


void strobe(){
  switch(strobestate){
    case 0:
      if(NOW-LAST>interval){
        LAST=millis();
        strobestate=1;
        for(int i=0;i<TailLEDcount;i++){
          Tail.setPixelColor(i,255,255,255,255);
        }
        Tail.setBrightness(brightness);
        Tail.show();
      }
    break;
    case 1:
      if(NOW-LAST>strobelength){
        LAST=millis();
        strobestate=2;
        for(int i=0;i<TailLEDcount;i++){
          Tail.setPixelColor(i,0,0,0,0);
        }
      Tail.setBrightness(brightness);
      Tail.show();
      }
    break;
    case 2:
      if(NOW-LAST>interval/4){
        LAST=millis();
        strobestate=3;
        for(int i=0;i<TailLEDcount;i++){
          Tail.setPixelColor(i,255,255,255,255);
        }
      Tail.setBrightness(brightness);
      Tail.show();
      }      
    break;
    case 3:
      if(NOW-LAST>strobelength){
        LAST=millis();
        strobestate=0;
        for(int i=0;i<TailLEDcount;i++){
          Tail.setPixelColor(i,0,0,0,0);
        }
      Tail.setBrightness(brightness);
      Tail.show();
      }      
    break;
  }
}
