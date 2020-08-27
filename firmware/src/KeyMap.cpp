#include <Arduino.h>
#include "KeyMap.h"
#include "Keyboard.h"
#include "Globals.h"

// clang-format off

const int KeyMap::_map[][ROW_COUNT][COL_COUNT] = {
    [0] = {  
        { KEY_LEFT_SHIFT, 'j'}, 
        {'e', 'f'} \
    } 
};

// clang-format on

int KeyMap::getKey(byte row, byte col)
{
    return KeyMap::_map[0][row][col];
};
