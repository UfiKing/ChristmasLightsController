#ifndef WIFI_AND_TIME_H
#define WIFI_AND_TIME_H

#include "LittleFS.h"

void configTime();

void getTime();

void setWifiCredentials(FS &fs);

void getWifiCredentials(FS &fs);

void setupWifi();

void setupAP();
#endif
