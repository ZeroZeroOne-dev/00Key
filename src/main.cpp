#include <Arduino.h>

const byte rowCount = 2;
const byte colCount = 2;
const byte rowPins[] = {23, 22};
const byte colPins[] = {34, 33};

void printKey(int row, int col)
{
  Serial.print("row: ");
  Serial.print(row + 1);
  Serial.print(" col: ");
  Serial.print(col + 1);
  Serial.println();
}

void setup()
{
  Serial.begin(115200);

  for (byte i = 0; i < colCount; i++)
  {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  for (byte i = 0; i < rowCount; i++)
  {
    pinMode(rowPins[i], OUTPUT);
  }
}

void loop()
{
  for (byte i = 0; i < rowCount; i++)
  {
    byte row = rowPins[i];

    digitalWrite(row, LOW);

    for (byte z = 0; z < colCount; z++)
    {
      byte col = colPins[z];

      if (digitalRead(col) == LOW)
      {
        printKey(i, z);
      }
    }

    digitalWrite(row, HIGH);
  }
}