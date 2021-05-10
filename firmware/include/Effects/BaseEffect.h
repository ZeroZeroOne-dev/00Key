#ifndef BaseEffect_h
#define BaseEffect_h

#include <FastLED.h>

class BaseEffect
{
protected:
    CRGB *_leds;
    int _num_leds;

public:
    BaseEffect(CRGB leds[], int num_leds) : _leds(leds), _num_leds(num_leds) {}
    virtual void setup() = 0;
    virtual void loop() = 0;
};

#endif