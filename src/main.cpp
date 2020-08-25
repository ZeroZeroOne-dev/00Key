#include <Arduino.h>
#include "KeyMap.h"
#include "Globals.h"
#include "Keyboard.h"

const byte rowPins[] = {12, 11};
const byte colPins[] = {4, 3};

char *keyMap;

#pragma region Keyboard

void sendKey(byte key)
{
  Keyboard.write(key);
}

#pragma endregion Keyboard

#pragma region KeyMap

void setupKeyMap()
{
  keyMap = KeyMap::getMap();
}

byte getKey(byte row, byte col)
{
  auto index = col + (row * COL_COUNT);
  return keyMap[index];
}

#pragma endregion KeyMap

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
    delayMicroseconds(200);

    for (byte colIndex = 0; colIndex < COL_COUNT; colIndex++)
    {
      byte col = colPins[colIndex];

      if (digitalRead(col) == LOW)
      {
        auto key = getKey(rowIndex, colIndex);
        sendKey(key);
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
  delay(5);
}