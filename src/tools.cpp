#include "tools.h"

namespace coding_lemur
{
    String Tools::getChipId()
    {
        uint64_t chipId = ESP.getEfuseMac(); // 64-Bit MAC-Adresse
        String chipIdStr = String((uint32_t)(chipId >> 32), HEX) + String((uint32_t)chipId, HEX);
        return chipIdStr;
    }

    double Tools::round2(double value)
    {
        return (int)(value * 100 + 0.5) / 100.0;
    }

    int Tools::getRssiAsQuality(int rssi)
    {
        int quality = 0;

        if (rssi <= -100)
            quality = 0;
        else if (rssi >= -50)
            quality = 100;
        else
            quality = 2 * (rssi + 100);

        return quality;
    }

    unsigned long Tools::getUnixTime()
    {
        time_t now;
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo))
            return 0;

        time(&now);
        return now; // unix time
    }

    void Tools::loadFilesToArray(File root, JsonArray list)
    {
        File file = root.openNextFile();

        while (file)
        {
            list.add(file.name());
            file = root.openNextFile();
        }
    }

    JsonDocument Tools::createInfoJson(String version, String chipId)
    {
        JsonDocument doc;
        doc["version"] = version;

        // system
        JsonObject system = doc["system"].to<JsonObject>();
        system["deviceId"] = chipId;
        system["uptime"] = esp_timer_get_time() / 1000 / 1000; // in seconds
        system["time"] = getUnixTime();
        system["freeHeap"] = ESP.getFreeHeap();
        system["cpuFreq"] = ESP.getCpuFreqMHz();
        system["flashSize"] = ESP.getFlashChipSize();
        system["flashSpeed"] = ESP.getFlashChipSpeed();
        system["flashMode"] = ESP.getFlashChipMode();
        system["sdkVersion"] = ESP.getSdkVersion();
        system["chipModel"] = ESP.getChipModel();
        system["chipCores"] = ESP.getChipCores();
        system["freePsram"] = ESP.getFreePsram();
        system["temperature"] = (temperatureRead() - 32) / 1.8; // convert from Fahrenheit to Celsius

        // filesystem
        JsonObject fileSystemPart = doc["fileSystem"].to<JsonObject>();
        fileSystemPart["totalBytes"] = LittleFS.totalBytes();
        fileSystemPart["usedBytes"] = LittleFS.usedBytes();

        // network
        JsonObject network = doc["network"].to<JsonObject>();
        const int8_t rssi = WiFi.RSSI();
        network["wifiRssi"] = rssi;
        network["wifiQuality"] = getRssiAsQuality(rssi);
        network["wifiSsid"] = WiFi.SSID();
        network["ip"] = WiFi.localIP().toString();
        network["mac"] = WiFi.macAddress();

        return doc;
    }
}
