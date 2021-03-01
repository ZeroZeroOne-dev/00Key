#include <WS2812Serial.h>
#define USE_WS2812SERIAL

#include <FastLED.h>
#include "Underglow.h"
#include "OLED.h"

#define DATA_PIN 35
#define NUM_LEDS 16
#define COLOR_ORDER BRG

CRGB leds[NUM_LEDS];

int _red = 128;
int _green = 0;
int _blue = 255;

void Underglow::setup()
{
    FastLED.addLeds<WS2812SERIAL, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 380);
}

void Underglow::loop()
{
    for (size_t i = 0; i < NUM_LEDS; i++)
    {
        leds[i].setRGB(_red, _green, _blue);
    }

    FastLED.show();
}

void Underglow::add(int red, int green, int blue)
{
    if (_red + red > 255 || _green + green > 255 || _blue + blue > 255)
    {
        return;
    }

    if (_red + red < 0 || _green + green < 0 || _blue + blue < 0)
    {
        return;
    }

    _red += red;
    _green += green;
    _blue += blue;
    OLED::setUnderglow(_red, _green, _blue);
}

void Underglow::set(int red, int green, int blue)
{
    _red = red;
    _green = green;
    _blue = blue;
    OLED::setUnderglow(_red, _green, _blue);
}