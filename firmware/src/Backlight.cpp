#include <Arduino.h>
#include "Backlight.h"
#include "OLED.h"

const byte ledPin = 28;
const byte step = 51;
byte currentLevel = 255;

void writeCurrent()
{
    analogWrite(ledPin, currentLevel);

    int percentage = (double)currentLevel / 255 * 100;

    OLED::setBacklight(percentage);
}

void Backlight::setup()
{
    pinMode(ledPin, OUTPUT);
    writeCurrent();
}

void Backlight::up()
{
    if (currentLevel < 255)
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
