#ifndef RainbowEffect_h
#define RainbowEffect_h

#include <FastLED.h>
#include "BaseEffect.h"

class RainbowEffect : public BaseEffect
{
public:
    RainbowEffect(CRGB leds[], int num_leds) : BaseEffect(leds, num_leds) {}
    void setup();
    void loop();
};

#endif