#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <time.h>
#include "wifiAndTime.h"
#include "lightsClass.h"


const char* ssidInput = "SSIDInput";
const char* passwordInput = "PASSWORDInput";

const char* APssidInput = "AP_SSIDInput";
const char* APpasswordInput = "AP_PASSWORDInput";

WebHandler WebHandler;

LightsHandler LightsHandler;

AsyncWebServer server(80);

String inputMessage;
String inputParam;

String processor(const String& var){
  return String();
}

void setup(){
  WebHandler.getWifiCredentials();
  if(*WebHandler.ssid == '\n' || *WebHandler.password == '\n'){
    WebHandler.setupAP();
  }else{
    WebHandler.setupWifi();
    WebHandler.configTimeServer();
    WebHandler.getTime();
  }
  Serial.begin(9600);
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/index.html", "",false, processor);
      });
  server.on("/button1", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("buton");
      LightsHandler.state = !LightsHandler.state;
      WebHandler.getTime();
      request->send(LittleFS, "/index.html", "",false, processor);
      });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
      if(request->hasParam(ssidInput)){
        inputMessage = request->getParam(ssidInput)->value();
        strcpy(WebHandler.ssid, inputMessage.c_str());
        WebHandler.setFileFromVariable(WebHandler.ssid, "/ssid.txt");
      }
      else if(request->hasParam(passwordInput)){
        inputMessage = request->getParam(passwordInput)->value();
        strcpy(WebHandler.password, inputMessage.c_str());
        WebHandler.setFileFromVariable(WebHandler.password, "/pass.txt");
      }
      else if(request->hasParam(APssidInput)){
        inputMessage = request->getParam(APssidInput)->value();
        strcpy(WebHandler.APssid, inputMessage.c_str());
        WebHandler.setFileFromVariable(WebHandler.APssid, "/APssid.txt");
      }
      else if(request->hasParam(APpasswordInput)){
        inputMessage = request->getParam(APpasswordInput)->value();
        strcpy(WebHandler.APpassword, inputMessage.c_str());
        WebHandler.setFileFromVariable(WebHandler.APpassword, "/APpass.txt");
      }else if(request->hasParam("BRIGHTNESS_Input")){
        inputMessage = request->getParam("BRIGHTNESS_Input")->value();
        LightsHandler.brightness = inputMessage.toInt();
      }
      request->send(200, "/", "");
      });

  server.on("/wifiSettings", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/wifiSettings.html", "", false, processor);
      });

  server.on("/connectToWifi", HTTP_GET, [](AsyncWebServerRequest *request){
      WebHandler.getWifiCredentials();
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

  server.on("/manuelON", HTTP_GET, [](AsyncWebServerRequest *request){
      WebHandler.manuelOverride = 1;
      LightsHandler.state = true;
      request->send(LittleFS, "/index.html", "", false, processor);
      });

  server.on("/manuelOFF", HTTP_GET, [](AsyncWebServerRequest *request){
      WebHandler.manuelOverride = 0;
      LightsHandler.state = false;
      request->send(LittleFS, "/index.html", "", false, processor);
      });

  server.on("/auto", HTTP_GET, [](AsyncWebServerRequest *request){
      WebHandler.manuelOverride = -1;
      request->send(LittleFS, "/index.html", "", false, processor);
      });

  server.begin(); 
}


void loop(){
  if(LightsHandler.state){
    LightsHandler.rainbowEffect1();
  }else{
    LightsHandler.lightsOff();
  }
  WebHandler.getTime(); 
  delay(10);
  if(330 <= (WebHandler.hours * 60) + WebHandler.minutes && (WebHandler.hours * 60) + WebHandler.minutes <= 450){
    LightsHandler.state = true;
  //}else if( 960 <= (WebHandler.hours * 60) + WebHandler.minutes && (WebHandler.hours * 60) + WebHandler.minutes <= 1320){
  }else if( 960 <= (WebHandler.hours * 60) + WebHandler.minutes && (WebHandler.hours * 60) + WebHandler.minutes <= 1320){
    LightsHandler.state = true;
  }else if (WebHandler.manuelOverride == -1){
    LightsHandler.state = false;
    delay(1000);
  }  
}


