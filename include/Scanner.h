#ifndef Scanner_h
#define Scanner_h

#include <Arduino.h>

namespace ZeroZeroKey
{
    struct ScanResult
    {
        byte row;
        byte col;
    };

    class Scanner
    {
    private:
        const byte _rowCount;
        const byte _colCount;
        const byte *_rowPins;
        const byte *_colPins;
        const byte *_status;

    public:
        Scanner(const byte rowCount, const byte colCount, const byte *rowPins, const byte *colPins);
        void Scan();
    };
} // namespace ZeroZeroKey

#endif