#include <Arduino.h>
#include "KeyMap.h"

char KeyMap::_map[] = {'q', 'w', 'e', 'r'};

char *KeyMap::getMap()
{
    return KeyMap::_map;
};
