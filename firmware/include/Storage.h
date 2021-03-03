#ifndef Storage_h
#define Storage_h

#include <Arduino.h>

class Storage
{
public:
    static void setup();

    static String get(String key);
    static String getOrDefault(String key, String defaultValue);
    static void set(String key, String value);

    static int getInt(String key);
    static int getIntOrDefault(String key, int defaultValue);
    static void setInt(String key, int value);
};

#endif