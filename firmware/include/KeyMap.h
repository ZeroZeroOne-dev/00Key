#ifndef KeyMap_h
#define KeyMap_h

#include <Arduino.h>
#include <Globals.h>

class KeyMap
{
public:
    static int getKey(byte row, byte col);
    static void pressKey(byte row, byte col);
    static void releaseKey(byte row, byte col);

private:
    static const int _map[][ROW_COUNT][COL_COUNT];
};

#endif