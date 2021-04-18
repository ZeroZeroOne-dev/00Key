#include "Effects/RainbowEffect.h"

void RainbowEffect::setup() {
    auto a = 3;
}

void RainbowEffect::loop()
{
    fill_rainbow(_leds, _num_leds, millis() / 150, 256 / _num_leds);
}