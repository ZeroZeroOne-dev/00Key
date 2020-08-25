#include <Arduino.h>
#include "Scanner.h"

using namespace ZeroZeroKey;

const byte rowCount = 2;
const byte colCount = 2;
const byte rowPins[] = {12, 11};
const byte colPins[] = {4, 3};
Scanner *scanner;

void setup()
{
  Serial.begin(115200);
  scanner = new Scanner(rowCount, colCount, rowPins, colPins);
}

void loop()
{
  scanner->Scan();
}