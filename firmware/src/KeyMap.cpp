#include <Arduino.h>
#include "KeyMap.h"
#include "Keyboard.h"

int KeyMap::_map[] = {KEY_LEFT_SHIFT, 'j', 'e', 'f'};

int *KeyMap::getMap()
{
    return KeyMap::_map;
};
