#include "Storage.h"
#include <Arduino.h>
#include <map>
#include <SdFat.h>
#include "OLED.h"

#define SD_CONFIG SdioConfig(FIFO_SDIO)

SdFs sd;

std::map<String, String> _cache;

void readFile()
{
    delay(5000);
    Serial.println("TRYING");
    if (!sd.begin(SD_CONFIG))
    {
        sd.initErrorHalt(&Serial);
        Serial.println("CANT BEGIN");
        return;
    }
    Serial.println("BEGUN");

    auto file = sd.open("00Key.config", FILE_READ);
    if (!file)
    {
        Serial.println("CANT OPEN");
        return;
    }

    while (file.available())
    {
        auto line = file.readStringUntil('\n');
        auto location = line.indexOf('=');
        auto key = line.substring(0, location);
        auto value = line.substring(location, key.length() - 1);

        _cache[key] = value;
    }

    file.close();
}

void writeFile()
{
    auto file = sd.open("00Key.config", FILE_WRITE);
    if (!file)
    {
        return;
    }

    for (auto kv : _cache)
    {
        file.println(kv.first + "=" + kv.second);
    }

    file.close();
}

void Storage::setup()
{
    _cache = {};
    readFile();
};

String Storage::get(String key)
{
    return _cache[key];
}

String Storage::getOrDefault(String key, String defaultValue)
{
    if (_cache.count(key) == 0)
    {
        return defaultValue;
    }

    return _cache[key];
}

void Storage::set(String key, String value)
{
    _cache[key] = value;
    writeFile();
}

int Storage::getInt(String key)
{
    return _cache[key].toInt();
}

int Storage::getIntOrDefault(String key, int defaultValue)
{
    if (_cache.count(key) == 0)
    {
        return defaultValue;
    }

    return _cache[key].toInt();
}

void Storage::setInt(String key, int value)
{
    _cache[key] = String(value);
    writeFile();
}
