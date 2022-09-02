#ifndef StaticEffect_h
#define StaticEffect_h

#include <FastLED.h>
#include "BaseEffect.h"
#include "Storage.h"

enum class RGBColor : int
{
    RED,
    GREEN,
    BLUE
};

class StaticEffect : public BaseEffect
{
private:
    static const int StoreAfter = 3000;
    StorageLocations _redLocation;
    StorageLocations _greenLocation;
    StorageLocations _blueLocation;
    int _red = 0;
    int _green = 0;
    int _blue = 0;
    int _shouldStore = false;
    int _storeStart = 0;

public:
    StaticEffect(CRGB leds[], int num_leds, StorageLocations redLocation, StorageLocations greenLocation, StorageLocations blueLocation);
    void set(int red, int green, int blue);
    void add(int red, int green, int blue);
    void setup();
    void loop();
    void store();
    void selected();
};

#endif