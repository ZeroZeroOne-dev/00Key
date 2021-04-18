#ifndef Storage_h
#define Storage_h

#include <Arduino.h>

enum class StorageLocations {
    BL = 1001,
    RED = 1002,
    GREEN = 1003,
    BLUE = 1004,
    EFFECT = 1005
};

class Storage
{
public:
    static void setup();

    static int get(StorageLocations location);
    static void set(StorageLocations location, int value);
};

#endif