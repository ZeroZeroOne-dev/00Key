#include <Arduino.h>
#include "Globals.h"
#include "KeyMap.h"
#include "Keyboard.h"

const byte rowPins[] = {12, 11};
const byte colPins[] = {4, 3};

char *keyMap;
byte keyStatus[ROW_COUNT * COL_COUNT] = {0};

#pragma region Translations

byte getIndex(byte row, byte col)
{
  return col + (row * COL_COUNT);
}

#pragma endregion Translations

#pragma region KeyMap

void setupKeyMap()
{
  keyMap = KeyMap::getMap();
}

byte getKey(byte index)
{
  return keyMap[index];
}

#pragma endregion KeyMap

#pragma region Keyboard

void pressKey(byte index)
{
  auto key = getKey(index);
  Keyboard.press(key);
}

void releaseKey(byte index)
{
  auto key = getKey(index);
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
      byte index = getIndex(rowIndex, colIndex);

      if (keyStatus[index] == 0 && digitalRead(col) == LOW)
      {
        keyStatus[index] = DEBOUNCE * 2;
        pressKey(index);
      }
      else if (keyStatus[index] > DEBOUNCE + 1)
      {
        keyStatus[index]--;
      }
      else if (keyStatus[index] == DEBOUNCE + 1 && digitalRead(col) == HIGH)
      {
        keyStatus[index]--;
        releaseKey(index);
      }
      else if (keyStatus[index] > 0 && keyStatus[index] <= DEBOUNCE)
      {
        keyStatus[index]--;
      }
    }

    digitalWrite(row, HIGH);
  }
}

#pragma endregion Scanning

void setup()
{
  Serial.begin(115200);
  setupKeyMap();
  setupScan();
}

void loop()
{
  loopScan();
  delay(SCAN_DELAY);
}