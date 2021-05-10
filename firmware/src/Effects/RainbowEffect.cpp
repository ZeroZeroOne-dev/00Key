#include "Effects/RainbowEffect.h"

void RainbowEffect::setup() { }

void RainbowEffect::loop()
{
    fill_rainbow(_leds, _num_leds, millis() / 150, 256 / _num_leds);
}