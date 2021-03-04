#include "Storage.h"
#include <Arduino.h>
#include <map>
#include <EEPROM.h>
#include "OLED.h"

int eeCacheAddress = 0;

int Storage::get(StorageLocations location)
{
    return EEPROM.read(static_cast<int>(location));
}

void Storage::set(StorageLocations location, int value)
{
    EEPROM.update(static_cast<int>(location), value);
}