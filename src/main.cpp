#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <time.h>
#include "wifiAndTime.h"

const char* ssidInput = "SSIDInput";
const char* passwordInput = "PASSWORDInput";

const char* APssidInput = "AP_SSIDInput";
const char* APpasswordInput = "AP_PASSWORDInput";

bool isWifiOn = false;

WebHandler WebHandler;

AsyncWebServer server(80);

String processor(const String& var){
  return String();
}


void setup(){
  Serial.begin(9600);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/index.html", "",false, processor);
      });
  server.on("/button1", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("buton");
      request->send(LittleFS, "/index.html", "",false, processor);
      });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
      String inputMessage;
      String inputParam;

      if(request->hasParam(ssidInput)){
        inputMessage = request->getParam(ssidInput)->value();
        WebHandler.setSSID((char*)inputMessage.c_str());
      }
      else if(request->hasParam(passwordInput)){
        inputMessage = request->getParam(passwordInput)->value();
        WebHandler.setPassword((char*)inputMessage.c_str());
      }
      else if(request->hasParam(APssidInput)){
        inputMessage = request->getParam(APssidInput)->value();
        WebHandler.setAPssid((char*)inputMessage.c_str());
      }
      else if(request->hasParam(APpasswordInput)){
        inputMessage = request->getParam(APpasswordInput)->value();
        WebHandler.setAPpassword((char*)inputMessage.c_str());
      }
      request->send(200, "/", "");
      });

  server.on("/wifiSettings", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/wifiSettings.html", "", false, processor);
      });

  server.on("/connectToWifi", HTTP_GET, [](AsyncWebServerRequest *request){
      WebHandler.setWifiCredentials();
      WebHandler.setupWifi();
      WebHandler.getTime();
      request->send(LittleFS, "/index.html", "", false, processor);
      });
  
  server.on("/connectToWifiPREFERENCES", HTTP_GET, [](AsyncWebServerRequest *request){
      WebHandler.getWifiCredentials();
      WebHandler.setupWifi();
      request->send(LittleFS, "/index.html", "", false, processor);
      });
  
  server.on("/setupAP", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/setupAP.html", "", false, processor);
      });

  server.on("/startAP", HTTP_GET, [](AsyncWebServerRequest *request){
      WebHandler.setupAP();
      request->send(LittleFS, "/setupAP.html", "", false, processor); 
      });

  server.begin(); 
}


void loop(){

}


