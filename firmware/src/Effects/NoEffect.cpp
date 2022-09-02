#include "Effects/NoEffect.h"
#include "OLED.h"

void NoEffect::setup() { }

void NoEffect::loop() { }

void NoEffect::selected() { 
    char r[] = "000";
    char g[] = "000";
    char b[] = "000";

    OLED::setUnderglow(r, g, b);
}