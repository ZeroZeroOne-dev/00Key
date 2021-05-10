#ifndef StaticEffect_h
#define StaticEffect_h

#include <FastLED.h>
#include "BaseEffect.h"
#include "Storage.h"

enum class RGBColor: int
{
    RED,
    GREEN,
    BLUE
};

class StaticEffect : public BaseEffect
{
public:
    static void set(int red, int green, int blue);
    static void add(int red, int green, int blue);
    StaticEffect(CRGB leds[], int num_leds) : BaseEffect(leds, num_leds) {}
    void setup();
    void loop();
};

#endif