#include <Arduino.h>
#include "Globals.h"
#include "KeyMap.h"
#include "OLED.h"
#include "Backlight.h"
#include "Scanner.h"

void setup()
{
  Serial.begin(115200);
  OLED::setup();
  Backlight::setup();
  Scanner::setup();
}

void loop()
{
  Scanner::loop();
  OLED::loop();
  delay(SCAN_DELAY);
}