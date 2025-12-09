#include "lightsClass.h"
#include <FastLED.h>
#define LED_PIN 18
#define NUM_LEDS 399

class LightsHandler{
  CRGB leds[NUM_LEDS];
  uint8_t brightness = 10;
  uint8_t hue = 0;

  public: 
    LightsHandler(){
      FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS);
      FastLED.setBrightness(brightness);
    }

    void lightsOff(){
      for(uint16_t i = 0; i<NUM_LEDS; i++){
        leds[i] = CRGB(0,0,0);
      }
      FastLED.show();
    }

    void lightsOn(){
      for(uint16_t i = 0; i<NUM_LEDS; i++){
        leds[i] = CRGB(255,255,255);
      }
      FastLED.show();
    }

    void rainbowEffect1(){
      for(uint16_t i = NUM_LEDS - 1; i > 0; i--){
        leds[i] = leds[i - 1];
      }
      leds[0] = CHSV(hue,255,255);
      hue++;
      
      FastLED.show();
    }


};


