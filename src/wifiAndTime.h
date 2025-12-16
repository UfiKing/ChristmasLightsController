#ifndef WIFI_AND_TIME_H
#define WIFI_AND_TIME_H

#include "LittleFS.h"


class WebHandler{
  
  
  //char* APssid = "9mDolgaKitaObdanaZLuckami";
  

  const char* ntpServer = "ntp1.arnes.si";
  const uint16_t GMT_Offset = 3600;
  const uint16_t DaylightSavings_Offset = 3600;

  bool isWifiOn = false;
  public:
  
  struct tm timeInfo;
  char ssid[33]; // max 33
  char password[63]; // max 63
  char APssid[33] = "luckeee";
  char APpassword[63] = "Geslo123!";
  
  uint8_t hours = 0;
  uint8_t minutes = 0;

  int8_t manuelOverride = -1;

  WebHandler(){
    Serial.begin(9600);
    Serial.println("Starting file sistem!");
    if(LittleFS.begin()){
      Serial.println("filesystem started successfully!");
    }else{
      Serial.println("filesystem didn't start successfully ):");
    }
  }

  int configTimeServer();

  void getTime(); 

  void setFileFromVariable(char var[], char* path, bool first = true); 

  void setVariableFromFile(char var[], char path[]);

  /*void setSSID(char newSSID[]);

  void setPassword(char newPassword[]);

  void setAPssid(char newSSID[]);

  void setAPpassword(char newPassword[]);*/

  void setWifiCredentials();
  
  void getWifiCredentials();

  void setupWifi();  
  
  void setupAP();
  
};

#endif
