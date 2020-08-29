#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans18pt7b.h>
#include "Globals.h"
#include "KeyMap.h"
#include "Scanner.h"

#pragma region OLED

Adafruit_SSD1306 display(128, 64, &Wire2, -1);

void setupOled()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loopOled()
{
  display.clearDisplay();
  display.setFont(&FreeSans18pt7b);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 41);
  display.print("00Key");
  display.display();
}

#pragma endregion OLED

void setup()
{
  Serial.begin(115200);
  Scanner::setup();
  setupOled();
}

void loop()
{
  Scanner::loop();
  loopOled();
  delay(SCAN_DELAY);
}