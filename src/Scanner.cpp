#include <Arduino.h>
#include "Scanner.h"

namespace ZeroZeroKey
{
    Scanner::Scanner(const byte rowCount, const byte colCount, const byte *rowPins, const byte *colPins) : _rowCount(rowCount), _colCount(colCount), _rowPins(rowPins), _colPins(colPins)
    {
        for (byte i = 0; i < colCount; i++)
        {
            pinMode(colPins[i], INPUT_PULLUP);
        }

        for (byte i = 0; i < rowCount; i++)
        {
            pinMode(rowPins[i], OUTPUT);
        }
    }

    void Scanner::Scan()
    {
        for (byte i = 0; i < _rowCount; i++)
        {
            byte row = _rowPins[i];

            digitalWrite(row, LOW);

            for (byte z = 0; z < _colCount; z++)
            {
                byte col = _colPins[z];

                if (digitalRead(col) == LOW)
                {
                }
            }

            digitalWrite(row, HIGH);
        }
    }
} // namespace ZeroZeroKey