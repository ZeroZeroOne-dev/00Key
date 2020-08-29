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

bool statusMap[ROW_COUNT][COL_COUNT] = {{false}};

int KeyMap::getKey(byte row, byte col)
{
    return KeyMap::_map[0][row][col];
};

void KeyMap::pressKey(byte row, byte col)
{
    if (statusMap[row][col] == true)
    {
        return;
    }

    auto key = getKey(row, col);
    statusMap[row][col] = true;
    Keyboard.press(key);
}

void KeyMap::releaseKey(byte row, byte col)
{
    if (statusMap[row][col] == false)
    {
        return;
    }

    auto key = getKey(row, col);
    statusMap[row][col] = false;
    Keyboard.release(key);
}
