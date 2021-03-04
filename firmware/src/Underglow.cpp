#include <WS2812Serial.h>
#define USE_WS2812SERIAL

#include <FastLED.h>
#include "Underglow.h"
#include "OLED.h"
#include "Storage.h"

#define DATA_PIN 35
#define NUM_LEDS 16
#define COLOR_ORDER BRG

CRGB leds[NUM_LEDS];

int _red = 0;
int _green = 0;
int _blue = 0;

int shouldStore = false;
int storeStart = 0;
int storeAfter = 3000;

void store()
{
    Storage::set(StorageLocations::RED, _red);
    Storage::set(StorageLocations::GREEN, _green);
    Storage::set(StorageLocations::BLUE, _blue);
}

void Underglow::setup()
{
    FastLED.addLeds<WS2812SERIAL, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 380);

    _red = Storage::get(StorageLocations::RED);
    _green = Storage::get(StorageLocations::GREEN);
    _blue = Storage::get(StorageLocations::BLUE);
    OLED::setUnderglow(_red, _green, _blue);
}

void Underglow::loop()
{
    for (size_t i = 0; i < NUM_LEDS; i++)
    {
        leds[i].setRGB(_red, _green, _blue);
    }

    FastLED.show();

    if(shouldStore && millis() - storeStart > storeAfter)
    {
        store();
        shouldStore = false;
    }
}


void Underglow::add(int red, int green, int blue)
{
    auto newRed = _red + red;
    auto newGreen = _green + green;
    auto newBlue = _blue + blue;

    if (newRed > 255 || newGreen > 255 || newBlue > 255)
    {
        return;
    }

    if (newRed < 0 || newGreen < 0 || newBlue < 0)
    {
        return;
    }

    Underglow::set(newRed, newGreen, newBlue);
}

void Underglow::set(int red, int green, int blue)
{
    _red = red;
    _green = green;
    _blue = blue;
    OLED::setUnderglow(_red, _green, _blue);

    shouldStore = true;
    storeStart = millis();
}