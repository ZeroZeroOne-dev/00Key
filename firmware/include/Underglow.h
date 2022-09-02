#ifndef Underglow_h
#define Underglow_h

#include "Effects/StaticEffect.h"

class Underglow
{
public:
    static void setup();
    static void loop();
    static void nextEffect();
    static StaticEffect* getCurrentStaticEffect();
};

#endif