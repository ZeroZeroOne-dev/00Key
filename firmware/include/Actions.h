#ifndef Actions_h
#define Actions_h

#include <Arduino.h>
#include <Globals.h>
#include <map>

typedef void (*action)();

class Actions
{
public:
    static action getAction(int key);

private:
    static const std::map<int, action> actionMap;
};

#endif