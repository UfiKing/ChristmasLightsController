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


void LightsHandler::changeBrightness(uint8_t newBrightness){
  this->brightness = newBrightness;
  FastLED.setBrightness(this->brightness);
}

void LightsHandler::specialBlink(){
  FastLED.setBrightness(255);
  for(uint16_t i = 0; i< LightsHandler::numLeds; i++){
    LightsHandler::leds[i] = CRGB(0xFE,0x00,0x80);
  }
  FastLED.show();
  //delay(150);
  delay(1000);
  for(uint16_t i = 0; i< LightsHandler::numLeds; i++){
    LightsHandler::leds[i] = CRGB(0x0,0x0,0x0);
  }
  FastLED.show();
  delay(1000); 
}

void LightsHandler::resetBrightness(){
  FastLED.setBrightness(LightsHandler::brightness);
}

