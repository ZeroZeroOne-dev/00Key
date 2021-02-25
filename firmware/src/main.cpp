#include <Arduino.h>
#include "Globals.h"
#include "KeyMap.h"
#include "OLED.h"
#include "Backlight.h"
#include "Underglow.h"
#include "Scanner.h"

void setup()
{
  Serial.begin(115200);
  OLED::setup();
  Backlight::setup();
  Underglow::setup();
  Scanner::setup();
}

void loop()
{
  Scanner::loop();
  OLED::loop();
  Underglow::loop();
  delay(SCAN_DELAY);
}