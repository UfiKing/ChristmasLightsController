#include <FastLED.h>
#ifndef LIGHTS_CLASS_H
#define LIGHTS_CLASS_H
#define LED_PIN 18

class LightsHandler{
  uint8_t brightness = 10;
  uint8_t hue = 0;  
  const uint16_t numLeds = 399;
  CRGB leds[399];
  public: 

  bool state = false;
  LightsHandler(){
    FastLED.addLeds<WS2812B, LED_PIN>(leds, numLeds);
    FastLED.setBrightness(brightness);
  }
  
  void lightsOff();

  void lightsOn();

  void rainbowEffect1();

};

#endif
