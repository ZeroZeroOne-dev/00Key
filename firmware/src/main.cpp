#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <Keyboard.h>
#include "Globals.h"
#include "KeyMap.h"

const byte rowPins[] = {12, 11};
const byte colPins[] = {4, 3};
int *keyMap;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SCL, SDA);

#pragma region Oled

void setupOled()
{
  u8g2.begin();
}

void loopOled()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_logisoso32_tf);
  u8g2.drawStr(0, 48, "00Key");
  u8g2.sendBuffer();
}

#pragma endregion Oled

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

      if (digitalRead(col) == LOW)
      {
        pressKey(index);
      }
      else
      {
        releaseKey(index);
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
  setupOled();
}

void loop()
{
  loopScan();
  loopOled();
  delay(SCAN_DELAY);
}