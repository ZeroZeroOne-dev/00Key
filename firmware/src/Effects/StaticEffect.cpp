#include "Effects/StaticEffect.h"
#include "OLED.h"

StaticEffect::StaticEffect(CRGB leds[], int num_leds, StorageLocations redLocation, StorageLocations greenLocation, StorageLocations blueLocation) : BaseEffect(leds, num_leds)                                                                                                                         
{
    _redLocation = redLocation;
    _greenLocation = greenLocation;
    _blueLocation = blueLocation;                                                                                                 
}

void StaticEffect::store()
{
    Storage::set(_redLocation, _red);
    Storage::set(_greenLocation, _green);
    Storage::set(_blueLocation, _blue);
}

void setOled(int red, int green, int blue){
    char redChar[3];
    sprintf(redChar, "%03d", red);

    char greenChar[3];
    sprintf(greenChar, "%03d", green);

    char blueChar[3];
    sprintf(blueChar, "%03d", blue);

    OLED::setUnderglow(redChar, greenChar, blueChar);
}

void StaticEffect::setup()
{
    _red = Storage::get(_redLocation);
    _green = Storage::get(_greenLocation);
    _blue = Storage::get(_blueLocation);
}

void StaticEffect::loop()
{
    for (size_t i = 0; i < _num_leds; i++)
    {
        _leds[i].setRGB(_red, _green, _blue);
    }

    if (_shouldStore && millis() - _storeStart > StoreAfter)
    {
        store();
        _shouldStore = false;
    }
}

void StaticEffect::set(int red, int green, int blue)
{
    _red = red;
    _green = green;
    _blue = blue;
    setOled(_red, _green, _blue);

    _shouldStore = true;
    _storeStart = millis();
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

void StaticEffect::selected()
{
    setOled(_red, _green, _blue);
}