#ifndef Actions_h
#define Actions_h

#include <Arduino.h>
#include <Globals.h>

typedef bool (*action)();

class Actions
{
public:
    static action getAction(bool statusMap[ROW_COUNT][COL_COUNT]);
};

#endif