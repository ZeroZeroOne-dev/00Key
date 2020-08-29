#include <Arduino.h>
#include "Globals.h"
#include "KeyMap.h"
#include "OLED.h"
#include "Scanner.h"

void setup()
{
  Serial.begin(115200);
  OLED::setup();
  Scanner::setup();
}

void loop()
{
  Scanner::loop();
  delay(SCAN_DELAY);
}