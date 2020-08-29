#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include "OLED.h"

Adafruit_SSD1306 display(128, 64, &Wire2, -1);

void draw00Key()
{
    display.setTextSize(2);
    display.setCursor(0, 24);
    display.print("00Key");
}

void OLED::setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setFont(&FreeSans9pt7b);
    display.setTextColor(WHITE);
    setLayer(0);
}

void OLED::setLayer(int layer)
{
    display.clearDisplay();
    draw00Key();
    display.setTextSize(1);
    display.setCursor(0, 59);
    display.print("Layer: ");
    display.print(layer);
    display.display();
}