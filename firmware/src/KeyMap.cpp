#include <Arduino.h>
#include "KeyMap.h"
#include "Globals.h"

// clang-format off

const int KeyMap::_map[][ROW_COUNT][COL_COUNT] = {
    [0] = {  
        { KEY_LEFT_SHIFT, KEY_J }, 
        { KEY_E, KEY_F }
    } 
};

// clang-format on

int KeyMap::getKey(byte row, byte col)
{
    return KeyMap::_map[0][row][col];
};
