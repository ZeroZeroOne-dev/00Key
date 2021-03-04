#ifndef Actions_h
#define Actions_h

#include <Arduino.h>
#include <Globals.h>
#include <map>

typedef bool (*action)(KeyDirection);

class Actions
{
public:
    static action getAction(int key);
    static void loop();

private:
    static const std::map<int, action> actionMap;
};

#endif