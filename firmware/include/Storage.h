#ifndef Storage_h
#define Storage_h

#include <Arduino.h>

enum class StorageLocations {
    BL = 1001,
    RED1 = 1002,
    GREEN1 = 1003,
    BLUE1 = 1004,
    RED2 = 1006,
    GREEN2 = 1007,
    BLUE2 = 1008,
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