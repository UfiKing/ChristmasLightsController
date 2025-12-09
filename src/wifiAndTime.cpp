#include "wifiAndTime.h"
#include <WiFi.h>
#include <time.h>
#include <ESPAsyncWebServer.h>


class WebHandler(){
  char ssid[33];
  char password[63];

  const char ntpServer = "ntp2.arnes.si";
  const uint16_t GMT_Offset = 3600;
  const uint16_t DaylightSavings_Offset = 3600;


  public:
  
  WebHandler(){
    LittleFS.begin();
  }

  uint8_t configTimeServer(){
    if(isWifiOn == false){
      Serial.println("Not connected to wifi!");
      return 1;
    }
    configTime(GMT_Offset, DaylightSavings_Offset, ntpServer);
    return 0;
  }

  void getTime(){
    
    if(configTimeServer() == 1){
      return;
    }

    struct tm timeInfo;
    getLocalTime(&timeInfo);
    Serial.print(timeInfo.tm_hour);
    Serial.print("  ");
    Serial.println(timeInfo.tm_min);
  }

  void setFileFromVariable(char path[], char var[]){
    File file = LittleFS.open(path, "w");

    if(!file){
      Serial.print("File ");
      Serial.print(path);
      Serial.println(" opened unsuccessfully");
    }
  }

}


void setWifiCredentials(FS &fs, char ssid[], char password[]){
  File file = fs.open("/ssid.txt", "w");

  if(!file){
    Serial.println("ohno not worky (file ssid.txt couldnt be opened)");
    return;
  }
  if(file.print(ssid)){
    Serial.println("file written successfully");
  }else{
    Serial.println("file written unsuccessfully, oopsie doopise");

  }
  file.close();
  delay(100);
  File file2 = fs.open("/pass.txt", "w");
  if(!file2){
    Serial.println("ohno not worky (file pass.txt couldnt be opened)");
    return;
  }
  if(file2.print(password)){
    Serial.println("file written successfully");
  }else{
    Serial.println("file written unsuccessfully, oopsie doopise");

  }
  file2.close();
}

void getWifiCredentials(FS &fs, char ssid[], char password[]){
  File file = fs.open("/ssid.txt");
  if(!file){
    Serial.println("ohno not worky (file ssid.txt couldnt be opened)");
    return;
  }
  //ssid = file.read();
  uint8_t i = 0;
  while(file.available()) ssid[i++] = (char)file.read();
  while(ssid[i++] != '\0' || ssid[i] != 0) ssid[i] = '\0';
  Serial.println(ssid);
  
  file.close();
  File file2 = fs.open("/pass.txt");
  if (!file2){
    Serial.println("ohno not worky (file pass.txt couldnt be opened)");
    return;
  }
  //password = file2.read();
  Serial.println(file2.read());

  file2.close();

}

void setupWifi(char ssid[], char password[]){
  //connect to wifi
  Serial.println("Setting up wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to wifi");

  }
  isWifiOn = true; 
  Serial.println(WiFi.localIP());

}


void setupAP(){
  Serial.println("Setting up AP mode");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(APssid, APpassword);
  isWifiOn = false;
  Serial.println(WiFi.softAPIP());
}









