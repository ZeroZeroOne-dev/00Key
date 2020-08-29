#ifndef KeyMap_h
#define KeyMap_h

#include <Globals.h>

class KeyMap
{
public:
    static int getKey(byte row, byte col);
    static void moveLayer();

private:
    static const int _map[][ROW_COUNT][COL_COUNT];
    static int _currentLayer;
};

#endif