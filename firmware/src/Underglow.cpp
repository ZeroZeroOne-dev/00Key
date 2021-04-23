#include <WS2812Serial.h>
#define USE_WS2812SERIAL

#include <FastLED.h>
#include "Underglow.h"
#include "Storage.h"
#include "Effects/BaseEffect.h"
#include "Effects/StaticEffect.h"
#include "Effects/RainbowEffect.h"
#include "Effects/NoEffect.h"

#define DATA_PIN 35
#define NUM_LEDS 16
#define COLOR_ORDER BRG

CRGB leds[NUM_LEDS];

BaseEffect *effects[] = {
    new StaticEffect(leds, NUM_LEDS),
    new RainbowEffect(leds, NUM_LEDS),
    new NoEffect(leds, NUM_LEDS)
};
int currentEffectIndex = 0;
BaseEffect *currentEffect;

void Underglow::setup()
{
    FastLED.addLeds<WS2812SERIAL, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 380);

    for(BaseEffect* effect : effects)
    {
        effect->setup();
    }
    
    currentEffectIndex = Storage::get(StorageLocations::EFFECT);
    currentEffect = effects[currentEffectIndex];
}

void Underglow::loop()
{
    currentEffect->loop();
    FastLED.show();
}

void Underglow::nextEffect(){
    currentEffectIndex++;
    if(currentEffectIndex > 2){
        currentEffectIndex = 0;
    }
    
    currentEffect = effects[currentEffectIndex];

    Storage::set(StorageLocations::EFFECT, currentEffectIndex);

    FastLED.clear();
}