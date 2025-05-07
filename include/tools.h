#ifndef TOOLS_H
#define TOOLS_H

#include <WiFi.h>
#include <time.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

namespace coding_lemur
{
    class Tools
    {
    public:
        static String getChipId();
        static double round2(double value);
        static int getRssiAsQuality(int rssi);
        static unsigned long getUnixTime();
        static void loadFilesToArray(File root, JsonArray list);
        static JsonDocument createInfoJson(String version, String chipId);

    private:
        Tools() = delete; // disallow constructor
    };
}

#endif // TOOLS_H
