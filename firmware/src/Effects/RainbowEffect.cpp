#include "Effects/RainbowEffect.h"
#include "OLED.h"

void RainbowEffect::setup() { }

void RainbowEffect::loop()
{
    fill_rainbow(_leds, _num_leds, millis() / 150, 256 / _num_leds);
}

void RainbowEffect::selected() {
    char r[] = "###";
    char g[] = "###";
    char b[] = "###";

    OLED::setUnderglow(r, g, b);
 }