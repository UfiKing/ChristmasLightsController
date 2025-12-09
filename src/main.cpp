#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <time.h>

const char* ntpServer = "pool.ntp.org";
const uint16_t timezoneOffset = 3600;


char ssid[33]; 
char password[64];

char APssid[33] = "ESP32";
char APpassword[64] = "VerySecurePassword";

const char* ssidInput = "SSIDInput";
const char* passwordInput = "PASSWORDInput";

const char* APssidInput = "AP_SSIDInput";
const char* APpasswordInput = "AP_PASSWORDInput";

bool isWifiOn = false;

AsyncWebServer server(80);

String processor(const String& var){
  return String();
}


void setup(){
  Serial.begin(9600);
  //setup filesystem
  if(!LittleFS.begin()){
    Serial.println("Neki se je zjebal. Kaj pa? idfk");
    return;
  }
  File file = LittleFS.open("/ssid.txt");
  if(file.read() == -1){
    setupAP();
  }else{
    getWifiCredentials(LittleFS);
    setupWifi();
  }
  //setupAP();

  //do some black magic fuckery
  
  //specify kje najde /
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/index.html", "",false, processor);
      });
  server.on("/button1", HTTP_GET, [](AsyncWebServerRequest *request){
      Serial.println("buton");
      setupWifi();
      request->send(LittleFS, "/index.html", "",false, processor);
      });

  server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
      String inputMessage;
      String inputParam;

      if(request->hasParam(ssidInput)){
      //gets the input
        inputMessage = request->getParam(ssidInput)->value();
       
        Serial.println(inputMessage);
      //copies it into ssid variable
        strcpy(ssid, inputMessage.c_str());
      }
      else if(request->hasParam(passwordInput)){

        //gets the input
        inputMessage = request->getParam(passwordInput)->value();
        Serial.println(inputMessage);

        strcpy(password, inputMessage.c_str());

      }
      else if(request->hasParam(APssidInput)){
        //gets the input
        inputMessage = request->getParam(APssidInput)->value();
       
        Serial.println(inputMessage);

        strcpy(APssid, inputMessage.c_str());
      }
      else if(request->hasParam(APpasswordInput)){
        //gets the input
        inputMessage = request->getParam(APpasswordInput)->value();
        Serial.println(inputMessage);

        strcpy(APpassword, inputMessage.c_str());

      }
      request->send(200, "/", "LKASDLKJALSKDJLKASJLKAJS");
      });

  server.on("/wifiSettings", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/wifiSettings.html", "", false, processor);
      });

  server.on("/connectToWifi", HTTP_GET, [](AsyncWebServerRequest *request){
      setWifiCredentials(LittleFS);
      setupWifi();
      getTime();
      request->send(LittleFS, "/index.html", "", false, processor);
      });
  
  server.on("/connectToWifiPREFERENCES", HTTP_GET, [](AsyncWebServerRequest *request){
      getWifiCredentials(LittleFS);
      setupWifi();
      request->send(LittleFS, "/index.html", "", false, processor);
      });
  
  server.on("/setupAP", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/setupAP.html", "", false, processor);
      });

  server.on("/startAP", HTTP_GET, [](AsyncWebServerRequest *request){
      setupAP();
      request->send(LittleFS, "/setupAP.html", "", false, processor); 
      });


  server.begin(); 
}


void loop(){

}


