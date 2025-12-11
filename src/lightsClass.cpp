#include "lightsClass.h"
#include <FastLED.h>

#define LED_PIN 18

void LightsHandler::lightsOff(){
  LightsHandler::state = false;
  for(uint16_t i = 0; i < LightsHandler::numLeds ; i++){
    LightsHandler::leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}

void LightsHandler::lightsOn(){
  LightsHandler::state = true;
  for(uint16_t i = 0; i < LightsHandler::numLeds; i++){
    LightsHandler::leds[i] = CRGB(255,255,255);
  }
  FastLED.show();
}

void LightsHandler::rainbowEffect1(){
  for(uint16_t i = LightsHandler::numLeds - 1; i > 0; i--){
    LightsHandler::leds[i] = LightsHandler::leds[i - 1];
  }
  leds[0] = CHSV(LightsHandler::hue,255,255);
  LightsHandler::hue++;
   
  FastLED.show();
}






