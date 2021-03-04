#include <Arduino.h>
#include "Scanner.h"
#include "Globals.h"
#include "KeyMap.h"
#include "Actions.h"

const byte rowPins[] = {0, 1, 2, 3, 4, 5};
const byte colPins[] = {23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 41, 40, 39, 38, 37, 36};
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

    statusMap[row][col] = true;
    auto key = KeyMap::getKey(row, col);

    auto action = Actions::getAction(key);
    if (action == NULL || action(KeyDirection::DOWN))
    {
        Keyboard.press(key);
    }
}

void releaseKey(byte row, byte col)
{
    if (statusMap[row][col] == false)
    {
        return;
    }

    statusMap[row][col] = false;
    auto key = KeyMap::getKey(row, col);

    auto action = Actions::getAction(key);
    if (action == NULL || action(KeyDirection::UP))
    {
        Keyboard.release(key);
    }
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