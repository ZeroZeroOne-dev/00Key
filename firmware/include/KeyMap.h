#ifndef KeyMap_h
#define KeyMap_h

#include <Arduino.h>

class KeyMap
{
public:
    static int *getMap();

private:
    static int _map[];
};

#endif