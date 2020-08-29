#include <Arduino.h>
#include "Scanner.h"
#include "KeyMap.h"
#include "Globals.h"

const byte rowPins[] = {33, 34};
const byte colPins[] = {31, 32};
bool statusMap[ROW_COUNT][COL_COUNT] = {{false}};

void Scanner::setup()
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

void pressKey(byte row, byte col)
{
    if (statusMap[row][col] == true)
    {
        return;
    }

    auto key = KeyMap::getKey(row, col);
    statusMap[row][col] = true;
    Keyboard.press(key);
}

void releaseKey(byte row, byte col)
{
    if (statusMap[row][col] == false)
    {
        return;
    }

    auto key = KeyMap::getKey(row, col);
    statusMap[row][col] = false;
    Keyboard.release(key);
}

void Scanner::loop()
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