#ifndef TOOLS_H
#define TOOLS_H

#include <WiFi.h>
#include <time.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

String getChipId();
double round2(double value);
int getRssiAsQuality(int rssi);
unsigned long getUnixTime();
void loadFilesToArray(File root, JsonArray list);
JsonDocument createInfoJson(String version, String chipId);

#endif // TOOLS_H
