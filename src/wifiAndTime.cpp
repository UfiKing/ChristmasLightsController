#include "wifiAndTime.h"
#include <WiFi.h>
#include <time.h>
#include <ESPAsyncWebServer.h>

/*
class WebHandler{
  char* ssid; // max 33
  char* password; // max 63
  
  char* APssid = "9mDolgaKitaObdanaZLuckami";
  char* APpassword = "Geslo123!";

  const char ntpServer[15] = "ntp2.arnes.si";
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
  
};*/

int WebHandler::configTimeServer(){
  if(WebHandler::isWifiOn == false){
    Serial.println("Not connected to wifi!");
    return 1;
  }
  configTime(WebHandler::GMT_Offset, WebHandler::DaylightSavings_Offset, WebHandler::ntpServer);
  return 0;
}


void WebHandler::getTime(){
    
    if(WebHandler::configTimeServer() == 1){
      return;
    }

    struct tm timeInfo;
    getLocalTime(&timeInfo);
    Serial.print(timeInfo.tm_hour);
    Serial.print("  ");
    Serial.println(timeInfo.tm_min);
  }

void WebHandler::setFileFromVariable(char var[], char path[]){
  File file = LittleFS.open(path, "w");

  Serial.print("File ");
  Serial.print(path);

  if(!file){
    Serial.println(" opened unsuccessfully, aborting any further writing");
    return;
  }
  Serial.println(" opened successfully");

  if(file.print(var)){
    Serial.println("File written successfully");
  }else{
    Serial.println("File written unsuccessfully");
  }

  file.close();

}

void WebHandler::setVariableFromFile(char var[], char path[]){
  File file = LittleFS.open(path, "w");

  Serial.print("File ");
  Serial.print(path);
  if(!file){
    Serial.println(" opened unsuccessfully, aborting any further writing");
    return;
  }
  Serial.println(" opened successfully");
    
  uint8_t i = 0;
  while(file.available()) var[i++] = (char)file.read();
  i = 0;
  while(var[i++] != '\0' || var[i] != 0) var[i] = '\0';
   
  Serial.println("Variable written successfully");
  file.close();
  Serial.println("File closed successfully");
}

void WebHandler::setSSID(char* newSSID){
  WebHandler::ssid = newSSID;
}

void WebHandler::setPassword(char newPassword[]){
  WebHandler::password = newPassword;
}

void WebHandler::setAPssid(char newSSID[]){
  WebHandler::APssid = newSSID;
}

void WebHandler::setAPpassword(char newPassword[]){
  WebHandler::APpassword = newPassword;
}

void WebHandler::setWifiCredentials(){
  WebHandler::setFileFromVariable(ssid, "/ssid.txt" );
  WebHandler::setFileFromVariable(password, "/pass.txt");
}

void WebHandler::getWifiCredentials(){
  WebHandler::setVariableFromFile(ssid, "/ssid.txt");
  WebHandler::setVariableFromFile(password, "pass.txt");
}

void WebHandler::setupWifi(){
  //connect to wifi
  Serial.println("Setting up wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WebHandler::ssid, WebHandler::password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to wifi");

  }
  WebHandler::isWifiOn = true; 
  Serial.println(WiFi.localIP());

}

void WebHandler::setupAP(){
  Serial.println("Setting up AP mode");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WebHandler::APssid, WebHandler::APpassword);
  WebHandler::isWifiOn = false;
  Serial.println(WiFi.softAPIP());
}


