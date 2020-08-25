#include <Arduino.h>
#include "KeyMap.h"

char *KeyMap::getMap()
{
    return KeyMap::_map;
};

char KeyMap::_map[] = {'q', 'w', 'e', 'r'};
