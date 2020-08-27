#include <Arduino.h>
#include "Globals.h"
#include "KeyMap.h"

const byte rowPins[] = {33, 34};
const byte colPins[] = {31, 32};
int *keyMap;

#pragma region Keyboard

void pressKey(byte row, byte col)
{
  auto key = KeyMap::getKey(row, col);
  Keyboard.press(key);
}

void releaseKey(byte row, byte col)
{
  auto key = KeyMap::getKey(row, col);
  Keyboard.release(key);
}

#pragma endregion Keyboard

#pragma region Scanning

void setupScan()
{
  for (byte i = 0; i < COL_COUNT; i++)
  {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  for (byte i = 0; i < ROW_COUNT; i++)
  {
    pinMode(rowPins[i], OUTPUT);
  }
}

void loopScan()
{
  for (byte rowIndex = 0; rowIndex < ROW_COUNT; rowIndex++)
  {
    byte row = rowPins[rowIndex];

    digitalWrite(row, LOW);
    delayMicroseconds(PIN_CHANGE_DELAY);

    for (byte colIndex = 0; colIndex < COL_COUNT; colIndex++)
    {
      byte col = colPins[colIndex];

      if (digitalRead(col) == LOW)
      {
        pressKey(rowIndex, colIndex);
      }
      else
      {
        releaseKey(rowIndex, colIndex);
      }
    }

    digitalWrite(row, HIGH);
  }
}

#pragma endregion Scanning

void setup()
{
  Serial.begin(115200);
  setupScan();
}

void loop()
{
  loopScan();
  delay(SCAN_DELAY);
}