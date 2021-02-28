#include <WS2812Serial.h>
#define USE_WS2812SERIAL

#include <FastLED.h>
#include "Underglow.h"

#define DATA_PIN 35
#define NUM_LEDS 16
#define COLOR_ORDER BRG     

CRGB leds[NUM_LEDS];

void Underglow::setup()
{
    FastLED.addLeds<WS2812SERIAL, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 380);
}

void Underglow::loop()
{
    for (size_t i = 0; i < NUM_LEDS; i++)
    {
        leds[i].setRGB(128, 0, 255);
    }

    FastLED.show();
}