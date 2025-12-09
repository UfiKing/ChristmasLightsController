#ifndef WIFI_AND_TIME_H
#define WIFI_AND_TIME_H

#include "LittleFS.h"


class WebHandler{
  char* ssid; // max 33
  char* password; // max 63
  
  char* APssid = "9mDolgaKitaObdanaZLuckami";
  char* APpassword = "Geslo123!";

  const char* ntpServer = "arnes2.ntp.si";
  const uint16_t GMT_Offset = 3600;
  const uint16_t DaylightSavings_Offset = 3600;

  bool isWifiOn = false;
  public:
  
  WebHandler(){
    LittleFS.begin();
  }

  int configTimeServer();

  void getTime(); 

  void setFileFromVariable(char var[], char path[]); 

  void setVariableFromFile(char var[], char path[]);

  void setSSID(char* newSSID);

  void setPassword(char newPassword[]);

  void setAPssid(char newSSID[]);

  void setAPpassword(char newPassword[]);

  void setWifiCredentials();
  
  void getWifiCredentials();

  void setupWifi();  
  
  void setupAP();
  
};

#endif
