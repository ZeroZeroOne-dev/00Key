#include "Effects/StaticEffect.h"
#include "OLED.h"

int _red = 0;
int _green = 0;
int _blue = 0;

int shouldStore = false;
int storeStart = 0;
int storeAfter = 3000;

void store()
{
    Storage::set(StorageLocations::RED, _red);
    Storage::set(StorageLocations::GREEN, _green);
    Storage::set(StorageLocations::BLUE, _blue);
}

void StaticEffect::setup()
{
    _red = Storage::get(StorageLocations::RED);
    _green = Storage::get(StorageLocations::GREEN);
    _blue = Storage::get(StorageLocations::BLUE);
    OLED::setUnderglow(_red, _green, _blue);
}

void StaticEffect::loop()
{
    for (size_t i = 0; i < _num_leds; i++)
    {
        _leds[i].setRGB(_red, _green, _blue);
    }

    if(shouldStore && millis() - storeStart > storeAfter)
    {
        store();
        shouldStore = false;
    }
}

void StaticEffect::set(int red, int green, int blue)
{
    _red = red;
    _green = green;
    _blue = blue;
    OLED::setUnderglow(_red, _green, _blue);

    shouldStore = true;
    storeStart = millis();
}

void StaticEffect::add(int red, int green, int blue)
{
    auto newRed = _red + red;
    auto newGreen = _green + green;
    auto newBlue = _blue + blue;

    if (newRed > 255 || newGreen > 255 || newBlue > 255)
    {
        return;
    }

    if (newRed < 0 || newGreen < 0 || newBlue < 0)
    {
        return;
    }

    set(newRed, newGreen, newBlue);
}