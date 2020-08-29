#include <Arduino.h>
#include "KeyMap.h"
#include "Globals.h"

// clang-format off

const int KeyMap::_map[][ROW_COUNT][COL_COUNT] = {
    [0] = {  
        { KEY_RIGHT_GUI, KEY_SCROLL_LOCK }, 
        { KEY_J, KEY_E }
    },
    [1] = {
        { KEY_RIGHT_GUI, KEY_SCROLL_LOCK }, 
        { KEY_F, KEY_PERIOD }
    }
};

// clang-format on

int KeyMap::getKey(byte row, byte col)
{
    return KeyMap::_map[0][row][col];
};
