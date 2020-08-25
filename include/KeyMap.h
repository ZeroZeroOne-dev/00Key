#ifndef KeyMap_h
#define KeyMap_h

#include <Arduino.h>

class KeyMap
{
public:
    static char *getMap();

private:
    static char _map[];
};

#endif