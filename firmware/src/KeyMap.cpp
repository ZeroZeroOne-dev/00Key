#include <Arduino.h>
#include "KeyMap.h"
#include "Keyboard.h"

// clang-format off

int KeyMap::_map[] = {
    KEY_LEFT_SHIFT, 'j', 
    'e', 'f'
};

// clang-format on

int *KeyMap::getMap()
{
    return KeyMap::_map;
};
