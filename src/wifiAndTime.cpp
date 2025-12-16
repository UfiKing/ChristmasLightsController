#include "wifiAndTime.h"
#include <WiFi.h>
#include <time.h>
#include <ESPAsyncWebServer.h>

int WebHandler::configTimeServer(){
  if(WebHandler::isWifiOn == false){
    Serial.println("Not connected to wifi!");
    return 1;
  }
  Serial.println("Connected to wifi!");
  Serial.print("GMT_Offset: ");
  Serial.println(WebHandler::GMT_Offset);
  Serial.print("DaylightSavings_Offset: ");
  Serial.println(WebHandler::DaylightSavings_Offset);
  Serial.print("ntp server: ");
  Serial.println(WebHandler::ntpServer);
  configTime(WebHandler::GMT_Offset, WebHandler::DaylightSavings_Offset, WebHandler::ntpServer);
  WebHandler::isWifiOn = true;
  return 0;
}


void WebHandler::getTime(){
  //configTime(WebHandler::GMT_Offset, WebHandler::DaylightSavings_Offset, WebHandler::ntpServer);
  /*if(WebHandler::configTimeServer() == 1){
    return;
  }*/
  if(!WebHandler::isWifiOn) return;
  getLocalTime(&timeInfo);
  //Serial.print(timeInfo.tm_hour);
  WebHandler::hours = timeInfo.tm_hour;
  //Serial.print("  ");
  //Serial.println(timeInfo.tm_min);
  WebHandler::minutes = timeInfo.tm_min;
}

void WebHandler::setFileFromVariable(char var[], char* path, bool first){
  File file = LittleFS.open(path, "w");

  Serial.print("File ");
  Serial.print(path);

  if(!file){
    Serial.println(" opened unsuccessfully, aborting any further writing");
    return;
  }
  Serial.println(" opened successfully");
  
  if(file.print(var)){
    Serial.print(var);
    Serial.println(" written successfully");
  }else{
    Serial.print(var);
    Serial.println(" written unsuccessfully");
    if(first){
      file.close();
      this->setFileFromVariable(var,path,false);
    } 
  }
  Serial.println(file.read());
  file.close();

}

void WebHandler::setVariableFromFile(char var[], char path[]){
  File file = LittleFS.open(path);

  Serial.print("File ");
  Serial.print(path);
  if(!file){
    Serial.println(" opened unsuccessfully, aborting any further writing");
    return;
  }
  Serial.println(" opened successfully");
    
  uint8_t i = 0;
  //while(file.available()) var[i++] = (char)file.read();
  
  while(file.available()){ 
    var[i] = file.read();
    Serial.print((int)var[i]);
    Serial.print(" ");
    Serial.println((char)var[i]);
    i++;
  }
  i = 0;
  //while(var[i++] != '\0' || var[i] != 0) var[i] = '\0';
   
  Serial.println("Variable written successfully");
  file.close();
  Serial.println("File closed successfully");
}

void WebHandler::setWifiCredentials(){
  Serial.println("setting the wifi credentials");
  Serial.println(WebHandler::ssid);
  WebHandler::setFileFromVariable(WebHandler::ssid, "/ssid.txt" );
  WebHandler::setFileFromVariable(WebHandler::password, "/pass.txt");
}

void WebHandler::getWifiCredentials(){
  WebHandler::setVariableFromFile(WebHandler::ssid, "/ssid.txt");
  WebHandler::setVariableFromFile(WebHandler::password, "/pass.txt");
}

void WebHandler::setupWifi(){
  //connect to wifi
  Serial.println("Setting up wifi");
  Serial.println(WebHandler::ssid);
  Serial.println(WebHandler::password);
  WebHandler::getWifiCredentials();
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
  WebHandler::setVariableFromFile(WebHandler::APssid, "/APssid.txt");
  WebHandler::setVariableFromFile(WebHandler::APpassword, "/APpass.txt");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WebHandler::APssid, WebHandler::APpassword);
  WebHandler::isWifiOn = false;
  Serial.println(WiFi.softAPIP());
}


