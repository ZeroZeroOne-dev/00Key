#ifndef NoEffect_h
#define NoEffect_h

#include <FastLED.h>
#include "BaseEffect.h"

class NoEffect : public BaseEffect
{
public:
    NoEffect(CRGB leds[], int num_leds) : BaseEffect(leds, num_leds) {}
    void setup();
    void loop();
};

#endif