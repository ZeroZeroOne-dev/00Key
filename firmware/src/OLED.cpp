#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include "OLED.h"

Adafruit_SSD1306 display(128, 64, &Wire2, -1);
int _layer = 0;
String _blLevel = "0";

void draw()
{
    display.clearDisplay();

    display.setFont(&FreeSansBold9pt7b);
    display.setCursor(0, 12);
    display.print("00Key");

    display.setFont(&FreeSans9pt7b);
    display.setCursor(0, 34);
    display.print("Layer: ");
    display.print(_layer);

    display.setCursor(0, 59);
    display.print("BLight: ");
    display.print(_blLevel);

    display.display();
}

void OLED::setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(1);

    display.setTextColor(WHITE);
    display.setTextWrap(false);
    setLayer(0);
}

void OLED::setLayer(int layer)
{
    _layer = layer;
    draw();
}

void OLED::setBacklight(String level)
{
    _blLevel = level;
    draw();
}