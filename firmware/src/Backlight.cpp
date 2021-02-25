#include <Arduino.h>
#include "Backlight.h"
#include "OLED.h"

const byte ledPin = 28;
const byte step = 25;
byte currentLevel = 125;
byte maxLevel = 125;

void writeCurrent()
{
    analogWrite(ledPin, currentLevel);

    int percentage = (double)currentLevel / maxLevel * 100;

    OLED::setBacklight(percentage);
}

void Backlight::setup()
{
    pinMode(ledPin, OUTPUT);
    writeCurrent();
}

void Backlight::up()
{
    if (currentLevel < maxLevel)
    {
        currentLevel += step;
    }

    writeCurrent();
}

void Backlight::down()
{
    if (currentLevel > 0)
    {
        currentLevel -= step;
    }

    writeCurrent();
}
