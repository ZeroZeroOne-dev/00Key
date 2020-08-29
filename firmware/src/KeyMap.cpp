#include <Arduino.h>
#include "KeyMap.h"
#include "Globals.h"

// clang-format off

const int KeyMap::_map[][ROW_COUNT][COL_COUNT] = {
    [0] = {  
        { KEY_00KEY_MOVELAYER, KEY_J }, 
        { KEY_E, KEY_F }
    },
    [1] = {
        { KEY_00KEY_MOVELAYER, KEY_R }, 
        { KEY_Y, KEY_PERIOD }
    }
};

// clang-format on

int KeyMap::_currentLayer = 0;

int KeyMap::getKey(byte row, byte col)
{
    return KeyMap::_map[_currentLayer][row][col];
};

void KeyMap::moveLayer()
{
    int totaLayers = (sizeof(KeyMap::_map) / sizeof(*KeyMap::_map));
    if (_currentLayer < (totaLayers - 1))
    {
        _currentLayer++;
    }
    else
    {
        _currentLayer = 0;
    }
};