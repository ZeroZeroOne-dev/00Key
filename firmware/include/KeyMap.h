#ifndef KeyMap_h
#define KeyMap_h

#include <Arduino.h>
#include <Globals.h>

class KeyMap
{
public:
    static int getKey(byte row, byte col);

private:
    static const int _map[][ROW_COUNT][COL_COUNT];
};

#endif